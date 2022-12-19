#include "class/hid/hid_device.h"
#include "class/hid/hid.h"
#include "usb_reports.h"

// report description was taken from
uint8_t const hid_report[] = {
    HID_USAGE_PAGE(    HID_USAGE_PAGE_DESKTOP),         // 0x06 0x01
    HID_USAGE     (HID_USAGE_DESKTOP_KEYBOARD),         // 0x09 0x06
    HID_COLLECTION(HID_COLLECTION_APPLICATION),         // 0xA1 0x01
        // Modifiers (LR Shift, LR Alt, LR Ctrl, LR Gui)
        HID_USAGE_PAGE  (HID_USAGE_PAGE_KEYBOARD),      // 0x09 0x07
        HID_LOGICAL_MIN (                      0),      // 0x15 0x00   - not pressed
        HID_LOGICAL_MAX (                      1),      // 0x26 0x01 - pressed
        HID_USAGE_MIN   (   HID_KEY_CONTROL_LEFT),      // 0x19 0xe0
        HID_USAGE_MAX   (      HID_KEY_GUI_RIGHT),      // 0x29 0xe7
        HID_REPORT_COUNT(                      1),      // 0x95 0x01
        HID_REPORT_SIZE (                      8),      // 0x75 0x08
        HID_INPUT       (HID_DATA | HID_VARIABLE | HID_ABSOLUTE),   // 0x81 0x02

        // LEDs (Kana, Compose, ScrollLock, CapsLock, NumLock)
        HID_USAGE_PAGE  (HID_USAGE_PAGE_LED),           // 0x09 0x08
        HID_USAGE_MIN   (                 1),           // 0x19 0x01
        HID_USAGE_MAX   (                 5),           // 0x29 0x05
        HID_REPORT_COUNT(                 1),           // 0x95 0x01
        HID_REPORT_SIZE (                 5),           // 0x75 0x05
        HID_OUTPUT      (HID_DATA | HID_VARIABLE | HID_ABSOLUTE),   // 0x91 0x02
        // LED padding (need to fit information into 1 byte
        HID_REPORT_COUNT(                 1),           // 0x95 0x01
        HID_REPORT_SIZE (                 3),           // 0x75 0x05
        HID_OUTPUT      (      HID_CONSTANT),           // 0x91 0x01

        // Key codes, max 6 pressed keys can be sent
        HID_USAGE_PAGE   (   HID_USAGE_PAGE_KEYBOARD),  // 0x09 0x07
        HID_LOGICAL_MIN  (              HID_KEY_NONE),  // 0x15 0x00   - not pressed
        HID_LOGICAL_MAX_N(      HID_KEY_GUI_RIGHT, 2),  // 0x26 0x00E7 - pressed
        HID_USAGE_MIN    (              HID_KEY_NONE),  // 0x19 0xE0
        HID_USAGE_MAX    (         HID_KEY_GUI_RIGHT),  // 0x29 0xE7
        HID_REPORT_COUNT (                         6),  // 0x95 0x06
        HID_REPORT_SIZE  (                         8),  // 0x75 0x08
        HID_INPUT        (HID_DATA | HID_ARRAY | HID_ABSOLUTE),   // 0x81 0x00

    HID_COLLECTION_END,                             // 0xC0
};

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance) {
    (void) instance;
    return hid_report;
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
        hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
        hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
}

/* usb_reports.c */
