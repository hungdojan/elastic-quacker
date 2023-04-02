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
│   ├── parser
│   │   ├── error.py
│   │   ├── __init__.py
│   │   ├── key_seqv_parser.py
│   │   ├── key_seqv.py
│   │   ├── mappings.py
│   │   └── regex_groups.py
│   └── payload
│       └── __init__.py
├── README.md
├── requirements.txt
├── rubber_ducky
│   ├── CMakeLists.txt
│   ├── keyseqv
│   │   ├── key_seqv.c
│   │   ├── key_seqv.h
│   │   ├── key_seqv_linux.c
│   │   └── key_seqv_win.c
│   ├── main.c
│   ├── msc.c
│   ├── rd_server
│   │   ├── dhcpserver
│   │   ├── lwipopts.h
│   │   ├── request_process.c
│   │   ├── request_process.h
│   │   ├── tcp_server.c
│   │   └── tcp_server.h
│   ├── tusb_config.h
│   ├── usb_descriptors.c
│   ├── usb_general.c
│   ├── usb_general.h
│   └── usb_reports.c
└── tests
    ├── resources
    │   └── open_fit_vut.txt
    └── test_parser.py
```
