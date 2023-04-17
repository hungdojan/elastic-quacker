# RD Script language

`RD script` is a custom language designed to let users easily create the payloads. It is inspired by vim key notations. It's parser distinguishes two types of commands/key combinations: *normal typing* and *speical combination*. 
When the user wants the device to type a string (like URL or a command in command line) he/she should use **normal typing**. It consists of [printable keys](#printable-keys) and has not special format. `cmd` produces `Key_C`, `Key_M` and `Key_D` key presses. **Special combinations** on the other hand have a strict rules. The content must be packed inside `<` and `>` symbols. They allow users to press [keys that don't produce a printable key](#special-keys) like `Enter`, `Tab`, `Delete`, and key combinations that contains [modifier keys](#modifier-keys) like `Alt`, `Shift`, `Control` or `Meta`/`Windows key`. The simplification of the *special combination* format is:
```<[how_long_to_hold_this]-[set_of_modifiers]-[special_key_or_set_of_printable_keys]>```. The formal language grammar notation in BNF can be found in [Language Grammar](#language-grammar) section.

## Language Grammar
```
RD-SCRIPT           ::= [COMMENT][RD-SCRIPT]   |
                        [DELAY][RD-SCRIPT]     |
                        [PRINTABLE][RD-SCRIPT] |
                        [SPECIAL-COMBINATION][RD-SCRIPT] |
                        [EOL]

COMMENT             ::= "#" everything after this is ignored

DELAY               ::= <DELAY [DELAY-VALUE]>

DELAY-VALUE         ::= positive whole number

SPECIAL-COMBINATION ::= <[HOLD-VALUE][MODIFIERS][PRINTABLES]> | <[HOLD-VALUE][MODIFIERS][SPECIAL-KEY]>

HOLD-VALUE          ::= positive whole number "-" | ""

MODIFIERS           ::= [MODIFIER] "-" [MODIFIERS] | ""

MODIFIER            ::= modifier short alias

SPECIAL-KEY         ::= "\" [SPECIAL-OR-MACRO]

SPECIAL-OR-MACRO    ::= special key name | macro name

PRINTABLES          ::= [PRINTABLE][PRINTABLES] | ""

PRINTABLE           ::= ASCII printable character
```

There are 4 types of keys that the user will come across when creating an RD script:

### Printable keys
Keys that produce printable characters in ASCII. Just insert them normally to the script.

### Special keys
Keys that don't produce printable character. These keys needs to be inside special combination scope and start with backslash symbol `\`. The example of usage is `<\enter>` or `<\bs>`.

### Modifier keys
Ctrl, Alt, Shift and Win/Meta keys. In the *special combination* they are seperated by `-` delimiter (for example `<m-s-s>` will produce `Meta+Shift+s` combination).

### Macro keys
These keys are aliases to another keys and are treated the same way as [Special keys](#special-keys). For example the syntax of the special combination starts with `<` and ends with `>` characters. Unfortunately because of that we can't use those *printable keys* inside the special combination scope. That is why there are aliases for them: `lt` for `<` and `gt` for `>`. So instead of `<<>` use `<\lt>`.

The list of modifiers, special keys, macro keys and printable keys can be found in [mappings.py](/rd_client/parser/mappings.py) as `MODIFIER_MAP`, `SPECIAL_MAP`, `MACRO_KEYS` and `NORMAL_TO_KEY_MAP`/`SHIFT_TO_NORMAL_MAP` respectively.

## Parser warnings and errors
There are some additional syntax rules that users have to follow:

### Warnings
- A printable key is present multiple times inside *special combination*. This key will be pressed only once. If you want it to be pressed twice or more times create a new *special combination*.
  - `<c-awa>` will produce `Ctrl+a+w` ignoring second `a`. Fix: `<c-aw><c-a>`.
- A modifier key is present multiple times inside *special combination*. This key will be pressed only once.
  - `<c-a-c-p>` will produce `Ctrl+Alt+p` ignoring second `Ctrl`.

### Errors
- Inconsistent use of `Shift` modifier inside *special combination*. You have to create a new *special combination*.
  - `<c-Auto>` - Upper case `a` needs a `Shift` modifier but other keys don't. Fix: `<c-A><c-uto>`.
- Unknown modifier key. Only `a`, `c`, `m`, `s` + left (`l`) and right (`r`) prefixes are supported.
  - `<b-a>` will cause this error since there is no `b` modifier. So will `<ma-a>` since `ma` is not known. But `<la-rc-lm-p>` will pass (`LeftAlt+RightCtrl+LeftMeta+p`).
-  Unknown *special key* or *macro key*. This error is raised when user provides a key name that is not present in [SPECIAL_MAP](https://github.com/hungdojan/RubberDucky_BachelorThesis/blob/main/rd_client/parser/mappings.py#L225) or [MACRO_MAP](https://github.com/hungdojan/RubberDucky_BachelorThesis/blob/main/rd_client/parser/mappings.py#L206).
- There are more than 6 printable keys present in *special combination*. The HID report packet only supports up to 6 simultaneously pressed keys.
  - `<a-longstr>` - `longstr` has 7 keys. Fix: `<a-longst><a-r>`
- `Shift` modifier key must not be present when the *special combination* contains printable keys.
  - `<c-s-p>` - You can't combinane `Shift` modifier with `p` key. Fix: `<c-P>`
- Script contains non-ASCII character. Refrain from using those (even in comments).
  - `# Toto je komentář (this is a comment in Czech)` - `á` character is not in ASCII.

### Common mistakes
- *Special keys* need to start with backslash character. `<enter>` will produce `e+n+t+r` while `<\enter>` will produce `ENTER`.
- If you want to press a backslash key in the *special combination* it must not be at the start of `[PRINTABLES]` section. `<\abc>` will raise an error, `<a\bc>` will produce `a+\+b+c`.

## Examples
```
# type firefox
firefox

# wait 500ms
<DELAY 500>

# press ctrl + alt + delete combination
<c-a-\delete>

# press simultaneously pdf
<pdf>

# hold backspace for 3s
<3000-\backspace>
```
