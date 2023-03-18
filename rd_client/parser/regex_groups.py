import enum

class Groups(enum.Enum):
    DELAY_WAIT_ORIGINAL = 0
    DELAY_WAIT_VALUE    = 1
    SPECIAL_ORIGINAL    = 2
    SPECIAL_WHOLE       = 3 # probably for debugging purposes
    SPECIAL_HOLD_DELAY  = 4
    SPECIAL_MODIFIERS   = 5
    SPECIAL_ESCAPE_EN   = 6
    SPECIAL_VALUE       = 7 # ids are keys like escape or enter
    COMMENT             = 8
    NORMAL_KEYS         = 9


# rules:
# <DELAY [num]>
# <[HOLD_TIME][lof_modif]?[escape_en][special_id]>
# <[HOLD_TIME][lof_modif]?[special_key]+>
# normal_key
# # comment
# <#> hash-tag
KEY_SEQV_REGEX = r'(<DELAY (\d+)>)|(<((?:(\d+)-)?((?:[a-zA-Z]{1,2}-)*)(\\)?([^<>\s]+))>)|(#.*)|([ -~])'
LINE_REGEX = r'^(<[^<>\s]+>|[ -~\s])*$'
