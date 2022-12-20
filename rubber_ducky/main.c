#include "bsp/board.h"  // board_init
#include "keyseqv/key_seqv.h"
#include "pico/cyw43_arch.h"
#include "tusb.h"
#include "usb_reports.h"

void my_task() {
    struct key_seqv_t key_sqv;
    if (!tud_ready())
        return;
    if (!enable_key_seqv || !key_seqv_get_report(&key_sqv)) {
        tud_hid_keyboard_report(0, 0, NULL);
        return;
    }
    sleep_ms(key_sqv.wait_before);
    uint8_t *keycode = key_sqv.report.keycode[0] ?
                       key_sqv.report.keycode : NULL;
    if (tud_hid_keyboard_report(0, key_sqv.report.modifier, keycode))
        key_seqv_increase_counter();
}

int main(void) {
    board_init();
    tusb_init();
    if (cyw43_arch_init())
        return 1;

    while (1) {
        // TODO: my task
        tud_task(); // tinyusb device task
        my_task();
    }

    return 0;
}
