# Implementation of RubberDucky using Raspberry Pi Pico W
This repository contains source files used in practical part of my bachelor thesis "Implement Rubber Duckies on Available USB Devices and Make a Practical Test".

Author: Hung Do (xdohun00)  
School: Faculty of Information Technologies, BUT  
Year: 2022/2023  

- [Implementation of RubberDucky using Raspberry Pi Pico W](#implementation-of-rubberducky-using-raspberry-pi-pico-w)
  - [Introduction](#introduction)
  - [Requirements](#requirements)
  - [Setting up this project](#setting-up-this-project)
  - [Compile project and upload to the device](#compile-project-and-upload-to-the-device)
  - [RD script parser](#rd-script-parser)
  - [Configuration and RD script language rules](#configuration-and-rd-script-language-rules)
  - [Make commands](#make-commands)
    - [Basic usage](#basic-usage)

## Introduction
TODO:

## Requirements
This project was developed and tested on `5.15.104-2-MANJARO x86_64 GNU/Linux` operating system.

Softwares required to run this project are:
- Python 3.9 and higher
- cmake
- make
- [pico-sdk requirements](https://github.com/raspberrypi/pico-sdk) - Raspberry Pi Pico SDK for development in C

Optionally, you may want to install
- poetry (optional, developed and tested with version 1.4.0)

The installation of the listed softwares will differ depending on the user's operating systems.

## Setting up this project
In order to build this project, user is required to initialized all submodules needed. This set of commands installs the bare minimum that the project needs to run or to develop on. If you want to install everything use command `git submodule update --init --recursive` (optional).
```bash
git clone https://github.com/hungdojan/RubberDucky_BachelorThesis.git
cd RubberDucky_BachelorThesis
git submodule init
git submodule update --init

# initialize pico-sdk submodules
cd pico-sdk
git submodule update --init
```

## Compile project and upload to the device
The project can be compile with a given `Makefile`. Simply run `make` command in the project's root directory. That will create a build directory `build_rd` with lots of new generated files. In there you will find `build_rd/rubber_ducky/rubber_ducky.uf2` binary file that you will copy to your Raspberry Pi Pico device. You can find a tutorial on how to drop UF2 binary onto Raspberry Pi Pico device [here](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries).

You can also compile the project manually. Just create a new build directory and run `cmake .. -DPICO_SDK_PATH=../pico-sdk/` in it. That will create a `Makefile` inside the build directory. Then call `make` command to generate UF2 binary file.

```bash
mkdir build_rd
cd build_rd
cmake .. -DPICO_SDK_PATH=../pico-sdk/
make -j8

# ...or one-liner from the root directory
cmake -H. -B'build_rd' -DPICO_SDK_PATH=pico-sdk/ && make -C'build_rd' -j8
```

The `Makefile` script offers more actions which you can find all of them listed [here](#make-commands).

## RD script parser
Additionally, I created a Python script that converts a custom `RD script` to a series of key presses readable by our Rubber Ducky device. `rd_client` module app currently supports 2 modes:
- **CLI mode**    - Used to convert `RD script` to C source code. Replace the output with `rubber_ducky/
- **Client mode** - Send the transformed `RD script` over TCP socket. Need to be connected to Rubber Ducky Wifi.

The `TUI mode` is not implemented yet but is planned in the future.

You can run Python scripts using Makefile/poetry or Python. No special modules required. There are 8 arguments that you can run the script with. To list all of them run `python -m rd_client -h` or `poetry run app -h` in the project's root directory.

```
$ poetry run app -h
usage: RubberDucky script parser [-h] [--version] [-H IP address] [-i filename] [-l filename] [-n] [-o filename] [-p PORT] [-t] [-v]

options:
  -h, --help                        show this help message and exit
  --version                         show program's version number and exit
  -H IP address, --host IP address  IP address of the RubberDucky device.
  -i filename, --input filename     Source RubberDucky script file.
  -l filename, --log_file filename  Log filename. Defaults to STDERR.
  -n, --network                     Upload script using networking.
  -o filename, --output filename    Generated output filename.
  -p PORT, --port PORT              Application port of the RubberDucky device. Defaults to 5000.
  -t, --tui                         Open program in interactive mode.
  -v, --verbose                     Enable logging.
```

## Configuration and RD script language rules
User is allowed to modify Rubber Ducky's device configuration file `rubber_ducky/config.h`. Check the [configuration documentation](docs/configuration.md) for more detailed information.

`RD script` is a custom language designed to allow user to easily write the payloads. It is inspired by vim key notations. The language supports:
- [x] **single line comments**
- [x] **setting delays** - wait for a defined time period before pressing another keys
- [x] **holding delay** - keys are pressed for a defined time period
- [x] **huge selection of keys to press** - list of them can be found [here]()
- [x] **up to 6 keys + modifiers simultaneously pressed** - allows to run shortcuts
  - doesn't include *special keys*, only one *special key* can be pressed at a time (plan to update this in the future)

You can find more information related to `RD script` language [here](docs/rd_script.md).

```
# example script that opens terminal and list out current directory's content
# Ubuntu's keyboard shortcut for opening terminal is Ctrl+Alt+t
<c-a-t>

# wait for the terminal to open (500 ms)
<DELAY 500>

# run the command
ls<\enter>
```

## Make commands
The given `Makefile` contains 7 useful commands that the user can call. They are all listed below:
- `make` or `make build` - Calls `cmake` and compiles the project in `pico-build` directory. If enabled this command will also generate `compile_commands.json` file.
- `make clean`      - Removes generated files from the project directory.
- `make run_cli`    - Runs a Python script which transform `RD script` file into C source code.
- `make run_client` - Once connected to Rubber Ducky's WiFi, this command can be used to send a new `RD script` to the USB device.
- `make test`       - Runs a Python unit tests and shows the coverage. Requires **poetry**. 
- `make test_show_coverage` - Runs a Python unit tests and shows the coverage in the `firefox`. Requires **poetry** and **firefox**. 

If you use language servers like [ccls](https://github.com/MaskRay/ccls) you can enable `compile_commands.json` generation in the script. Just uncomment the forth line in the `Makefile`:

```
# C project: Bachelor Thesis
BUILD_DIR=./build_rd
CMAKE_MACROS=-DCMAKE_BUILD_TYPE=Debug -DPICO_SDK_PATH=pico-sdk/
#CMAKE_MACROS+=-DCMAKE_EXPORT_COMPILE_COMMANDS=YES   # <<< uncomment this line
...
```

### Basic usage
Here are some example of the use cases:
- Change Rubber Ducky's starting/default script. Replace `make run_cli` with `python -m rd_client -v` if **poetry** is not present on your machine.
```
$ make run_cli > rubber_ducky/keyseqv/key_seqv_script.c
INFO :: ------ Start parsing script ------
<c-a-t><DELAY 500>firefox fit.vut.cz<\enter>
INFO :: Modifiers: [LCTRL, LALT]; Keys: [t]
INFO :: Wait: 500 ms; 
INFO :: Keys: [f, i, r, e]
INFO :: Keys: [f, o, x, space]
INFO :: Keys: [f, i, t, ., v, u]
INFO :: Keys: [t, ., c, z]
INFO :: Keys: [enter]
^D
INFO :: ------- Writing to output -------
INFO :: -------- Writing finished --------
$
$
$ make run_cli < scripts/linux_open_fit_vut_page.txt > rubber_ducky/keyseqv/key_seqv_script.c 
INFO :: ------ Start parsing script ------
INFO :: Modifiers: [LCTRL, LALT]; Keys: [t]
INFO :: Wait: 500 ms; 
INFO :: Keys: [f, i, r, e]
INFO :: Keys: [f, o, x, space]
INFO :: Keys: [f, i, t, ., v, u]
INFO :: Keys: [t, ., c, z]
INFO :: Keys: [enter]
INFO :: ------- Writing to output -------
INFO :: -------- Writing finished --------
```

- Upload script to Rubber Ducky device using client mode. Replace `make run_client` with `python -m rd_client -vn -p 5000 -H 192.168.4.1`. The machine needs to be connected to Rubber Ducky's wifi network. Network's SSID and password can be found in `rubber_ducky/config.h` file. You can change those to your liking.

```
$ cat rubber_ducky/config.h | grep "define WIFI"
    #define WIFI_ENABLE 1
    #define WIFI_SSID "RubberDucky_WiFi"
    #define WIFI_PSWD "TheCakeIsALie"
$ make run_client < scripts/win_trackmania_training01.txt
INFO :: ------ Start parsing script ------
INFO :: Hold: 3350 ms; Keys: [w]
INFO :: Hold: 500 ms; Keys: [d]
INFO :: Hold: 900 ms; Keys: [w, d]
INFO :: Hold: 300 ms; Keys: [w]
INFO :: Hold: 500 ms; Keys: [a]
INFO :: Hold: 800 ms; Keys: [a, w]
INFO :: Hold: 600 ms; Keys: [w]
INFO :: Hold: 500 ms; Keys: [d]
INFO :: Hold: 500 ms; Keys: [w, d]
INFO :: Hold: 1500 ms; Keys: [w]
INFO :: ------ Connecting to host... ------
INFO :: --------- Sending to host ---------
INFO :: Sent - SET_EDITABLE:   [01]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - CLEAR_DATA:     []
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [16 0d 00 00 00 00 1a 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [f4 01 00 00 00 00 07 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [84 03 00 00 00 00 1a 07  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [2c 01 00 00 00 00 1a 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [f4 01 00 00 00 00 04 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [20 03 00 00 00 00 04 1a  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [58 02 00 00 00 00 1a 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [f4 01 00 00 00 00 07 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [f4 01 00 00 00 00 1a 07  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [dc 05 00 00 00 00 1a 00  00 00 00 00 00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - PUSH_DATA:      [00 00 00 00 00 00 00 00  00 00 00 00 01]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - SET_EDITABLE:   [00]
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: Sent - RUN_SEQUENCES:  []
INFO :: Recv - RESPONSE_OK:    [0a 00 00 00]
INFO :: ----- Payload successfully sent -----
```
