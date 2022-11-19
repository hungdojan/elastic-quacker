add_executable(mass_storage
    main.c
)

target_link_libraries(mass_storage pico_stdlib pico_cyw43_arch_none)

pico_add_extra_outputs(mass_storage)
