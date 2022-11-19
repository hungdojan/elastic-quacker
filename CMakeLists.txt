cmake_minimum_required(VERSION 3.12)

set(PICO_BOARD pico_w)
include(pico_sdk_import.cmake)

project(bachelor_thesis C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(rubber_ducky)
add_subdirectory(mass_storage)
