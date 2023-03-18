import enum

class Modifier(enum.Enum):
    LCTRL = 'KEYBOARD_MODIFIER_LEFTCTRL'
    LSHIFT = 'KEYBOARD_MODIFIER_LEFTSHIFT'
    LALT = 'KEYBOARD_MODIFIER_LEFTALT'
    LMETA = 'KEYBOARD_MODIFIER_LEFTGUI'
    RCTRL = 'KEYBOARD_MODIFIER_RIGHTCTRL'
    RSHIFT = 'KEYBOARD_MODIFIER_RIGHTSHIFT'
    RALT = 'KEYBOARD_MODIFIER_RIGHTALT'
    RMETA = 'KEYBOARD_MODIFIER_RIGHTGUI'

class Key(enum.Enum):
    KEY_NONE = 'HID_KEY_NONE'
    KEY_A = 'HID_KEY_A'
    KEY_B = 'HID_KEY_B'
    KEY_C = 'HID_KEY_C'
    KEY_D = 'HID_KEY_D'
    KEY_E = 'HID_KEY_E'
    KEY_F = 'HID_KEY_F'
    KEY_G = 'HID_KEY_G'
    KEY_H = 'HID_KEY_H'
    KEY_I = 'HID_KEY_I'
    KEY_J = 'HID_KEY_J'
    KEY_K = 'HID_KEY_K'
    KEY_L = 'HID_KEY_L'
    KEY_M = 'HID_KEY_M'
    KEY_N = 'HID_KEY_N'
    KEY_O = 'HID_KEY_O'
    KEY_P = 'HID_KEY_P'
    KEY_Q = 'HID_KEY_Q'
    KEY_R = 'HID_KEY_R'
    KEY_S = 'HID_KEY_S'
    KEY_T = 'HID_KEY_T'
    KEY_U = 'HID_KEY_U'
    KEY_V = 'HID_KEY_V'
    KEY_W = 'HID_KEY_W'
    KEY_X = 'HID_KEY_X'
    KEY_Y = 'HID_KEY_Y'
    KEY_Z = 'HID_KEY_Z'
    KEY_1 = 'HID_KEY_1'
    KEY_2 = 'HID_KEY_2'
    KEY_3 = 'HID_KEY_3'
    KEY_4 = 'HID_KEY_4'
    KEY_5 = 'HID_KEY_5'
    KEY_6 = 'HID_KEY_6'
    KEY_7 = 'HID_KEY_7'
    KEY_8 = 'HID_KEY_8'
    KEY_9 = 'HID_KEY_9'
    KEY_0 = 'HID_KEY_0'
    KEY_ENTER = 'HID_KEY_ENTER'
    KEY_ESCAPE = 'HID_KEY_ESCAPE'
    KEY_BACKSPACE = 'HID_KEY_BACKSPACE'
    KEY_TAB = 'HID_KEY_TAB'
    KEY_SPACE = 'HID_KEY_SPACE'
    KEY_MINUS = 'HID_KEY_MINUS'
    KEY_EQUAL = 'HID_KEY_EQUAL'
    KEY_BRACKET_LEFT = 'HID_KEY_BRACKET_LEFT'
    KEY_BRACKET_RIGHT = 'HID_KEY_BRACKET_RIGHT'
    KEY_BACKSLASH = 'HID_KEY_BACKSLASH'
    KEY_EUROPE_1 = 'HID_KEY_EUROPE_1'
    KEY_SEMICOLON = 'HID_KEY_SEMICOLON'
    KEY_APOSTROPHE = 'HID_KEY_APOSTROPHE'
    KEY_GRAVE = 'HID_KEY_GRAVE'
    KEY_COMMA = 'HID_KEY_COMMA'
    KEY_PERIOD = 'HID_KEY_PERIOD'
    KEY_SLASH = 'HID_KEY_SLASH'
    KEY_CAPS_LOCK = 'HID_KEY_CAPS_LOCK'
    KEY_F1 = 'HID_KEY_F1'
    KEY_F2 = 'HID_KEY_F2'
    KEY_F3 = 'HID_KEY_F3'
    KEY_F4 = 'HID_KEY_F4'
    KEY_F5 = 'HID_KEY_F5'
    KEY_F6 = 'HID_KEY_F6'
    KEY_F7 = 'HID_KEY_F7'
    KEY_F8 = 'HID_KEY_F8'
    KEY_F9 = 'HID_KEY_F9'
    KEY_F10 = 'HID_KEY_F10'
    KEY_F11 = 'HID_KEY_F11'
    KEY_F12 = 'HID_KEY_F12'
    KEY_PRINT_SCREEN = 'HID_KEY_PRINT_SCREEN'
    KEY_SCROLL_LOCK = 'HID_KEY_SCROLL_LOCK'
    KEY_PAUSE = 'HID_KEY_PAUSE'
    KEY_INSERT = 'HID_KEY_INSERT'
    KEY_HOME = 'HID_KEY_HOME'
    KEY_PAGE_UP = 'HID_KEY_PAGE_UP'
    KEY_DELETE = 'HID_KEY_DELETE'
    KEY_END = 'HID_KEY_END'
    KEY_PAGE_DOWN = 'HID_KEY_PAGE_DOWN'
    KEY_ARROW_RIGHT = 'HID_KEY_ARROW_RIGHT'
    KEY_ARROW_LEFT = 'HID_KEY_ARROW_LEFT'
    KEY_ARROW_DOWN = 'HID_KEY_ARROW_DOWN'
    KEY_ARROW_UP = 'HID_KEY_ARROW_UP'
    KEY_NUM_LOCK = 'HID_KEY_NUM_LOCK'
    KEY_KEYPAD_DIVIDE = 'HID_KEY_KEYPAD_DIVIDE'
    KEY_KEYPAD_MULTIPLY = 'HID_KEY_KEYPAD_MULTIPLY'
    KEY_KEYPAD_SUBTRACT = 'HID_KEY_KEYPAD_SUBTRACT'
    KEY_KEYPAD_ADD = 'HID_KEY_KEYPAD_ADD'
    KEY_KEYPAD_ENTER = 'HID_KEY_KEYPAD_ENTER'
    KEY_KEYPAD_1 = 'HID_KEY_KEYPAD_1'
    KEY_KEYPAD_2 = 'HID_KEY_KEYPAD_2'
    KEY_KEYPAD_3 = 'HID_KEY_KEYPAD_3'
    KEY_KEYPAD_4 = 'HID_KEY_KEYPAD_4'
    KEY_KEYPAD_5 = 'HID_KEY_KEYPAD_5'
    KEY_KEYPAD_6 = 'HID_KEY_KEYPAD_6'
    KEY_KEYPAD_7 = 'HID_KEY_KEYPAD_7'
    KEY_KEYPAD_8 = 'HID_KEY_KEYPAD_8'
    KEY_KEYPAD_9 = 'HID_KEY_KEYPAD_9'
    KEY_KEYPAD_0 = 'HID_KEY_KEYPAD_0'
    KEY_KEYPAD_DECIMAL = 'HID_KEY_KEYPAD_DECIMAL'
    KEY_EUROPE_2 = 'HID_KEY_EUROPE_2'
    KEY_APPLICATION = 'HID_KEY_APPLICATION'
    KEY_POWER = 'HID_KEY_POWER'
    KEY_KEYPAD_EQUAL = 'HID_KEY_KEYPAD_EQUAL'
    KEY_F13 = 'HID_KEY_F13'
    KEY_F14 = 'HID_KEY_F14'
    KEY_F15 = 'HID_KEY_F15'
    KEY_F16 = 'HID_KEY_F16'
    KEY_F17 = 'HID_KEY_F17'
    KEY_F18 = 'HID_KEY_F18'
    KEY_F19 = 'HID_KEY_F19'
    KEY_F20 = 'HID_KEY_F20'
    KEY_F21 = 'HID_KEY_F21'
    KEY_F22 = 'HID_KEY_F22'
    KEY_F23 = 'HID_KEY_F23'
    KEY_F24 = 'HID_KEY_F24'
    KEY_EXECUTE = 'HID_KEY_EXECUTE'
    KEY_HELP = 'HID_KEY_HELP'
    KEY_MENU = 'HID_KEY_MENU'
    KEY_SELECT = 'HID_KEY_SELECT'
    KEY_STOP = 'HID_KEY_STOP'
    KEY_AGAIN = 'HID_KEY_AGAIN'
    KEY_UNDO = 'HID_KEY_UNDO'
    KEY_CUT = 'HID_KEY_CUT'
    KEY_COPY = 'HID_KEY_COPY'
    KEY_PASTE = 'HID_KEY_PASTE'
    KEY_FIND = 'HID_KEY_FIND'
    KEY_MUTE = 'HID_KEY_MUTE'
    KEY_VOLUME_UP = 'HID_KEY_VOLUME_UP'
    KEY_VOLUME_DOWN = 'HID_KEY_VOLUME_DOWN'
    KEY_LOCKING_CAPS_LOCK = 'HID_KEY_LOCKING_CAPS_LOCK'
    KEY_LOCKING_NUM_LOCK = 'HID_KEY_LOCKING_NUM_LOCK'
    KEY_LOCKING_SCROLL_LOCK = 'HID_KEY_LOCKING_SCROLL_LOCK'
    KEY_KEYPAD_COMMA = 'HID_KEY_KEYPAD_COMMA'
    KEY_KEYPAD_EQUAL_SIGN = 'HID_KEY_KEYPAD_EQUAL_SIGN'
    KEY_KANJI1 = 'HID_KEY_KANJI1'
    KEY_KANJI2 = 'HID_KEY_KANJI2'
    KEY_KANJI3 = 'HID_KEY_KANJI3'
    KEY_KANJI4 = 'HID_KEY_KANJI4'
    KEY_KANJI5 = 'HID_KEY_KANJI5'
    KEY_KANJI6 = 'HID_KEY_KANJI6'
    KEY_KANJI7 = 'HID_KEY_KANJI7'
    KEY_KANJI8 = 'HID_KEY_KANJI8'
    KEY_KANJI9 = 'HID_KEY_KANJI9'
    KEY_LANG1 = 'HID_KEY_LANG1'
    KEY_LANG2 = 'HID_KEY_LANG2'
    KEY_LANG3 = 'HID_KEY_LANG3'
    KEY_LANG4 = 'HID_KEY_LANG4'
    KEY_LANG5 = 'HID_KEY_LANG5'
    KEY_LANG6 = 'HID_KEY_LANG6'
    KEY_LANG7 = 'HID_KEY_LANG7'
    KEY_LANG8 = 'HID_KEY_LANG8'
    KEY_LANG9 = 'HID_KEY_LANG9'
    KEY_ALTERNATE_ERASE = 'HID_KEY_ALTERNATE_ERASE'
    KEY_SYSREQ_ATTENTION = 'HID_KEY_SYSREQ_ATTENTION'
    KEY_CANCEL = 'HID_KEY_CANCEL'
    KEY_CLEAR = 'HID_KEY_CLEAR'
    KEY_PRIOR = 'HID_KEY_PRIOR'
    KEY_RETURN = 'HID_KEY_RETURN'
    KEY_SEPARATOR = 'HID_KEY_SEPARATOR'
    KEY_OUT = 'HID_KEY_OUT'
    KEY_OPER = 'HID_KEY_OPER'
    KEY_CLEAR_AGAIN = 'HID_KEY_CLEAR_AGAIN'
    KEY_CRSEL_PROPS = 'HID_KEY_CRSEL_PROPS'
    KEY_EXSEL = 'HID_KEY_EXSEL'
    KEY_CONTROL_LEFT = 'HID_KEY_CONTROL_LEFT'
    KEY_SHIFT_LEFT = 'HID_KEY_SHIFT_LEFT'
    KEY_ALT_LEFT = 'HID_KEY_ALT_LEFT'
    KEY_GUI_LEFT = 'HID_KEY_GUI_LEFT'
    KEY_CONTROL_RIGHT = 'HID_KEY_CONTROL_RIGHT'
    KEY_SHIFT_RIGHT = 'HID_KEY_SHIFT_RIGHT'
    KEY_ALT_RIGHT = 'HID_KEY_ALT_RIGHT'
    KEY_GUI_RIGHT = 'HID_KEY_GUI_RIGHT'


# mapping modifier's name to values
MODIFIER_MAP = {
    'c':  Modifier.LCTRL,
    's':  Modifier.LSHIFT,
    'a':  Modifier.LALT,
    'm':  Modifier.LMETA,
    'lc': Modifier.LCTRL,
    'ls': Modifier.LSHIFT,
    'la': Modifier.LALT,
    'lm': Modifier.LMETA,
    'rc': Modifier.RCTRL,
    'rs': Modifier.RSHIFT,
    'ra': Modifier.RALT,
    'rm': Modifier.RMETA,
}

# < and > symbols have a role in this script's language
# user cannot use them in the special sequence and is required
# to use their unique name
# e. g.: to press the combination a-s-., write <a-gt>; <a->> is syntax error
MACRO_KEYS = {
    'lt': (Modifier.LSHIFT, Key.KEY_COMMA),
    'gt': (Modifier.LSHIFT, Key.KEY_PERIOD)
}

# list of special key names
# these keys don't produce a printable character when typing
SPECIAL_MAP = {
    'enter': Key.KEY_ENTER,
    'escape': Key.KEY_ESCAPE,
    'esc': Key.KEY_ESCAPE,
    'backspace': Key.KEY_BACKSPACE,
    'bs': Key.KEY_BACKSPACE,
    'tab': Key.KEY_TAB,
    'space': Key.KEY_SPACE,
    'caps_lock': Key.KEY_CAPS_LOCK,
    'f1': Key.KEY_F1,
    'f2': Key.KEY_F2,
    'f3': Key.KEY_F3,
    'f4': Key.KEY_F4,
    'f5': Key.KEY_F5,
    'f6': Key.KEY_F6,
    'f7': Key.KEY_F7,
    'f8': Key.KEY_F8,
    'f9': Key.KEY_F9,
    'f10': Key.KEY_F10,
    'f11': Key.KEY_F11,
    'f12': Key.KEY_F12,
    'print_screen': Key.KEY_PRINT_SCREEN,
    'scroll_lock': Key.KEY_SCROLL_LOCK,
    'pause': Key.KEY_PAUSE,
    'insert': Key.KEY_INSERT,
    'home': Key.KEY_HOME,
    'page_up': Key.KEY_PAGE_UP,
    'delete': Key.KEY_DELETE,
    'end': Key.KEY_END,
    'page_down': Key.KEY_PAGE_DOWN,
    'arrow_right': Key.KEY_ARROW_RIGHT,
    'arrow_left': Key.KEY_ARROW_LEFT,
    'arrow_down': Key.KEY_ARROW_DOWN,
    'arrow_up': Key.KEY_ARROW_UP,
    'num_lock': Key.KEY_NUM_LOCK,
    'num_divide': Key.KEY_KEYPAD_DIVIDE,
    'num_multiply': Key.KEY_KEYPAD_MULTIPLY,
    'num_subtract': Key.KEY_KEYPAD_SUBTRACT,
    'num_add': Key.KEY_KEYPAD_ADD,
    'num_enter': Key.KEY_KEYPAD_ENTER,
    'num1': Key.KEY_KEYPAD_1,
    'num2': Key.KEY_KEYPAD_2,
    'num3': Key.KEY_KEYPAD_3,
    'num4': Key.KEY_KEYPAD_4,
    'num5': Key.KEY_KEYPAD_5,
    'num6': Key.KEY_KEYPAD_6,
    'num7': Key.KEY_KEYPAD_7,
    'num8': Key.KEY_KEYPAD_8,
    'num9': Key.KEY_KEYPAD_9,
    'num0': Key.KEY_KEYPAD_0,
    'num_1': Key.KEY_KEYPAD_1,
    'num_2': Key.KEY_KEYPAD_2,
    'num_3': Key.KEY_KEYPAD_3,
    'num_4': Key.KEY_KEYPAD_4,
    'num_5': Key.KEY_KEYPAD_5,
    'num_6': Key.KEY_KEYPAD_6,
    'num_7': Key.KEY_KEYPAD_7,
    'num_8': Key.KEY_KEYPAD_8,
    'num_9': Key.KEY_KEYPAD_9,
    'num_0': Key.KEY_KEYPAD_0,
    'num_decimal': Key.KEY_KEYPAD_DECIMAL,
    'shift_left': Key.KEY_SHIFT_LEFT,
    'alt_left': Key.KEY_ALT_LEFT,
    'gui_left': Key.KEY_GUI_LEFT,
    'control_right': Key.KEY_CONTROL_RIGHT,
    'shift_right': Key.KEY_SHIFT_RIGHT,
    'alt_right': Key.KEY_ALT_RIGHT,
    'gui_right': Key.KEY_GUI_RIGHT,

    # special keys that are usually not on the keyboard
    'europe_1': Key.KEY_EUROPE_1,
    'europe_2': Key.KEY_EUROPE_2,
    'application': Key.KEY_APPLICATION,
    'power': Key.KEY_POWER,
    'num_equal': Key.KEY_KEYPAD_EQUAL,
    'f13': Key.KEY_F13,
    'f14': Key.KEY_F14,
    'f15': Key.KEY_F15,
    'f16': Key.KEY_F16,
    'f17': Key.KEY_F17,
    'f18': Key.KEY_F18,
    'f19': Key.KEY_F19,
    'f20': Key.KEY_F20,
    'f21': Key.KEY_F21,
    'f22': Key.KEY_F22,
    'f23': Key.KEY_F23,
    'f24': Key.KEY_F24,
    'execute': Key.KEY_EXECUTE,
    'help': Key.KEY_HELP,
    'menu': Key.KEY_MENU,
    'select': Key.KEY_SELECT,
    'stop': Key.KEY_STOP,
    'again': Key.KEY_AGAIN,
    'undo': Key.KEY_UNDO,
    'cut': Key.KEY_CUT,
    'copy': Key.KEY_COPY,
    'paste': Key.KEY_PASTE,
    'find': Key.KEY_FIND,
    'mute': Key.KEY_MUTE,
    'volume_up': Key.KEY_VOLUME_UP,
    'volume_down': Key.KEY_VOLUME_DOWN,
    'locking_caps_lock': Key.KEY_LOCKING_CAPS_LOCK,
    'locking_num_lock': Key.KEY_LOCKING_NUM_LOCK,
    'locking_scroll_lock': Key.KEY_LOCKING_SCROLL_LOCK,
    'keypad_comma': Key.KEY_KEYPAD_COMMA,
    'keypad_equal_sign': Key.KEY_KEYPAD_EQUAL_SIGN,
    'kanji1': Key.KEY_KANJI1,
    'kanji2': Key.KEY_KANJI2,
    'kanji3': Key.KEY_KANJI3,
    'kanji4': Key.KEY_KANJI4,
    'kanji5': Key.KEY_KANJI5,
    'kanji6': Key.KEY_KANJI6,
    'kanji7': Key.KEY_KANJI7,
    'kanji8': Key.KEY_KANJI8,
    'kanji9': Key.KEY_KANJI9,
    'lang1': Key.KEY_LANG1,
    'lang2': Key.KEY_LANG2,
    'lang3': Key.KEY_LANG3,
    'lang4': Key.KEY_LANG4,
    'lang5': Key.KEY_LANG5,
    'lang6': Key.KEY_LANG6,
    'lang7': Key.KEY_LANG7,
    'lang8': Key.KEY_LANG8,
    'lang9': Key.KEY_LANG9,
    'alternate_erase': Key.KEY_ALTERNATE_ERASE,
    'sysreq_attention': Key.KEY_SYSREQ_ATTENTION,
    'cancel': Key.KEY_CANCEL,
    'clear': Key.KEY_CLEAR,
    'prior': Key.KEY_PRIOR,
    'return': Key.KEY_RETURN,
    'separator': Key.KEY_SEPARATOR,
    'out': Key.KEY_OUT,
    'oper': Key.KEY_OPER,
    'clear_again': Key.KEY_CLEAR_AGAIN,
    'crsel_props': Key.KEY_CRSEL_PROPS,
    'exsel': Key.KEY_EXSEL,
}

# all the keys that produces a printable character when typing.
NORMAL_TO_KEY_MAP = {
    'a': Key.KEY_A,
    'b': Key.KEY_B,
    'c': Key.KEY_C,
    'd': Key.KEY_D,
    'e': Key.KEY_E,
    'f': Key.KEY_F,
    'g': Key.KEY_G,
    'h': Key.KEY_H,
    'i': Key.KEY_I,
    'j': Key.KEY_J,
    'k': Key.KEY_K,
    'l': Key.KEY_L,
    'm': Key.KEY_M,
    'n': Key.KEY_N,
    'o': Key.KEY_O,
    'p': Key.KEY_P,
    'q': Key.KEY_Q,
    'r': Key.KEY_R,
    's': Key.KEY_S,
    't': Key.KEY_T,
    'u': Key.KEY_U,
    'v': Key.KEY_V,
    'w': Key.KEY_W,
    'x': Key.KEY_X,
    'y': Key.KEY_Y,
    'z': Key.KEY_Z,
    '1': Key.KEY_1,
    '2': Key.KEY_2,
    '3': Key.KEY_3,
    '4': Key.KEY_4,
    '5': Key.KEY_5,
    '6': Key.KEY_6,
    '7': Key.KEY_7,
    '8': Key.KEY_8,
    '9': Key.KEY_9,
    '0': Key.KEY_0,
    ' ': Key.KEY_SPACE,
    '-': Key.KEY_MINUS,
    '=': Key.KEY_EQUAL,
    '[': Key.KEY_BRACKET_LEFT,
    ']': Key.KEY_BRACKET_RIGHT,
    '\\': Key.KEY_BACKSLASH,
    ';': Key.KEY_SEMICOLON,
    '\'': Key.KEY_APOSTROPHE,
    '`': Key.KEY_GRAVE,
    ',': Key.KEY_COMMA,
    '.': Key.KEY_PERIOD,
    '/': Key.KEY_SLASH
}


# list of characters that can be typed only with shift modifier toggled
SHIFT_TO_NORMAL_MAP = {
    "~": "`",
    "!": "1",
    "@": "2",
    "#": "3",
    "$": "4",
    "%": "5",
    "^": "6",
    "&": "7",
    "*": "8",
    "(": "9",
    ")": "0",
    "_": "-",
    "+": "=",
    "|": "\\",
    "{": "[",
    "}": "]",
    ":": ";",
    '"': "'",
    "<": ",",
    ">": ".",
    "?": "/",
}

# list of backwards mapping used in debugging
MAPPING_KEYS = list(SPECIAL_MAP.keys()) + list(NORMAL_TO_KEY_MAP.keys())
MAPPING_VALUES = list(SPECIAL_MAP.values()) + list(NORMAL_TO_KEY_MAP.values())

# index of modifiers
MODIFIER_INDEX_MAP = (
    Modifier.LCTRL,
    Modifier.LSHIFT,
    Modifier.LALT,
    Modifier.LMETA,
    Modifier.RCTRL,
    Modifier.RSHIFT,
    Modifier.RALT,
    Modifier.RMETA,
)

# hex code of each key
KEY_TO_VALUE_MAP = {
    Key.KEY_NONE                :0x00,
    Key.KEY_A                   :0x04,
    Key.KEY_B                   :0x05,
    Key.KEY_C                   :0x06,
    Key.KEY_D                   :0x07,
    Key.KEY_E                   :0x08,
    Key.KEY_F                   :0x09,
    Key.KEY_G                   :0x0A,
    Key.KEY_H                   :0x0B,
    Key.KEY_I                   :0x0C,
    Key.KEY_J                   :0x0D,
    Key.KEY_K                   :0x0E,
    Key.KEY_L                   :0x0F,
    Key.KEY_M                   :0x10,
    Key.KEY_N                   :0x11,
    Key.KEY_O                   :0x12,
    Key.KEY_P                   :0x13,
    Key.KEY_Q                   :0x14,
    Key.KEY_R                   :0x15,
    Key.KEY_S                   :0x16,
    Key.KEY_T                   :0x17,
    Key.KEY_U                   :0x18,
    Key.KEY_V                   :0x19,
    Key.KEY_W                   :0x1A,
    Key.KEY_X                   :0x1B,
    Key.KEY_Y                   :0x1C,
    Key.KEY_Z                   :0x1D,
    Key.KEY_1                   :0x1E,
    Key.KEY_2                   :0x1F,
    Key.KEY_3                   :0x20,
    Key.KEY_4                   :0x21,
    Key.KEY_5                   :0x22,
    Key.KEY_6                   :0x23,
    Key.KEY_7                   :0x24,
    Key.KEY_8                   :0x25,
    Key.KEY_9                   :0x26,
    Key.KEY_0                   :0x27,
    Key.KEY_ENTER               :0x28,
    Key.KEY_ESCAPE              :0x29,
    Key.KEY_BACKSPACE           :0x2A,
    Key.KEY_TAB                 :0x2B,
    Key.KEY_SPACE               :0x2C,
    Key.KEY_MINUS               :0x2D,
    Key.KEY_EQUAL               :0x2E,
    Key.KEY_BRACKET_LEFT        :0x2F,
    Key.KEY_BRACKET_RIGHT       :0x30,
    Key.KEY_BACKSLASH           :0x31,
    Key.KEY_EUROPE_1            :0x32,
    Key.KEY_SEMICOLON           :0x33,
    Key.KEY_APOSTROPHE          :0x34,
    Key.KEY_GRAVE               :0x35,
    Key.KEY_COMMA               :0x36,
    Key.KEY_PERIOD              :0x37,
    Key.KEY_SLASH               :0x38,
    Key.KEY_CAPS_LOCK           :0x39,
    Key.KEY_F1                  :0x3A,
    Key.KEY_F2                  :0x3B,
    Key.KEY_F3                  :0x3C,
    Key.KEY_F4                  :0x3D,
    Key.KEY_F5                  :0x3E,
    Key.KEY_F6                  :0x3F,
    Key.KEY_F7                  :0x40,
    Key.KEY_F8                  :0x41,
    Key.KEY_F9                  :0x42,
    Key.KEY_F10                 :0x43,
    Key.KEY_F11                 :0x44,
    Key.KEY_F12                 :0x45,
    Key.KEY_PRINT_SCREEN        :0x46,
    Key.KEY_SCROLL_LOCK         :0x47,
    Key.KEY_PAUSE               :0x48,
    Key.KEY_INSERT              :0x49,
    Key.KEY_HOME                :0x4A,
    Key.KEY_PAGE_UP             :0x4B,
    Key.KEY_DELETE              :0x4C,
    Key.KEY_END                 :0x4D,
    Key.KEY_PAGE_DOWN           :0x4E,
    Key.KEY_ARROW_RIGHT         :0x4F,
    Key.KEY_ARROW_LEFT          :0x50,
    Key.KEY_ARROW_DOWN          :0x51,
    Key.KEY_ARROW_UP            :0x52,
    Key.KEY_NUM_LOCK            :0x53,
    Key.KEY_KEYPAD_DIVIDE       :0x54,
    Key.KEY_KEYPAD_MULTIPLY     :0x55,
    Key.KEY_KEYPAD_SUBTRACT     :0x56,
    Key.KEY_KEYPAD_ADD          :0x57,
    Key.KEY_KEYPAD_ENTER        :0x58,
    Key.KEY_KEYPAD_1            :0x59,
    Key.KEY_KEYPAD_2            :0x5A,
    Key.KEY_KEYPAD_3            :0x5B,
    Key.KEY_KEYPAD_4            :0x5C,
    Key.KEY_KEYPAD_5            :0x5D,
    Key.KEY_KEYPAD_6            :0x5E,
    Key.KEY_KEYPAD_7            :0x5F,
    Key.KEY_KEYPAD_8            :0x60,
    Key.KEY_KEYPAD_9            :0x61,
    Key.KEY_KEYPAD_0            :0x62,
    Key.KEY_KEYPAD_DECIMAL      :0x63,
    Key.KEY_EUROPE_2            :0x64,
    Key.KEY_APPLICATION         :0x65,
    Key.KEY_POWER               :0x66,
    Key.KEY_KEYPAD_EQUAL        :0x67,
    Key.KEY_F13                 :0x68,
    Key.KEY_F14                 :0x69,
    Key.KEY_F15                 :0x6A,
    Key.KEY_F16                 :0x6B,
    Key.KEY_F17                 :0x6C,
    Key.KEY_F18                 :0x6D,
    Key.KEY_F19                 :0x6E,
    Key.KEY_F20                 :0x6F,
    Key.KEY_F21                 :0x70,
    Key.KEY_F22                 :0x71,
    Key.KEY_F23                 :0x72,
    Key.KEY_F24                 :0x73,
    Key.KEY_EXECUTE             :0x74,
    Key.KEY_HELP                :0x75,
    Key.KEY_MENU                :0x76,
    Key.KEY_SELECT              :0x77,
    Key.KEY_STOP                :0x78,
    Key.KEY_AGAIN               :0x79,
    Key.KEY_UNDO                :0x7A,
    Key.KEY_CUT                 :0x7B,
    Key.KEY_COPY                :0x7C,
    Key.KEY_PASTE               :0x7D,
    Key.KEY_FIND                :0x7E,
    Key.KEY_MUTE                :0x7F,
    Key.KEY_VOLUME_UP           :0x80,
    Key.KEY_VOLUME_DOWN         :0x81,
    Key.KEY_LOCKING_CAPS_LOCK   :0x82,
    Key.KEY_LOCKING_NUM_LOCK    :0x83,
    Key.KEY_LOCKING_SCROLL_LOCK :0x84,
    Key.KEY_KEYPAD_COMMA        :0x85,
    Key.KEY_KEYPAD_EQUAL_SIGN   :0x86,
    Key.KEY_KANJI1              :0x87,
    Key.KEY_KANJI2              :0x88,
    Key.KEY_KANJI3              :0x89,
    Key.KEY_KANJI4              :0x8A,
    Key.KEY_KANJI5              :0x8B,
    Key.KEY_KANJI6              :0x8C,
    Key.KEY_KANJI7              :0x8D,
    Key.KEY_KANJI8              :0x8E,
    Key.KEY_KANJI9              :0x8F,
    Key.KEY_LANG1               :0x90,
    Key.KEY_LANG2               :0x91,
    Key.KEY_LANG3               :0x92,
    Key.KEY_LANG4               :0x93,
    Key.KEY_LANG5               :0x94,
    Key.KEY_LANG6               :0x95,
    Key.KEY_LANG7               :0x96,
    Key.KEY_LANG8               :0x97,
    Key.KEY_LANG9               :0x98,
    Key.KEY_ALTERNATE_ERASE     :0x99,
    Key.KEY_SYSREQ_ATTENTION    :0x9A,
    Key.KEY_CANCEL              :0x9B,
    Key.KEY_CLEAR               :0x9C,
    Key.KEY_PRIOR               :0x9D,
    Key.KEY_RETURN              :0x9E,
    Key.KEY_SEPARATOR           :0x9F,
    Key.KEY_OUT                 :0xA0,
    Key.KEY_OPER                :0xA1,
    Key.KEY_CLEAR_AGAIN         :0xA2,
    Key.KEY_CRSEL_PROPS         :0xA3,
    Key.KEY_EXSEL               :0xA4,
    Key.KEY_CONTROL_LEFT        :0xE0,
    Key.KEY_SHIFT_LEFT          :0xE1,
    Key.KEY_ALT_LEFT            :0xE2,
    Key.KEY_GUI_LEFT            :0xE3,
    Key.KEY_CONTROL_RIGHT       :0xE4,
    Key.KEY_SHIFT_RIGHT         :0xE5,
    Key.KEY_ALT_RIGHT           :0xE6,
    Key.KEY_GUI_RIGHT           :0xE7,
}
