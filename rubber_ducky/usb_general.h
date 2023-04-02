#ifndef _USB_GENERAL_H_
#define _USB_GENERAL_H_
#include "tusb.h"

// HID report length
#define _REPORT_LENGTH 65

// disk size
#define BYTES_PER_SECTOR 512u
#define NUM_OF_SECTORS 16u

// convert u32 to four u8 numbers using LE
#define FILE_SIZE(_size) \
    (uint8_t)((_size) & 0xff), \
    (uint8_t)(((_size) & 0xff00) >> 8), \
    (uint8_t)(((_size) & 0xff0000) >> 16), \
    (uint8_t)(((_size) & 0xff000000) >> 24)

// file contents
#define AUTOMATA_CONTENT \
"Mačka\r\n"

#define README_CONTENT \
"# Rubber Ducky\r\n" \
"This is a read-only readme file. If you can access this file that means that it works!\r\n"

// Sense key table: https://www.seagate.com/files/staticfiles/support/docs/manual/Interface%20manuals/100293068j.pdf#G4.1602528
// Additional sense key table: https://www.seagate.com/files/staticfiles/support/docs/manual/Interface%20manuals/100293068j.pdf#G4.1602906

// USB status used by MSC; indicates if the device was connected or not
extern bool is_ejected;

/**
 * @brief Return the state of 'enable_key_seqv' variable.
 *
 * @return State of 'enable_key_seqv'.
 */
bool get_enable_key_seqv();

/**
 * @brief Update the state of 'enable_key_seqv' variable.
 *
 * @param value New state of 'enable_key_seqv' variable.
 */
void set_enable_key_seqv(bool value);

/**
 * @brief Passive delay; call tud_task() in the mean time.
 *
 * @param ticks Number of ticks.
 */
void active_delay(uint32_t ticks);

#endif // _USB_GENERAL_H_
