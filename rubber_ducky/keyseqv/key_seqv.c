/**
 * @brief Defines key sequence functions.
 *
 * This source ocude serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file key_seqv.c
 * @author Hung Do
 * @date 21/12/2022
 */

#include "key_seqv.h"

/** Index of the key sequence to send */
static size_t key_seqv_index = 0;
/** Differentiates whether device runs hard-coded or uploaded script */
static bool mode_static = true;
/** Returns number of key sequences in the buffer */
static int key_seqv_len = -1;

void key_seqv_reset_index_counter() {
    key_seqv_index = 0;
}

void key_seqv_increase_counter() {
    if (!key_seqvs[key_seqv_index].last_item)
        key_seqv_index++;
}

bool key_seqv_get_report(struct key_seqv_t * const report_out) {
    if (report_out == NULL)
        return false;

    *report_out = key_seqvs[key_seqv_index];
    return true;
}
