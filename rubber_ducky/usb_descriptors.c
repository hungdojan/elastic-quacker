/**
 * @brief Definition of USB and report description.
 *
 * This file defines functions used in initial exchange information with host (enumeration).
 * Some snippets of code were taken from TinyUSB examples.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file usb_description.c
 * @author Hung Do
 * @date 18/12/2022
 */
#include "tusb.h"
#include "tusb_types.h"
#include "device/usbd.h"

// These makros are taken from TinyUSB example file
// https://github.com/hathach/tinyusb/blob/4bfab30c02279a0530e1a56f4a7c539f2d35a293/examples/device/hid_composite/src/usb_descriptors.c
#define _PID_MAP(itf, n)  ( (CFG_TUD_##itf) << (n) )
#define USB_PID           (0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) | \
                          _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4) )

// device descriptor
tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = 0x01,     // DEVICE constant
    .bcdUSB             = 0x0110,   // USB1.1
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

    // list of vendors found here: http://www.linux-usb.org/usb.ids
    .idVendor           = 0xD0D0,   // vendor's id (must be unique)
    .idProduct          = 0xCAFE,   // product id (must be unique with vendor)
    .bcdDevice          = 0x0100,   // version

    .iManufacturer      = 0x01,     // string index of manufacture name
    .iProduct           = 0x02,     // string index of product name
    .iSerialNumber      = 0x00,

    .bNumConfigurations = 0x01      // number of configuration the device supports
};

uint8_t const * tud_descriptor_device_cb() {
    return (uint8_t const *) &desc_device;
}

uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    // TODO: contains configuration, interface and endpoint descriptors
    return NULL;
}

uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    // TODO:
    return NULL;
}
