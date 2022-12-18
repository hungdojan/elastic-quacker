add_executable(rubber_ducky
    main.c
)

target_sources(rubber_ducky PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb_descriptors.c
    )

# include directory with tusb_config.h so that
# TinyUSB can find it
target_include_directories(rubber_ducky PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(rubber_ducky PUBLIC
    pico_stdlib
    pico_cyw43_arch_none
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(rubber_ducky)
