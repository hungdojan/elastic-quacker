/**
 * @brief File defines important HID structures and functions.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file usb_reports.c
 * @author Hung Do
 * @date 25/02/2023
 */
#include "class/hid/hid_device.h"
#include "class/hid/hid.h"
#include "keyseqv/key_seqv.h"
#include "pico/cyw43_arch.h"
#include "usb_general.h"
#include "error_state.h"

#define DEBUG_CAPS_LOCK

bool enable_key_seqv = false;

// report description for keyboard
uint8_t const hid_report[] = {
    // TUD_HID_REPORT_DESC_KEYBOARD()
    HID_USAGE_PAGE(    HID_USAGE_PAGE_DESKTOP),         // 0x05 0x01
    HID_USAGE     (HID_USAGE_DESKTOP_KEYBOARD),         // 0x09 0x06
    HID_COLLECTION(HID_COLLECTION_APPLICATION),         // 0xA1 0x01
        // Modifiers (LR Shift, LR Alt, LR Ctrl, LR Gui)
        HID_USAGE_PAGE  (HID_USAGE_PAGE_KEYBOARD),      // 0x05 0x07
        HID_USAGE_MIN   (   HID_KEY_CONTROL_LEFT),      // 0x19 0xe0
        HID_USAGE_MAX   (      HID_KEY_GUI_RIGHT),      // 0x29 0xe7
        HID_LOGICAL_MIN (                      0),      // 0x15 0x00 - not pressed
        HID_LOGICAL_MAX (                      1),      // 0x26 0x01 - pressed
        HID_REPORT_SIZE (                      1),      // 0x75 0x01
        HID_REPORT_COUNT(                      8),      // 0x95 0x08
        HID_INPUT       (HID_DATA | HID_VARIABLE | HID_ABSOLUTE),   // 0x81 0x02

        // Reserved byte
        HID_REPORT_SIZE (                 8),           // 0x75 0x08
        HID_REPORT_COUNT(                 1),           // 0x95 0x01
        HID_INPUT       (      HID_CONSTANT),           // 0x81 0x01

        // LEDs (Kana, Compose, ScrollLock, CapsLock, NumLock)
        HID_USAGE_PAGE  (HID_USAGE_PAGE_LED),           // 0x05 0x08
        HID_USAGE_MIN   (                 1),           // 0x19 0x01
        HID_USAGE_MAX   (                 5),           // 0x29 0x05
        HID_REPORT_SIZE (                 1),           // 0x75 0x01
        HID_REPORT_COUNT(                 5),           // 0x95 0x05
        HID_OUTPUT      (HID_DATA | HID_VARIABLE | HID_ABSOLUTE),   // 0x91 0x02
        // LED padding (need to fit information into 1 byte
        HID_REPORT_COUNT(                 1),           // 0x95 0x01
        HID_REPORT_SIZE (                 3),           // 0x75 0x05
        HID_OUTPUT      (      HID_CONSTANT),           // 0x91 0x01

        // Key codes, max 6 pressed keys can be sent
        HID_USAGE_PAGE   (   HID_USAGE_PAGE_KEYBOARD),  // 0x05 0x07
        HID_LOGICAL_MIN  (              HID_KEY_NONE),  // 0x15 0x00   - not pressed
        HID_LOGICAL_MAX_N(      HID_KEY_GUI_RIGHT, 2),  // 0x26 0x00E7 - pressed
        HID_USAGE_MIN    (              HID_KEY_NONE),  // 0x19 0xE0
        HID_USAGE_MAX_N  (      HID_KEY_GUI_RIGHT, 2),  // 0x29 0x00E7
        HID_REPORT_COUNT (                         6),  // 0x95 0x06
        HID_REPORT_SIZE  (                         8),  // 0x75 0x08
        HID_INPUT        (HID_DATA | HID_ARRAY | HID_ABSOLUTE),   // 0x81 0x00

    HID_COLLECTION_END,                                 // 0xC0
};

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance) {
    (void) instance;
    return hid_report;
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
        hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
        hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    // ignore this request
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
#ifdef DEBUG_CAPS_LOCK
    if (buffer == NULL || bufsize <= 0)
        return;
    if (report_type != HID_REPORT_TYPE_OUTPUT)
        return;

    // reset key sequence when caps lock is turned off
    if (!(buffer[0] & KEYBOARD_LED_CAPSLOCK)) {
        key_seqv_reset_index_counter();
    }
#endif
}

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint8_t len) {
    (void) instance;
    (void) report;
    (void) len;
}

void tud_mount_cb(void) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    key_seqv_reset_index_counter();
    enable_key_seqv = true;
    is_ejected = false;
}

void tud_resume_cb(void) {
    key_seqv_reset_index_counter();
    enable_key_seqv = true;
    is_ejected = false;
}

/* usb_reports.c */
