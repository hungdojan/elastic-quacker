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
├── README.md
├── requirements.txt
├── rubber_ducky
│   ├── CMakeLists.txt
│   ├── error_state.c
│   ├── error_state.h
│   ├── keyseqv
│   │   ├── key_seqv.h
│   │   ├── key_seqv.c
│   │   ├── key_seqv_linux.c
│   │   └── key_seqv_win.c
│   ├── main.c
│   ├── msc.c
│   ├── msc.h
│   ├── tusb_config.h
│   ├── usb_descriptors.c
│   ├── usb_reports.c
│   └── usb_reports.h
└── scripts
    ├── parser-cli.py
    └── rd_parser
        ├── __init__.py
        ├── error.py
        ├── key_seqv.py
        ├── key_seqv_parser.py
        ├── mappings.py
        └── regex_groups.py
```
