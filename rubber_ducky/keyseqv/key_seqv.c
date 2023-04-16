/**
 * @brief Defines key sequence functions.
 *
 * This source ocude serves as the submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file key_seqv.c
 * @author Hung Do
 * @date 21/12/2022
 */

#include "key_seqv.h"
#include "usb_general.h"    // set_enable_key_seqv, active_delay

#define COPY_KEY_SEQV(dst, src) \
    do { \
        dst.delay = src.delay;                      \
        dst.report.modifier = src.report.modifier;  \
        for (int i = 0; i < 6; i++)                \
            dst.report.keycode[i] = src.report.keycode[i];  \
        dst.last_item = src.last_item;              \
    } while(0)

/** Index of the key sequence to send */
static size_t key_seqv_index = 0;
/** Index of the key sequence for debugging */
static size_t key_seqv_index_debug = 0;
/** Differentiates whether device is currently being edited or not. */
static bool read_write = false;
/** Returns number of key sequences in the buffer */
static int key_seqv_len = -1;

void key_seqv_reset_index_counter(bool debug) {
    if (debug) {
        key_seqv_index_debug = 0;
    } else {
        key_seqv_index = 0;
        active_delay(100000);
    }
}

void key_seqv_increase_counter(bool debug) {
    // empty list
    if (key_seqv_len == 0)
        return;

    if (!key_seqvs[key_seqv_index].last_item) {
        if (debug)
            key_seqv_index_debug++;
        else
            key_seqv_index++;
    }
}

bool key_seqv_get_report(struct key_seqv_t * const report_out) {
    if (report_out == NULL)
        return false;
    if (key_seqv_len == 0)
        return false;

    *report_out = key_seqvs[key_seqv_index];
    return true;
}

size_t key_seqv_debug_report(uint8_t *buffer, size_t buffer_size) {
    if (buffer == NULL)
        return 0;

    if (sizeof(struct key_seqv_t) > buffer_size)
        return 0;

    struct key_seqv_t *curr = &key_seqvs[key_seqv_index_debug];
    memcpy(buffer, (const void *)curr, sizeof(struct key_seqv_t));

    return sizeof(struct key_seqv_t);
}

void key_seqv_set_mode(bool is_read_write) {
    if (is_read_write == read_write)
        return;

    read_write = is_read_write;
    if (is_read_write)
        set_enable_key_seqv(false);

    // clear the list when used for the first time
    if (key_seqv_len < 0 && is_read_write) {
        key_seqv_clear();
    }
}

bool key_seqv_is_read_write() {
    return read_write;
}

bool key_seqv_push_report(const struct key_seqv_t *report_in) {
    if (!read_write ||          // not in read-write mode
        report_in == NULL ||    // wrong input conditions
        key_seqv_len >= KEY_SEQV_BUFFER_SIZE    // list is full
        ) {
        return false;
    }

    // add new item
    COPY_KEY_SEQV(key_seqvs[key_seqv_len], (*report_in));

    // update last item flags
    key_seqvs[key_seqv_len].last_item = true;
    if (key_seqv_len > 0) {
        key_seqvs[key_seqv_len - 1].last_item = false;
    }
    key_seqv_len++;

    return true;
}

bool key_seqv_pop_report(struct key_seqv_t * const report_out) {
    if (!read_write ||          // not in read-write mode
        key_seqv_len < 1        // empty list
        ) {
        return false;
    }

    key_seqv_len--;

    // update last item
    if (key_seqv_len > 0) {
        key_seqvs[key_seqv_len - 1].last_item = true;
    }
    // popped remove item
    if (report_out) {
        COPY_KEY_SEQV((*report_out), key_seqvs[key_seqv_len]);
    }

    return true;
}

void key_seqv_clear() {
    key_seqv_len = 0;
}

int key_seqv_get_len() {
    return key_seqv_len;
}

void key_seqv_run_sequences() {
    key_seqv_reset_index_counter(false);
    set_enable_key_seqv(true);
}

/* key_seqv.c */
