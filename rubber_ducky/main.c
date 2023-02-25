/**
 * @brief Main file with initialization functions.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file main.c
 * @author Hung Do
 * @date 21/12/2022
 */
#include "bsp/board.h"          // board_init
#include "keyseqv/key_seqv.h"   // struct key_seqv_t, key_seqv_get_report
#include "pico/cyw43_arch.h"    // cyw43_arch_init
#include "tusb.h"
#include "usb_general.h"        // enable_key_seqv

/**
 * @brief Send a key sequence using HID report.
 *
 * @return uint32_t Delay time in ms.
 */
uint32_t send_report() {
    struct key_seqv_t key_sqv;
    if (!tud_hid_ready())
        return 0;

    if (!enable_key_seqv || !key_seqv_get_report(&key_sqv)) {
        tud_hid_keyboard_report(0, 0, NULL);
        return 0;
    }

    uint8_t *keycode = key_sqv.report.keycode[0] ?
                       key_sqv.report.keycode : NULL;

    // increase counter when report was successfully sent
    if (tud_hid_keyboard_report(0, key_sqv.report.modifier, keycode)) {
        key_seqv_increase_counter();
        return key_sqv.delay;
    }
    return 0;
}

int main(void) {
    // init board and library
    board_init();
    tusb_init();
    if (cyw43_arch_init())
        return 1;

    // initial booting delay
    for (int i = 0; i < 500000; i++)
        tud_task(); // tinyusb device task

    // main program loop
    uint32_t delay = 0;
    while (1) {
        tud_task(); // tinyusb device task
        delay = send_report();
        sleep_ms(delay);
    }

    return 0;
}

/* main.c */
