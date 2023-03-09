import enum

class Groups(enum.Enum):
    DELAY_WAIT_ORIGINAL = 0
    DELAY_WAIT_VALUE    = 1
    SPECIAL_ORIGINAL    = 2
    SPECIAL_WHOLE       = 3 # probably for debugging purposes
    SPECIAL_MODIFIERS   = 4
    SPECIAL_ESCAPE_EN   = 5
    SPECIAL_VALUE       = 6 # ids are keys like escape or enter
    COMMENT             = 7
    NORMAL_KEYS         = 8


# TODO: comment
# rules
# <DELAY [num]>
# <[lof_modif]?[escape_en][special_id]>
# <[lof_modif]?[special_key]+>
# normal_key
# # comment
# <#> hash-tag
KEY_SEQV_REGEX = r'(<DELAY (\d+)>)|(<(((?:[a-zA-Z]{1,2}-)*)(\\)?([^<>\s]+))>)|(#.*)|([ -~])'
LINE_REGEX = r'^(<[^<>\s]+>|[ -~\s])*$'
