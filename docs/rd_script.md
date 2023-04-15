# RD Script language

`RD script` is a custom language designed to let users easily create the payloads. It is inspired by vim key notations. There are 4 types of keys that the user will come across when creating an RD script:

#### Printable keys
Keys that produces a printable character in ASCII. Just insert them normally to the script.

#### Special keys
Keys that don't produce printable character. These keys needs to be inside special combination scope and start with backslash symbol `\`. The example of usage is `<\enter>` or `<\bs>`.

#### Modifier keys
Ctrl, Alt, Shift and Win/Meta keys.

#### Macro keys
These keys are aliases to another keys. For example the syntax of the special combination starts with `<` and ends with `>` characters. Unfortunately because of that we can't use those *printable keys* inside the special combination scope. That is why there are aliases for them: `lt` for `<` and `gt` for `>`. So instead of `<<>` use `<\lt>`.


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

The list of modifiers, special keys, macro keys and printable keys can be found in [mappings.py](/rd_client/parser/mappings.py) as `MODIFIER_MAP`, `SPECIAL_MAP`, `MACRO_KEYS` and `NORMAL_TO_KEY_MAP`/`SHIFT_TO_NORMAL_MAP` respectively.
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
