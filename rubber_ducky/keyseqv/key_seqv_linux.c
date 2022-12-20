#include "key_seqv.h"

static size_t key_seqv_index = 0;

// key sequences for Linux systems
static const struct key_seqv_t key_seqvs[] = {
    // {  0, {0, 0, {HID_KEY_CAPS_LOCK, 0,}}, false},
    {  0, {KEYBOARD_MODIFIER_LEFTALT, 0, {HID_KEY_ENTER, 0,}}, false},
    {500, {0, 0, {0,}}, false},
    {  0, {KEYBOARD_MODIFIER_LEFTSHIFT, 0, {HID_KEY_F, HID_KEY_I, HID_KEY_R, HID_KEY_E}}, false},
    {  0, {0, 0, {0,}}, false},
    {  0, {KEYBOARD_MODIFIER_LEFTSHIFT, 0, {HID_KEY_F, HID_KEY_O, HID_KEY_X, HID_KEY_SPACE}}, false},
    {  0, {0, 0, {0,}}, false},
    {  0, {KEYBOARD_MODIFIER_LEFTSHIFT, 0, {HID_KEY_O, HID_KEY_P, HID_KEY_E, HID_KEY_N, HID_KEY_A, HID_KEY_I}}, false},
    {  0, {0, 0, {0,}}, false},
    {  0, {0, 0, {HID_KEY_PERIOD}}, false},
    {  0, {KEYBOARD_MODIFIER_LEFTSHIFT, 0, {HID_KEY_C, HID_KEY_O, HID_KEY_M}}, false},
    {  0, {0, 0, {0,}}, false},
    {  0, {KEYBOARD_MODIFIER_LEFTSHIFT, 0, {HID_KEY_ENTER, 0,}}, false},
    {  0, {0, 0, {0, 0,}}, true},
};

void key_seqv_reset_index_counter() {
    key_seqv_index = 0;
}

void key_seqv_increase_counter() {
    if (!key_seqvs[key_seqv_index].last_item)
        key_seqv_index++;
}

bool key_seqv_get_report(struct key_seqv_t *const report_out) {
    if (report_out == NULL)
        return false;

    *report_out = key_seqvs[key_seqv_index];
    return true;
}

/* key_seqv.c */
