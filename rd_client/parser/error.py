class ErrorCode:
    NO_ERROR=0
    INPUT_FILE_NOT_FOUND=1
    OUTPUT_FILE_NOT_FOUND=2
    NON_ASCII_CHARACTER=3


class ParserError(Exception):
    """Base class for all rd_parser exceptions."""
    pass


class NonReadableCharacterError(ParserError):
    """Whole line doesn't pass line regex test."""
    pass


class SpecialSequenceShiftToggleError(ParserError):
    """Special sequence has inconsistent use of shift modifier."""
    pass


class UnknownModifierError(ParserError):
    """Special sequence includes unknown modifier."""
    pass


class UndefinedSpecialKeyNameError(ParserError):
    """Given special key name was not found."""
    pass


class KeySequenceSizeExceededError(ParserError):
    """User exceeded maximum number of keys that can be pressed at the same time."""
    pass


class ShiftToggleWithPrintableKeysError(ParserError):
    """Cannot combine shift modifier in special sequence together with normal keys."""
    pass
