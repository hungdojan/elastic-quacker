import enum

class Groups(enum.Enum):
    DELAY_ORIGINAL = 0
    DELAY_VALUE    = 1
    SPECIAL_ORIGINAL  = 2
    SPECIAL_CONTENT = 3
    SPECIAL_MODIFIERS = 4
    SPECIAL_KEYS = 5
    NORMAL_KEYS = 6

# TODO: comment
KEY_SEQV_REGEX = r'(<DELAY (\d+)>)|(<(((?:[a-z]{1,2}-)*)([a-z\d]+|[^<>\s]+))>)|([ -~])'
LINE_REGEX = r'^(<[^<>\s]+>|[ -~\s])*$'
