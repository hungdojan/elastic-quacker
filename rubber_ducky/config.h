/**
 * @brief File containing all important configuration macros.
 *
 * This source code serves as the submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Prictical Test"
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

// enable mass storage simulation
#ifndef CFG_TUD_MSC
    #define CFG_TUD_MSC 1
#endif

// set the size of key sequence array buffer
#ifndef KEY_SEQV_BUFFER_SIZE
    #define KEY_SEQV_BUFFER_SIZE 1001
#endif

// enable communication over wifipicow_test
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
    #define AUTOSTART_AFTER_PLUGIN 0
#endif

#endif // _CONFIG_H_
