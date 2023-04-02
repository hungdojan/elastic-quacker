add_executable(rubber_ducky
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

target_sources(rubber_ducky PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/usb_descriptors.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb_reports.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb_general.c
    ${CMAKE_CURRENT_SOURCE_DIR}/keyseqv/key_seqv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/msc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rd_server/dhcpserver/dhcpserver.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rd_server/tcp_server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rd_server/request_process.c
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


# include directory with tusb_config.h and lwipopts.h
# so that TinyUSB and lwIP libraries can find it
target_include_directories(rubber_ducky PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}             # tusb_config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/rd_server   # lwipopts.h
    )

target_link_libraries(rubber_ducky PRIVATE
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    tinyusb_device
    tinyusb_board
)

pico_add_extra_outputs(rubber_ducky)
