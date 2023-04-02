#include "usb_general.h"
#include "pico/cyw43_arch.h"    // cyw43_arch_gpio_put
#include "boards/pico_w.h"      // CYW43_WL_GPIO_LED_PIN

// enables rubber ducky scripting
static bool enable_key_seqv = false;

bool get_enable_key_seqv() {
    return enable_key_seqv;
}

void set_enable_key_seqv(bool value) {
    enable_key_seqv = value;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, value);
}

void active_delay(uint32_t ticks) {
    for (uint32_t i = 0; i < ticks; i++) {
        tud_task(); // tinyusb device task
    }
}

/* usb_general.c */
