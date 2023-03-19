# Implementation of RubberDucky using Raspberry Pi Pico W
This repository contains source files used in practical part of my bachelor thesis
"Implement Rubber Duckies on Available USB Devices and Make a Practival Test".  

Author: Hung Do (xdohun00)  
School: Faculty of Information Technologies, BUT  
Year: 2022/2023  

## Project tree
```
RubberDucky_BachelorThesis
├── CMakeLists.txt
├── Makefile
├── pico-sdk
│   └── ...
├── pyproject.toml
├── rd_client
│   ├── app_modes
│   │   ├── base.py
│   │   ├── cli_mode.py
│   │   ├── __init__.py
│   │   ├── network_mode.py
│   │   ├── tui_mode.py
│   │   └── utils.py
│   ├── __init__.py
│   ├── __main__.py
│   └── parser
│       ├── error.py
│       ├── __init__.py
│       ├── key_seqv_parser.py
│       ├── key_seqv.py
│       ├── mappings.py
│       └── regex_groups.py
├── README.md
├── requirements.txt
├── rubber_ducky
│   ├── CMakeLists.txt
│   ├── error_state.c
│   ├── error_state.h
│   ├── keyseqv
│   │   ├── key_seqv.c
│   │   ├── key_seqv.h
│   │   ├── key_seqv_linux.c
│   │   └── key_seqv_win.c
│   ├── main.c
│   ├── msc.c
│   ├── tusb_config.h
│   ├── usb_descriptors.c
│   ├── usb_general.h
│   └── usb_reports.c
└── tests
    ├── resources
    │   └── open_fit_vutbr.txt
    └── test_parser.py
```
