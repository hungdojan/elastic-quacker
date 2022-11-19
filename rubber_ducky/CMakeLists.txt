add_executable(rubber_ducky
    main.c
)

target_link_libraries(rubber_ducky pico_stdlib pico_cyw43_arch_none)

pico_add_extra_outputs(rubber_ducky)
