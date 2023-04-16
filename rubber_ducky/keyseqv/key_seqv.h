/**
 * @brief Declaration of key sequence structure and its functions.
 *
 * This source code serves as the submission to my bachelor thesis topic
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
 *
 * @param debug Reset debug index.
 */
void key_seqv_reset_index_counter(bool debug);

/**
 * @brief Increase key sequence index counter.
 *
 * @param debug Increase the debug index.
 */
void key_seqv_increase_counter(bool debug);

/**
 * @brief Returns next key combination.
 *
 * @param [out] report_out Reference to memory to store information.
 * @return Returns true if information passed through referenced memory is valid.
 */
bool key_seqv_get_report(struct key_seqv_t * const report_out);

/**
 * @brief Returns debug info of the current key sequence.
 *
 * @param [out] buffer Outputing buffer where function stores current key sequence data.
 * @param buffer_size  Buffer's max size.
 * @return Size of the buffer content.
 */
size_t key_seqv_debug_report(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Update read-write mode of the key sequence list.
 *
 * Read-write mode allows user to edit the key sequence list.
 * When the list is in read-write mode, the process of running
 * the list of sequences (sending commands to the host machine) is put on
 * halt. To enable payload execution, call key_seqv_run_sequences().
 *
 * This function DOES NOT reset the index of the counter. User has to
 * reset it manually using key_seqv_reset_index_counter() function.
 *
 * If user enables read-write mode for the FIRST TIME this function
 * automatically clears the list of key sequences.
 *
 * @param is_read_write 'true' will set the list to read-write mode.
 *                      'false' will set the list to read-only mode.
 */
void key_seqv_set_mode(bool is_read_write);

/**
 * @brief Check if the device is in read-write mode.
 *
 * @return 'true' is returned if device is currently in read-write mode;
 *         'false' otherwise.
 */
bool key_seqv_is_read_write();

/**
 * @brief Adds new key sequence to the end of the list.
 *
 * @param report_in Reference to the key sequence structure to insert into the list.
 * @return 'true' when the sequence was successfully added.
 */
bool key_seqv_push_report(const struct key_seqv_t * report_in);

/**
 * @brief Remove and return last key_sequence in the list.
 *
 * @param [out] report_out Reference to a memory to store popped sequence.
 * @return Returns 'true' if an item was popped. If the list is empty this
 *         function will return 'false'.
 */
bool key_seqv_pop_report(struct key_seqv_t * const report_out);

/**
 * @brief Clear the list of key sequences.
 */
void key_seqv_clear();

/**
 * @brief Returns key sequence list's length.
 *
 * This function can only compute list's length AFTER it was edited.
 * If the list hasn't been edited yet (hasn't been changed to read-write
 * mode) this function will return negative number.
 *
 * @return Length of the key sequence list. Negative number for default list.
 */
int key_seqv_get_len();

/**
 * @brief Perform the stored key sequences.
 *
 * Reset key sequence index and enable key sequence execution.
 */
void key_seqv_run_sequences();

#endif // _KEY_SEQV_H_
