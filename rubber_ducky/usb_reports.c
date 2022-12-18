#include "tusb.h"
#include "class/hid/hid_device.h"
#include "class/hid/hid.h"  // hid_report_type_t

uint8_t const *tub_hid_descriptor_report_cb(uint8_t instance) {
    // TODO:
    return NULL;
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
        hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
        hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
}
