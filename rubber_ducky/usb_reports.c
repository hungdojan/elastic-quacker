#include "class/hid/hid_device.h"
#include "class/hid/hid.h"
#include "keyseqv/key_seqv.h"
#include "pico/cyw43_arch.h"
#include "usb_general.h"
#include "error_state.h"

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
#if 0
    // initial check
    if (buffer == NULL || reqlen <= 0)
        return 0;

    // expected only report type INPUT
    if (report_type != HID_REPORT_TYPE_INPUT)
        return 0;

    struct key_seqv_t key_sqv;
    // no other key sequence is needed to be sent
    if (!enable_key_seqv || !key_seqv_get_report(&key_sqv))
        return 0;

    // signalize error state; stop ongoing process
    if (reqlen < 8) {
        enter_error_state(ERR_GET_REPORT_SIZE);
    }
    uint16_t report_size = 8;

    // send a report; turn on board's LED when last item is sent
    sleep_ms(key_sqv.delay);
    memcpy(buffer, &(key_sqv.report), report_size);
    if (!key_sqv.last_item)
        key_seqv_increase_counter();

    return report_size;
#else
    (void) report_type;
    (void) buffer;
    (void) reqlen;
    return 0;
#endif
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
        hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    // ignore this request
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
    if (buffer == NULL || bufsize <= 0)
        return;
    if (report_type != HID_REPORT_TYPE_OUTPUT)
        return;

    // reset key sequence when caps lock is turned off
    if (!(buffer[0] & KEYBOARD_LED_CAPSLOCK)) {
        key_seqv_reset_index_counter();
    }
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
