/**
 * @brief Defines key sequence for Linux systems.
 *
 * This particular set of key sequence opens openai.com page in firefox using terminal.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file key_seqv_linux.c
 * @author Hung Do
 * @date 21/12/2022
 */
#include "key_seqv.h"

/// Index of the key sequence to send
// static size_t key_seqv_index = 0;

/// List of key sequences for (my) Linux system
struct key_seqv_t key_seqvs[] = {
    INITIAL_DELAY,

    {  0, {KEYBOARD_MODIFIER_LEFTALT, 0, {HID_KEY_ENTER, 0,}}, false},
    {500, {0, 0, {0,}}, false},
    {  0, {0, 0, {HID_KEY_F, HID_KEY_I, HID_KEY_R, HID_KEY_E}}, false},
    {  0, {0, 0, {0,}}, false},
    {  0, {0, 0, {HID_KEY_F, HID_KEY_O, HID_KEY_X, HID_KEY_SPACE}}, false},
    {  0, {0, 0, {0,}}, false},
    {  0, {0, 0, {HID_KEY_F, HID_KEY_I, HID_KEY_T, HID_KEY_PERIOD, HID_KEY_V, HID_KEY_U}}, false},
    {  0, {0, 0, {0,}}, false},
    {  0, {0, 0, {HID_KEY_T, HID_KEY_PERIOD, HID_KEY_C, HID_KEY_Z}}, false},
    {  0, {0, 0, {0,}}, false},
    {  0, {0, 0, {HID_KEY_ENTER, 0,}}, false},

    LAST_ITEM,
};

/* key_seqv.c */
