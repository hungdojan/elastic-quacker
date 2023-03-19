from .mappings import Key, Modifier, MODIFIER_INDEX_MAP, KEY_TO_VALUE_MAP

class KeySeqv:

    def __init__(self, keys: list[Key], delay: int=0,
                 modifiers: list[Modifier]=[], last: bool=False):
        self.__delay = delay
        self.__modifiers = modifiers
        self.__keys = keys
        self.__last = last


    @property
    def delay(self) -> int:
        return self.__delay


    @property
    def modifiers(self) -> tuple[Modifier]:
        return tuple(self.__modifiers)


    @property
    def keys(self) -> tuple[Key]:
        return tuple(self.__keys)


    @property
    def last(self) -> bool:
        return self.__last


    @last.setter
    def last(self, value: bool):
        self.__last = value


    def to_bytes(self) -> bytearray:
        _b = bytearray()

        # delay
        _b.extend(self.delay.to_bytes(4, 'little'))

        # report
        # modifiers
        modifier = 0
        for m in self.modifiers:
            modifier |= (1 << MODIFIER_INDEX_MAP.index(m))
        _b.append(modifier)
        # reserved
        _b.append(0)
        keycodes = self.__keys + [Key.KEY_NONE for _ in range(6 - len(self.keys))]
        # keycodes
        for kc in keycodes:
            _b.append(KEY_TO_VALUE_MAP[kc])

        # last
        _b.append(self.last)

        return _b


    def __str__(self) -> str:
        out = '    {'
        out += f'{self.__delay}, {{'
        if self.__modifiers:
            out += '|'.join([m.value for m in self.__modifiers])
        else:
            out += '0'
        out += ', 0, {'
        if self.__keys:
            out += ', '.join([k.value for k in self.__keys])
        else:
            out += '0,'
        out += '}}, '
        out += f'{"true" if self.__last else "false"}}},\n'
        return out


    def __repr__(self) -> str:
        return str(self)
