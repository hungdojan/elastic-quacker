# Typing test

This file briefly describes how I tested the typing speed and accuracy of the device.

## Requirements

- [tt](https://github.com/lemnos/tt)
- Linux operating system (I run these tests on Fedora)

## Testing

Change `KEYPRESS_DELAY_MS` value in `rubber_ducky/config.h` to your liking. You can either statically compile the test key sequences or upload them via Wi-Fi.
The testing itself can be automated using `xdotool` or `ydotool` (depending if your system supports X11).
If you intend to run multiple tests at once, I recommend you this configuration:
```
DEBUG_CAPS_LOCK 1
AUTOSTART_AFTER_PLUGIN 0
```

#### Compilation

Choose between `a)` and `b)` option for generating the payload.

```sh
# preps: 
cd [project_root_directory]
# edit rubber_ducky/config.h with chosen editor
$EDITOR rubber_ducky/config.h

# a) generate the script with
# make run_cli < [path_to_payload_script] > rubber_ducky/keyseqv/key_seqv_script.c
make
# move u2f file to Raspberry Pi Pico

# b) send via Wi-Fi
# make run_client < [path_to_payload_script]
```

#### With xdotool
```
# run 20 tests
for i in {1..20}; do \
    xdotool key Caps_Lock; \
    xdotool key Caps_Lock; \
    cat [path_to_custom_text] | tt -oneshot -noresult -csv >> [output_csv_file]; \
    done
# see the results
```

#### With ydotool
```
# run 20 tests
for i in {1..20}; do \
    ydotool key 58:1 58:0; \
    ydotool key 58:1 58:0; \
    cat [path_to_custom_text] | tt -oneshot -noresult -csv >> [output_csv_file]; \
    done
# see the results
```
