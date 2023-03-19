/**
 * @brief Declaration of key sequence structure and its functions.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file key_seqv.h
 * @author Hung Do
 * @date 21/12/2022
 */
#ifndef _KEY_SEQV_H_
#define _KEY_SEQV_H_
#include "tusb.h"

#define TURN_OFF_KEYS(delay, last) {delay, {0, 0, {0, }}, last}
#define KEY_SEQV(delay, modifier, keys, last) \
    {0, {modifier, 0, keys}, false}, \
    TURN_OFF_KEYS(delay, last)

#define LAST_ITEM {0, {0, 0, {0, }}, true}

#define KEY_SEQV_BUFFER_SIZE 101

/**
 * @brief Key sequence structure.
 */
struct key_seqv_t {
    uint32_t delay;                 /**< Delay after sending report in ms */
    hid_keyboard_report_t report;   /**< Report data */
    bool last_item;                 /**< Last item flag, items after that are ignored */
};

extern struct key_seqv_t key_seqvs[KEY_SEQV_BUFFER_SIZE];

/**
 * @brief Reset key sequence index counter.
 */
void key_seqv_reset_index_counter();

/**
 * @brief Increase key sequence index counter.
 */
void key_seqv_increase_counter();

/**
 * @brief Returns next key combination.
 *
 * @param [out] report_out Reference to memory to store information.
 * @return Returns true if information passed through referenced memory is valid.
 */
bool key_seqv_get_report(struct key_seqv_t * const report_out);

#endif // _KEY_SEQV_H_
