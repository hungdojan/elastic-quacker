#include "bsp/board.h"  // board_init
#include "keyseqv/key_seqv.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"
#include "usb_reports.h"

uint32_t my_task() {
    struct key_seqv_t key_sqv;
    if (!tud_ready())
        return 0;
    if (!enable_key_seqv || !key_seqv_get_report(&key_sqv)) {
        tud_hid_keyboard_report(0, 0, NULL);
        return 0;
    }

    uint8_t *keycode = key_sqv.report.keycode[0] ?
                       key_sqv.report.keycode : NULL;
    if (tud_hid_keyboard_report(0, key_sqv.report.modifier, keycode)) {
        key_seqv_increase_counter();
        return key_sqv.delay;
    }
    return 0;
}

int main(void) {
    board_init();
    tusb_init();
    if (cyw43_arch_init())
        return 1;

    uint32_t delay = 0;
    while (1) {
        // TODO: my task
        tud_task(); // tinyusb device task
        delay = my_task();
        sleep_ms(delay);
    }

    return 0;
}
