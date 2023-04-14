/**
 * @brief File containing all important configuration macros.
 *
 * This source code serves as the submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file config.h
 * @author Hung Do
 * @date 06/04/2023
 */
#ifndef _CONFIG_H_
#define _CONFIG_H_

// enables keyboard
#ifndef CFG_TUD_HID
    #define CFG_TUD_HID 1
#endif

// slowing down key presses for more stable performance
// without this delay, the device/host struggles with registering
// modifier key presses (for example shift)
// if you computer still struggles with modifier keys
// try increasing the delay constant
// otherwise decrease the delay constant for faster typing (if needed)
// minimal value is 0
#ifndef KEYPRESS_DELAY_MS
    #define KEYPRESS_DELAY_MS 20
#endif

// enable mass storage emulation
#ifndef CFG_TUD_MSC
    #define CFG_TUD_MSC 1
#endif

// set the size of key sequence array buffer
#ifndef KEY_SEQV_BUFFER_SIZE
    #define KEY_SEQV_BUFFER_SIZE 1001
#endif

// enable communication over wifi
#ifndef WIFI_ENABLE
    #define WIFI_ENABLE 1
#endif

#if WIFI_ENABLE
    #define WIFI_SSID "RubberDucky_WiFi"
    #define WIFI_PSWD "TheCakeIsALie"
    #define _TCP_SERVER_PORT 5000
#endif

// allow the user to rerun the script with caps_lock double press
// the script will start running after caps lock's led turns off
#ifndef DEBUG_CAPS_LOCK
    #define DEBUG_CAPS_LOCK 1
#endif

// tells the rubber ducky device to start running the script after plugging in
// only works when DEBUG_CAPS_LOCK is set to 1
// otherwise this macro will have no use
#ifndef AUTOSTART_AFTER_PLUGIN
    #define AUTOSTART_AFTER_PLUGIN 1
#endif

// Since the USB enumeration process is running in the background
// once the USB device is plugged in the host, we need a way to wait for the
// enumeration to finish. The value stored in this macro HAS NO UNIT meaning
// the value represents the number of ticks of Raspberry's internal clock.

// Feel free to change each value to your liking.
// FIXME: research and implement a way to get rid of this delay workaround
#define _INITIAL_BOOT_DELAY 900000

#endif // _CONFIG_H_
