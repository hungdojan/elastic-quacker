import enum

class Groups(enum.Enum):
    DELAY_WAIT_ORIGINAL = 0
    DELAY_WAIT_VALUE    = 1
    SPECIAL_ORIGINAL    = 2
    SPECIAL_CONTENT     = 3
    SPECIAL_MODIFIERS   = 4
    SPECIAL_ESCAPE_EN   = 5
    SPECIAL_KEYS_OR_ID  = 6
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
