#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CFG_TUD_HID 1

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
#endif

#ifndef DEBUG_CAPS_LOCK
    #define DEBUG_CAPS_LOCK 0
#endif

#endif // _CONFIG_H_
