#include "key_seqv.h"

static size_t key_seqv_index = 0;

// key sequences for Linux systems
static const struct key_seqv_t key_seqvs[] = {
    {0, {0, 0, {HID_KEY_A, 0,}}, false},
    {0, {0, 0, {HID_KEY_H, 0,}}, false},
    {0, {0, 0, {HID_KEY_O, 0,}}, false},
    {0, {0, 0, {HID_KEY_J, 0,}}, false},
    {0, {0, 0, {0, 0,}}, true},
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
