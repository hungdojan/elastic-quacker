import logging
import re

from .error import *
from .key_seqv import KeySeqv
from .mappings import *
from .regex_groups import Groups, KEY_SEQV_REGEX, LINE_REGEX


LOG_FUN = {
    logging.WARN: logging.warn,
    logging.ERROR: logging.error,
    logging.INFO: logging.info,
    logging.DEBUG: logging.debug
}

class KeySeqvParser:

    def __init__(self, verbose: bool=False):
        self._verbose = verbose
        self._lof_keyseqvs: list[KeySeqv] = []
        self.__new_sequece_structure()
        self.__compile_patterns()


    @property
    def lof_keyseqvs(self) -> tuple:
        """Returns set of key sequences."""
        return tuple(self._lof_keyseqvs)


    @property
    def verbose(self) -> bool:
        return self._verbose


    @verbose.setter
    def verbose(self, value):
        self._verbose = value


    def __compile_patterns(self):
        self._line_regex = re.compile(LINE_REGEX)
        self._key_seqv_regex = re.compile(KEY_SEQV_REGEX)


    def clear_lof_keyseqvs(self):
        """Clear the set of key sequences."""
        self._lof_keyseqvs.clear()


    def set_last(self):
        """Set last item's last flag."""
        if self._lof_keyseqvs:
            last_item = self._lof_keyseqvs[-1]
            last_item.last = True


    def __new_sequece_structure(self):
        """Create a new structure for the keys."""
        self._ks_struct = {
            'delay': 0,
            'modifiers': [],
            'keys': []
        }


    def _create_log(self, _type: int, msg: str):
        """Write a report into logging file."""
        if not self._verbose:
            return

        fnc = LOG_FUN.get(_type)
        if fnc:
            fnc(msg)


    def _log_seqv_content(self):
        """Log the latest key sequence."""
        out_str = ''
        # log delay
        if self._ks_struct['delay']:
            status = 'Wait' if not self._ks_struct['keys'] else 'Hold'
            out_str += f'{status}: {self._ks_struct["delay"]} ms; '
        # log modifiers
        if self._ks_struct['modifiers']:
            modifiers = ', '.join([x.name for x in self._ks_struct['modifiers']])
            out_str += f'Modifiers: [{modifiers}]; '
        # log keys
        if self._ks_struct['keys']:
            keys = ', '.join([MAPPING_KEYS[MAPPING_VALUES.index(x)]
                              for x in self._ks_struct['keys']])
            out_str += f'Keys: [{keys}]'
        # write into log
        self._create_log(logging.INFO, out_str)


    def _push_pressed_and_released(self):
        """Simulate keys press and prepare new key sequence structure."""
        # keys pressed
        self._lof_keyseqvs.append(KeySeqv(**self._ks_struct))
        self._log_seqv_content()
        self.__new_sequece_structure()
        # keys released
        self._lof_keyseqvs.append(KeySeqv(**self._ks_struct))
        self.__new_sequece_structure()


    def _parse_normal_keys(self, value: str):
        """Parsing normal keys.

        Args:
            value (str): Key value to parse.
        """
        # check if symbol requires shift modifier
        if value in SHIFT_TO_NORMAL_MAP or value.isupper():
            key_macro_name = NORMAL_TO_KEY_MAP[SHIFT_TO_NORMAL_MAP[value]] \
                             if value in SHIFT_TO_NORMAL_MAP else \
                             NORMAL_TO_KEY_MAP[value.lower()]
            # first check if the key is already being pressed
            # if so we need to release it first (push current sequence)
            # and press it again
            if key_macro_name in self._ks_struct['keys']:
                self._push_pressed_and_released()

            # new sequence
            if not self._ks_struct['keys']:
                self._ks_struct['modifiers'].append(Modifier.LSHIFT)
            # shift is not toggled yet push the key sequence first
            elif Modifier.LSHIFT not in self._ks_struct['modifiers'] and \
                 Modifier.RSHIFT not in self._ks_struct['modifiers']:
                self._push_pressed_and_released()
                self._ks_struct['modifiers'].append(Modifier.LSHIFT)

            self._ks_struct['keys'].append(key_macro_name)

        else:
            key_macro_name = NORMAL_TO_KEY_MAP[value]
            # first check if the key is already being pressed
            # if so we need to release it first (push current sequence)
            # and press it again
            if key_macro_name in self._ks_struct['keys']:
                self._push_pressed_and_released()

            # if shift is toggled push the key sequence first
            if Modifier.LSHIFT in self._ks_struct['modifiers'] or \
               Modifier.RSHIFT in self._ks_struct['modifiers']:
                self._push_pressed_and_released()
            self._ks_struct['keys'].append(NORMAL_TO_KEY_MAP[value])


    def _parse_normal_keys_in_special(self, match: list,
                                      line_index: int) -> tuple[bool, list[Key]]:
        """Parsing normal key sequence inside special sequence.

        Args:
            match (list): Regex's list of matches (output of findall).
            line_index (int): Line's index (used in logging).

        Raises:
            SpecialSequenceShiftToggleError: Inconsistent shift toggle;
                            some normal keys require shift modifier and some don't.

        Returns:
            tuple[bool, list[Key]]: First value tells parser that shift modifier is used.
                                    Second value contains a list of pressed keys.
        """
        keys = match[Groups.SPECIAL_VALUE.value]
        keys_pressed = []
        is_shift_toggled = False
        for i, key in enumerate(keys):
            if i == 0:
                is_shift_toggled = key in SHIFT_TO_NORMAL_MAP or key.isupper()

            # shift keys
            if (is_shift_toggled and (key in SHIFT_TO_NORMAL_MAP or key.isupper())):
                key_name = NORMAL_TO_KEY_MAP[SHIFT_TO_NORMAL_MAP[key]] \
                           if key in SHIFT_TO_NORMAL_MAP else \
                           NORMAL_TO_KEY_MAP[key.lower()]
                # the key is already pressed
                if key_name in keys_pressed:
                    self._create_log(logging.WARN,
                                     f'The key "{key}" is pressed multiple times in ' \
                                     f'"{match[Groups.SPECIAL_ORIGINAL.value]}" on line {line_index+1}')
                    continue
                keys_pressed.append(key_name)
            # non-shift keys
            elif (not is_shift_toggled and key not in SHIFT_TO_NORMAL_MAP and not key.isupper()):
                # the key is already pressed
                if NORMAL_TO_KEY_MAP[key] in keys_pressed:
                    self._create_log(logging.WARN,
                                     f'The key "{key}" is pressed multiple times in ' \
                                     f'"{match[Groups.SPECIAL_ORIGINAL.value]}" on line {line_index+1}')
                    continue
                keys_pressed.append(NORMAL_TO_KEY_MAP[key])
            else:
                self._create_log(logging.ERROR,
                                 'Inconsistent use of shift modifier in ' \
                                 f'"{match[Groups.SPECIAL_ORIGINAL.value]}" on line {line_index+1}!')
                raise SpecialSequenceShiftToggleError()
        return is_shift_toggled, keys_pressed


    def _check_special_sequence(self, match: list, line_index: int):
        """Parsing special sequences.

        Args:
            match (list): Regex's list of matches (output of findall).
            line_index (int): Line's index (used in logging).

        Raises:
            UnknownModifierError: Parser came across unknown modifier.
            UndefinedSpecialKeyNameError: Parser came across unknown special key.
            KeySequenceSizeExceededError: Special sequence of normal keys exceeded max limit.
            ShiftToggleWithNormalKeyError: Shift modifier cannot be present together with normal key sequence.
            ParserError: Any other error related to parsing.
        """
        used_modifiers: list[Modifier] = []
        if match[Groups.SPECIAL_MODIFIERS.value]:
            # extracts modifiers
            seqv_modifiers = match[Groups.SPECIAL_MODIFIERS.value].split('-')[:-1]
            for m in seqv_modifiers:
                if not MODIFIER_MAP.get(m.lower()):
                    self._create_log(logging.ERROR,
                                     f'Unexpected modifier "{m}" in "{match[Groups.SPECIAL_ORIGINAL.value]}" ' \
                                     f'on line {line_index+1}!')
                    raise UnknownModifierError()
                if MODIFIER_MAP[m.lower()] in used_modifiers:
                    self._create_log(logging.WARN,
                                     f'Duplicate use of modifier "{m}" in ' \
                                     f'"{match[Groups.SPECIAL_ORIGINAL.value]}" on line {line_index+1}')
                    continue
                used_modifiers.append(MODIFIER_MAP[m.lower()])

        special_value: str = match[Groups.SPECIAL_VALUE.value]
        # the escape sign on this position tells the parser that
        # the next set of characters defines a special keys name
        # (SPECIAL_MAP or MACRO_KEYS)
        if match[Groups.SPECIAL_ESCAPE_EN.value]:
            # special key (like escape or return)
            if special_value.lower() in SPECIAL_MAP:
                self._ks_struct['keys'].append(SPECIAL_MAP[special_value.lower()])
                self._ks_struct['modifiers'] = used_modifiers
                if match[Groups.SPECIAL_HOLD_DELAY.value]:
                    self._ks_struct['delay'] = int(match[Groups.SPECIAL_HOLD_DELAY.value])
                return
            # macro key (like gt or lt)
            if special_value.lower() in MACRO_KEYS:
                # add shift if not toggled yet
                key_modifier, key_value = MACRO_KEYS[special_value.lower()]
                if key_modifier and key_modifier not in used_modifiers:
                    used_modifiers.append(key_modifier)

                self._ks_struct['keys'].append(key_value)
                self._ks_struct['modifiers'] = used_modifiers
                if match[Groups.SPECIAL_HOLD_DELAY.value]:
                    self._ks_struct['delay'] = int(match[Groups.SPECIAL_HOLD_DELAY.value])
                return
            self._create_log(logging.ERROR,
                             f'Unknown special key value "{special_value}" in ' \
                             f'"{match[Groups.SPECIAL_ORIGINAL.value]}" on line {line_index+1}')
            raise UndefinedSpecialKeyNameError()

        # otherwise normal keys are expected
        # can't send more than 6 keys at once
        if len(special_value) > 6:
            self._create_log(logging.ERROR,
                             'Special sequence value is too long (max 6 keys): ' \
                             f'"{match[Groups.SPECIAL_ORIGINAL.value]}" on line {line_index+1}')
            raise KeySequenceSizeExceededError()
        # shift should not be toggled yet
        if (Modifier.LSHIFT in used_modifiers or
            Modifier.RSHIFT in used_modifiers):
            self._create_log(logging.ERROR,
                             'When pressing normal keys, special key sequence ' \
                             'should not contain shift modifier in the script.')
            self._create_log(logging.ERROR,
                             f'Remove "s-" from {match[Groups.SPECIAL_ORIGINAL.value]} on line {line_index+1}')
            raise ShiftToggleWithNormalKeyError()

        # get the sequence
        is_shift_toggled, keys_pressed = self._parse_normal_keys_in_special(match, line_index)

        if is_shift_toggled:
            used_modifiers.append(Modifier.LSHIFT)

        self._ks_struct['modifiers'] = used_modifiers
        self._ks_struct['keys'] = keys_pressed
        if match[Groups.SPECIAL_HOLD_DELAY.value]:
            self._ks_struct['delay'] = int(match[Groups.SPECIAL_HOLD_DELAY.value])


    def parse_line(self, line: str, line_index: int):
        """Parses the given line to create KeySeqv objects.

        Created objects are stored in KeySeqvParser.lof_keyseqvs.

        Args:
            line (str): Line content
            line_index (int): Line's index (used in logging).

        Raises:
            NonReadableCharacterError: The line contains non ASCII printable character.
            ParserError: Any other error related to parsing.
        """

        if not self._line_regex.match(line):
            self._create_log(logging.ERROR,
                             f'Line {line_index+1} contains an unknown character. ' \
                             'Only printable ascii characters are allowed.')
            raise NonReadableCharacterError()

        matches = self._key_seqv_regex.findall(line)
        is_special_seqv = False

        for match in matches:
            # wait delay <DELAY [time_in_ms]>
            if match[Groups.DELAY_WAIT_ORIGINAL.value]:
                # finish previous sequence and add delay to the new one
                if self._ks_struct['keys'] or self._ks_struct['delay']:
                    # keys pressed
                    self._lof_keyseqvs.append(KeySeqv(**self._ks_struct))
                    self._log_seqv_content()
                    self.__new_sequece_structure()
                # keys release with delay
                self._ks_struct['delay'] = int(match[Groups.DELAY_WAIT_VALUE.value])
                self._lof_keyseqvs.append(KeySeqv(**self._ks_struct))
                self._log_seqv_content()
                self.__new_sequece_structure()
                is_special_seqv = False

            if is_special_seqv:
                self._lof_keyseqvs.append(KeySeqv(**self._ks_struct))
                self.__new_sequece_structure()
                is_special_seqv = False

            # max 6 keys pressed are allowed to be sent at the same time
            if len(self._ks_struct['keys']) > 5:
                self._push_pressed_and_released()

            # load special <[content]>
            if match[Groups.SPECIAL_ORIGINAL.value]:
                # push current sequence and create it for special sequence
                if self._ks_struct['keys']:
                    self._push_pressed_and_released()

                self._check_special_sequence(match, line_index)

                # push but wait for delay
                is_special_seqv = True
                self._lof_keyseqvs.append(KeySeqv(**self._ks_struct))
                self._log_seqv_content()
                self.__new_sequece_structure()

            # ignoring comments [everything that start with # character]
            if match[Groups.COMMENT.value]:
                pass

            # load normal keys [any_printable]
            elif match[Groups.NORMAL_KEYS.value]:
                value: str = match[Groups.NORMAL_KEYS.value]
                self._parse_normal_keys(value)

        # finish last item pending (if exists)
        if self._ks_struct['keys']:
            self._push_pressed_and_released()

        if is_special_seqv:
            self._lof_keyseqvs.append(KeySeqv(**self._ks_struct))
            self.__new_sequece_structure()
