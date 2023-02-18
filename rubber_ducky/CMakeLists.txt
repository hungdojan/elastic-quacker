add_executable(rubber_ducky
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

target_sources(rubber_ducky PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/usb_descriptors.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb_reports.c
    ${CMAKE_CURRENT_SOURCE_DIR}/error_state.c
    ${CMAKE_CURRENT_SOURCE_DIR}/keyseqv/key_seqv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/msc.c
    )

# choose key sequences base on operating system
# TODO: not working yet
set(OS_NAME "Linux")
if (${OS_NAME} STREQUAL "Win32")
    target_sources(rubber_ducky PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/keyseqv/key_seqv_win.c
        )
else()
    target_sources(rubber_ducky PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/keyseqv/key_seqv_linux.c
        )
endif()


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
