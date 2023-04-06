/**
 * @brief Definition of USB and report description.
 *
 * This file defines functions used in initial exchange information with host (enumeration).
 * Some snippets of code were taken/inspired from TinyUSB examples.
 *
 * This source code serves as the submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file usb_description.c
 * @author Hung Do
 * @date 18/12/2022
 */
#include "class/hid/hid.h"          // tusb_hid_descriptor_hid_t
#include "class/hid/hid_device.h"   // CFG_TUD_HID_EP_BUFSIZE
#include "class/msc/msc.h"          // MSC_SUBCLASS_SCSI, MSC_PROTOCOL_BOT
#include "class/msc/msc_device.h"
#include "common/tusb_types.h"
#include "device/usbd.h"
#include "tusb.h"
#include "usb_general.h"            // _REPORT_LENGTH

#define _CONFIG_LEN 9
#define _HID_LEN (9+9+7)
#if CFG_TUD_MSC
    #define _MSC_LEN (9+7+7)
#else
    #define _MSC_LEN (0)
#endif
#define _CONFIG_TOTAL_LENGTH (_CONFIG_LEN + _HID_LEN + _MSC_LEN)

enum {
    ITF_NUM_HID,
    ITF_NUM_MSC,
    ITF_NUM_TOTAL
};

// device descriptor
tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,     // DEVICE constant
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

tusb_desc_configuration_t const desc_config = {
    .bLength             = 9, // can't use sizeof due to padding
    .bDescriptorType     = TUSB_DESC_CONFIGURATION,
    .wTotalLength        = _CONFIG_TOTAL_LENGTH,
    .bNumInterfaces      = ITF_NUM_TOTAL,
    .bConfigurationValue = 0x01,
    .iConfiguration      = 0x00,
    .bmAttributes        = TU_BIT(7) | TU_BIT(5) | 0x00,    // self-powered
    .bMaxPower           = 50
};

// ===================== HID class =====================
// HID interface
tusb_desc_interface_t const desc_itf_hid = {
    .bLength            = 9, // can't use sizeof due to padding
    .bDescriptorType    = TUSB_DESC_INTERFACE,
    .bInterfaceNumber   = ITF_NUM_HID,
    .bAlternateSetting  = 0x00,
    .bNumEndpoints      = 0x01,
    .bInterfaceClass    = TUSB_CLASS_HID,
    .bInterfaceSubClass = 0x00,
    .bInterfaceProtocol = 0x00,
    .iInterface         = 0x02
};

// HID descriptor
tusb_hid_descriptor_hid_t const desc_hid = {
    .bLength            = 9, // can't use sizeof due to padding
    .bDescriptorType    = HID_DESC_TYPE_HID,
    .bcdHID             = 0x0100,
    .bCountryCode       = 0x00,
    .bNumDescriptors    = 0x01,
    .bReportType        = HID_DESC_TYPE_REPORT,
    .wReportLength      = _REPORT_LENGTH,
};

// HID endpoint
tusb_desc_endpoint_t const desc_ep_hid = {
    .bLength            = 7, // can't use sizeof due to padding
    .bDescriptorType    = TUSB_DESC_ENDPOINT,
    .bEndpointAddress   = 0x81, // IN | INTERRUPT
    .bmAttributes       = {.xfer=TUSB_XFER_INTERRUPT},
    .wMaxPacketSize     = CFG_TUD_HID_EP_BUFSIZE,
    .bInterval          = 5,
};

#if CFG_TUD_MSC
// ===================== MSC class =====================
// MSC interface
tusb_desc_interface_t const desc_itf_msc = {
    .bLength            = 9, // can't use sizeof due to padding
    .bDescriptorType    = TUSB_DESC_INTERFACE,
    .bInterfaceNumber   = ITF_NUM_MSC,
    .bAlternateSetting  = 0x00,
    .bNumEndpoints      = 0x02,
    .bInterfaceClass    = TUSB_CLASS_MSC,
    .bInterfaceSubClass = MSC_SUBCLASS_SCSI,
    .bInterfaceProtocol = MSC_PROTOCOL_BOT,
    .iInterface         = 0x03
};

// MSC endpoint IN
tusb_desc_endpoint_t const desc_ep_msc_in = {
    .bLength            = 7, // can't use sizeof due to padding
    .bDescriptorType    = TUSB_DESC_ENDPOINT,
    .bEndpointAddress   = 0x83, // IN | BULK
    .bmAttributes       = {.xfer=TUSB_XFER_BULK},
    .wMaxPacketSize     = CFG_TUD_MSC_EP_BUFSIZE,
    .bInterval          = 0,
};

// MSC endpoint OUT
tusb_desc_endpoint_t const desc_ep_msc_out = {
    .bLength            = 7, // can't use sizeof due to padding
    .bDescriptorType    = TUSB_DESC_ENDPOINT,
    .bEndpointAddress   = 0x03, // OUT | BULK
    .bmAttributes       = {.xfer=TUSB_XFER_BULK},
    .wMaxPacketSize     = CFG_TUD_MSC_EP_BUFSIZE,
    .bInterval          = 0,
};
#endif // CFG_TUD_MSC
// =====================================================


uint8_t config_buffer[_CONFIG_TOTAL_LENGTH] = { 0, };

static char *string_descriptor[] = {
    "BUT FIT",                      // Manufacture
    "Rubber Ducky",                 // Product
    "Definitely not a keyboard",    // interface HID
    "Just a mass storage"           // interface MSC
};

static uint16_t _desc_buffer[32] = { 0, };

uint8_t const * tud_descriptor_device_cb() {
    return (uint8_t const *) &desc_device;
}

uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    (void) index;
    // combine config, interface, hid and endpoint descriptors together
    size_t offset = 0;
    // Configuration descriptor
    memcpy(config_buffer + offset, (uint8_t *)&desc_config, desc_config.bLength);
    offset += desc_config.bLength;

    // HID Interface descriptor
    memcpy(config_buffer + offset, (uint8_t *)&desc_itf_hid, desc_itf_hid.bLength);
    offset += desc_itf_hid.bLength;

    // HID descriptor
    memcpy(config_buffer + offset, (uint8_t *)&desc_hid, desc_hid.bLength);
    offset += desc_hid.bLength;

    // HID Endpoint descriptor
    memcpy(config_buffer + offset, (uint8_t *)&desc_ep_hid, desc_ep_hid.bLength);
    offset += desc_ep_hid.bLength;
#if CFG_TUD_MSC
    // MSC Interface descriptor
    memcpy(config_buffer + offset, (uint8_t *)&desc_itf_msc, desc_itf_msc.bLength);
    offset += desc_itf_msc.bLength;

    // MSC Output Endpoint descriptor
    memcpy(config_buffer + offset, (uint8_t *)&desc_ep_msc_out, desc_ep_msc_out.bLength);
    offset += desc_ep_msc_out.bLength;

    // MSC Input Endpoint descriptor
    memcpy(config_buffer + offset, (uint8_t *)&desc_ep_msc_in, desc_ep_msc_in.bLength);
#endif // CFG_TUD_MSC

    return (uint8_t const *) config_buffer;
}

uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void) langid;
    uint8_t bLength;

    // to identify language (first index)
    if (index == 0) {
        _desc_buffer[1] = 0x0409;
        bLength = 1;
    } else {
        // other string descriptions
        // ignore indices that are greater than
        // the size of string array "string_descriptor"
        if (index > 2)
            return NULL;

        bLength = strlen(string_descriptor[index-1]);
        // trim access characters
        if (bLength > 32) {
            bLength = 31;
        }

        // convert ASCII to UTF-16
        for (uint8_t i = 0; i < bLength; i++) {
            _desc_buffer[i+1] = string_descriptor[index-1][i];
        }
    }
    _desc_buffer[0] = (TUSB_DESC_STRING << 8) | (bLength * 2 + 2);
    return _desc_buffer;
}

/* usb_descriptors.c */
