import os
import pytest

from rd_client.parser.error import KeySequenceSizeExceededError, NonReadableCharacterError, ShiftToggleWithNormalKeyError, SpecialSequenceShiftToggleError, UndefinedSpecialKeyNameError, UnknownModifierError
from rd_client.parser.mappings import normal_mapping, shift_mapping
from rd_client.parser.key_seqv import KeySeqv, Modifier, Key
from rd_client.parser.key_seqv_parser import KeySeqvParser

@pytest.fixture()
def ksp() -> KeySeqvParser:
    parser = KeySeqvParser(verbose=False)
    return parser


def test_key_seqv():
    # delay
    ks_delay = KeySeqv(delay=500, keys=[])
    assert ks_delay.delay == 500
    assert not ks_delay.keys
    assert not ks_delay.modifiers
    assert '    {500, {0, 0, {0,}}, false},\n' == str(ks_delay)

    # normal key
    ks_normal = KeySeqv(keys=[Key.KEY_A])
    assert len(ks_normal.keys) == 1
    assert not ks_normal.modifiers

    # special sequence
    modifiers = [Modifier.LALT]
    keys = [Key.KEY_A, Key.KEY_B]
    key_seqv = KeySeqv(keys, modifiers=modifiers)
    test_str = str(key_seqv)
    assert '    {0, {KEYBOARD_MODIFIER_LEFTALT, 0, {HID_KEY_A, HID_KEY_B}}, false},\n' == test_str
    assert str(key_seqv) == repr(key_seqv)

    # last
    ks_last = KeySeqv(keys=[])
    ks_last.last = True
    assert ks_last.last


def test_empty_list(ksp: KeySeqvParser):
    ksp.set_last()

    assert len(ksp.lof_keyseqvs) == 0


def test_normal_key(ksp: KeySeqvParser):
    test_str = ['a', 'multiple', 'doodle', ',.']
    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    # remove key releases (empty ks.keys)
    key_presses = [ks.keys for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(key_presses) == 6

    # first line
    assert len(key_presses[0]) == 1
    assert set(key_presses[0]) == {normal_mapping[test_str[0]],}

    # second line; [multip, le]
    assert len(key_presses[1]) == 6
    assert set(key_presses[1]) == set([normal_mapping[x] for x in test_str[1][:6]])
    assert len(key_presses[2]) == 2

    # third line; [do, odle]
    assert len(key_presses[3]) == 2
    assert len(key_presses[4]) == 4
    assert set(key_presses[4]) == set([normal_mapping[x] for x in test_str[2][2:]])

    # forth line; [',.']
    assert len(key_presses[5]) == 2
    assert set(key_presses[5]) == set([normal_mapping[x] for x in test_str[3]])


def test_normal_key_shift(ksp: KeySeqvParser):
    test_str = ['A', 'MULTIPLE', 'DOODLE', '{}']
    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    # remove key releases (empty ks.keys)
    key_presses = [ks for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(key_presses) == 6

    # first line
    assert len(key_presses[0].keys) == 1
    assert set(key_presses[0].keys) == {normal_mapping[test_str[0].lower()],}
    assert Modifier.LSHIFT in key_presses[0].modifiers

    # second line; [multip, le]
    assert len(key_presses[1].keys) == 6
    assert Modifier.LSHIFT in key_presses[1].modifiers
    assert set(key_presses[1].keys) == set([normal_mapping[x.lower()] for x in test_str[1][:6]])
    assert len(key_presses[2].keys) == 2

    # third line; [do, odle]
    assert len(key_presses[3].keys) == 2
    assert len(key_presses[4].keys) == 4
    assert set(key_presses[4].keys) == set([normal_mapping[x.lower()] for x in test_str[2][2:]])

    # forth line; ['{}']
    assert len(key_presses[5].keys) == 2
    assert set(key_presses[5].keys) == set([normal_mapping[shift_mapping[x]] for x in test_str[3]])


def test_normal_key_combined(ksp: KeySeqvParser):
    test_str = ['abcdefABCDEF', 'comBiNATion']

    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    ks_pressed = [ks for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(ks_pressed) == 7

    # first line; ['abcdef', 'ABCDEF']
    assert len(ks_pressed[0].keys) == 6
    assert not ks_pressed[0].modifiers
    assert len(ks_pressed[1].keys) == 6
    assert Modifier.LSHIFT in ks_pressed[1].modifiers

    # second line
    # 'com'
    assert len(ks_pressed[2].keys) == 3
    assert not ks_pressed[2].modifiers
    # 'B'
    assert len(ks_pressed[3].keys) == 1
    assert Modifier.LSHIFT in ks_pressed[3].modifiers
    # 'i'
    assert len(ks_pressed[4].keys) == 1
    assert not ks_pressed[4].modifiers
    # 'NAT'
    assert len(ks_pressed[5].keys) == 3
    assert Modifier.LSHIFT in ks_pressed[5].modifiers
    # 'ion'
    assert len(ks_pressed[6].keys) == 3
    assert not ks_pressed[6].modifiers


def test_delay(ksp: KeySeqvParser):
    test_str = '<DELAY 500>str<DELAY 600>'

    ksp.parse_line(test_str, 0)

    assert len(ksp.lof_keyseqvs) == 3
    # <DELAY 500>
    assert ksp.lof_keyseqvs[0].delay == 500
    # str
    assert ksp.lof_keyseqvs[1].delay == 0
    # <DELAY 600>
    assert ksp.lof_keyseqvs[2].delay == 600


def test_special_key(ksp: KeySeqvParser):
    test_str = [r'<\enter>a', r'\enter', r'<\esc><\bs><\gt><\lt>', r'<\CAPS_LOCK><\arrow_UP>']
    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    ks_pressed = [ks for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(ks_pressed) == 10

    # first line
    assert len(ks_pressed[0].keys) == 1
    assert Key.KEY_ENTER in ks_pressed[0].keys

    # second line
    assert len(ks_pressed[2].keys) == 4
    assert len(ks_pressed[3].keys) == 2

    # third line
    assert Key.KEY_ESCAPE in ks_pressed[4].keys
    assert Key.KEY_BACKSPACE in ks_pressed[5].keys
    assert (Key.KEY_PERIOD in ks_pressed[6].keys and
            Modifier.LSHIFT in ks_pressed[6].modifiers)
    assert (Key.KEY_COMMA in ks_pressed[7].keys and
            Modifier.LSHIFT in ks_pressed[7].modifiers)

    # forth line
    assert Key.KEY_CAPS_LOCK in ks_pressed[8].keys
    assert Key.KEY_ARROW_UP in ks_pressed[9].keys


def test_comments(ksp: KeySeqvParser):
    test_str = [r'# this is a comment', r'<\bs># this is a comment', r'<#>']

    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    ks_pressed = [ks for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(ks_pressed) == 2

    # first line
    assert normal_mapping[shift_mapping['#']] not in ks_pressed[0].keys

    # second line
    assert len(ks_pressed[0].keys) == 1
    assert Key.KEY_BACKSPACE in ks_pressed[0].keys

    # third line
    assert len(ks_pressed[1].keys) == 1
    assert (normal_mapping[shift_mapping['#']] in ks_pressed[1].keys and
            Modifier.LSHIFT in ks_pressed[1].modifiers)


def test_special_sequence(ksp: KeySeqvParser):
    test_str = ['<string>', '<STR>', r'<a\esc>']
    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    ks_pressed = [ks for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(ks_pressed) == 3

    # first line
    assert len(ks_pressed[0].keys) == 6
    assert set(ks_pressed[0].keys) == set([normal_mapping[x] for x in test_str[0][1:-1]])

    # second line
    assert len(ks_pressed[1].keys) == 3
    assert (Modifier.LSHIFT in ks_pressed[1].modifiers and
            set(ks_pressed[1].keys) == set([normal_mapping[x.lower()]
                                            for x in test_str[1][1:-1]]))

    # third line
    assert len(ks_pressed[2].keys) == 5
    assert Key.KEY_ESCAPE not in ks_pressed[2].keys


def test_special_sequence_modifiers(ksp: KeySeqvParser):
    test_str = [
        '<a-a>'
        '<a-c-a>'
        '<a-c-m-a>'
        '<la-ra-a>'
        '<a-ra-a>'
        '<c-rc-a>'
        '<a-xyz>'
        r'<a-\esc>'
        r'<a-s-\esc>'
        r'<a-c-s-\enter>'
    ]

    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    ks_pressed = [ks for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(ks_pressed) == 10

    # first line
    assert (Key.KEY_A in ks_pressed[0].keys and
            Modifier.LALT in ks_pressed[0].modifiers)

    # second line
    assert (Key.KEY_A in ks_pressed[1].keys and
            len(ks_pressed[1].modifiers) == 2)

    # third line
    assert (Key.KEY_A in ks_pressed[2].keys and
            len(ks_pressed[2].modifiers) == 3)

    # forth, fifth and sixth lines
    assert all([x in [Modifier.LALT, Modifier.RALT] for x in ks_pressed[3].modifiers])
    assert all([x in [Modifier.LALT, Modifier.RALT] for x in ks_pressed[4].modifiers])
    assert all([x in [Modifier.LCTRL, Modifier.RCTRL] for x in ks_pressed[5].modifiers])

    # seventh line
    assert Modifier.LALT in ks_pressed[6].modifiers
    assert len(ks_pressed[6].keys) == 3

    # eighth line
    assert Modifier.LALT in ks_pressed[7].modifiers
    assert len(ks_pressed[7].keys) == 1 and Key.KEY_ESCAPE in ks_pressed[7].keys

    # nineth line
    assert all(x in [Modifier.LALT, Modifier.LSHIFT] for x in ks_pressed[8].modifiers)
    assert len(ks_pressed[8].keys) == 1 and Key.KEY_ESCAPE in ks_pressed[8].keys

    # tenth line
    assert all(x in [Modifier.LALT, Modifier.LCTRL, Modifier.LSHIFT] for x in ks_pressed[9].modifiers)
    assert len(ks_pressed[9].keys) == 1 and Key.KEY_ENTER in ks_pressed[9].keys


def test_special_sequence_hold(ksp: KeySeqvParser):
    test_str = [r'<200-a-c-\gt>', r'<30-a-a><DELAY 500><40-\esc>a<50-\enter>']

    for i, s in enumerate(test_str):
        ksp.parse_line(s, i)

    assert len(ksp.lof_keyseqvs) == 10

    # first line
    assert ksp.lof_keyseqvs[0].delay == 200
    assert all([x in [Modifier.LALT, Modifier.LCTRL, Modifier.LSHIFT]
                for x in ksp.lof_keyseqvs[0].modifiers])
    assert Key.KEY_PERIOD in ksp.lof_keyseqvs[0].keys

    # second line
    assert ksp.lof_keyseqvs[2].delay == 30
    assert Modifier.LALT in ksp.lof_keyseqvs[2].modifiers
    assert Key.KEY_A in ksp.lof_keyseqvs[2].keys

    assert ksp.lof_keyseqvs[3].delay == 500

    assert ksp.lof_keyseqvs[4].delay == 40
    assert not ksp.lof_keyseqvs[4].modifiers
    assert (len(ksp.lof_keyseqvs[4].keys) == 1 and
            Key.KEY_ESCAPE in ksp.lof_keyseqvs[4].keys)

    assert Key.KEY_A in ksp.lof_keyseqvs[6].keys

    assert ksp.lof_keyseqvs[8].delay == 50
    assert Key.KEY_ENTER in ksp.lof_keyseqvs[8].keys


def test_errors(ksp: KeySeqvParser):
    ksp.verbose = True
    assert ksp.verbose

    with pytest.raises(NonReadableCharacterError):
        ksp.parse_line('䝣', 0)

    with pytest.raises(SpecialSequenceShiftToggleError):
        ksp.parse_line('<a-aH>', 0)

    with pytest.raises(UnknownModifierError):
        ksp.parse_line('<g-a>', 0)

    with pytest.raises(UndefinedSpecialKeyNameError):
        ksp.parse_line(r'<a-\random>', 0)

    with pytest.raises(KeySequenceSizeExceededError):
        ksp.parse_line('<a-abcdefg>', 0)

    with pytest.raises(ShiftToggleWithNormalKeyError):
        ksp.parse_line('<a-s-a>', 0)


def test_warnings(ksp: KeySeqvParser):
    # same key pressed multiple times in special sequence
    ksp.parse_line('<a-aa>', 0)
    assert len(ksp.lof_keyseqvs[0].keys) == 1
    ksp.parse_line('<a-AA>', 0)
    assert len(ksp.lof_keyseqvs[2].keys) == 1

    # duplicate modifier use
    ksp.parse_line('<a-a-a>', 0)
    assert len(ksp.lof_keyseqvs[4].modifiers) != 2
    ksp.parse_line('<a-la-a>', 0)
    assert len(ksp.lof_keyseqvs[6].modifiers) != 2


def test_last_and_clear(ksp: KeySeqvParser):
    ksp.parse_line('string', 0)
    assert len(ksp.lof_keyseqvs) == 2

    assert not ksp.lof_keyseqvs[-1].last
    ksp.set_last()
    assert ksp.lof_keyseqvs[-1].last

    ksp.clear_lof_keyseqvs()
    assert len(ksp.lof_keyseqvs) == 0


def test_file(ksp: KeySeqvParser):
    # TODO: path
    dir_path = os.path.dirname(os.path.realpath(__file__))
    with open(f'{dir_path}/resources/open_fit_vutbr.txt', 'r') as f:
        for i, line in enumerate(f):
            ksp.parse_line(line, i)
    ksp.set_last()

    ks_pressed = [ks for ks in ksp.lof_keyseqvs if ks.keys]
    assert len(ks_pressed) == 6

    # first (non comment) line
    assert len(ks_pressed[0].modifiers) == 1 and Modifier.LALT in ks_pressed[0].modifiers
    assert len(ks_pressed[0].keys) == 1 and Key.KEY_ENTER in ks_pressed[0].keys

    # second (non comment) line
    assert len(ks_pressed[1].keys) == 4 # 'fire'
    assert len(ks_pressed[2].keys) == 4 # 'fox '
    assert len(ks_pressed[3].keys) == 6 # 'fit.vu'
    assert len(ks_pressed[4].keys) == 6 # 'tbr.cz'
    assert len(ks_pressed[5].keys) == 1 and Key.KEY_ENTER in ks_pressed[5].keys
