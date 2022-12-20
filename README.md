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
├── mass_storage
│   ├── CMakeLists.txt
│   └── main.c
├── pico-sdk
│   └── ...
├── README.md
└── rubber_ducky
    ├── CMakeLists.txt
    ├── error_state.c
    ├── error_state.h
    ├── keyseqv
    │   ├── key_seqv.h
    │   ├── key_seqv_linux.c
    │   └── key_seqv_win.c
    ├── main.c
    ├── tusb_config.h
    ├── usb_descriptors.c
    ├── usb_reports.c
    └── usb_reports.h
```
