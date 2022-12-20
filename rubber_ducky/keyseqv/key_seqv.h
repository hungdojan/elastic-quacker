#ifndef _KEY_SEQV_H_
#define _KEY_SEQV_H_
#include "tusb.h"

struct key_seqv_t {
    uint32_t wait_before;
    hid_keyboard_report_t report;
    bool last_item;
};

void key_seqv_reset_index_counter();

void key_seqv_increase_counter();

/**
 * @brief Returns next key combination.
 *
 * @param [out] report_out Reference to memory to store information.
 * @return Returns true if information passed through referenced memory is valid.
 */
bool key_seqv_get_report(struct key_seqv_t * const report_out);

#endif // _KEY_SEQV_H_
