/**
 * @brief Declaring list of functions used for generating response packets.
 *
 * This source code serves as the submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file request_process.h
 * @author Hung Do
 * @date 06/04/2023
 */
#ifndef _REQUEST_PROCESS_H_
#define _REQUEST_PROCESS_H_

#include "keyseqv/key_seqv.h"

#define _RESPONSE_HEADER(op_code, buffer, buffer_size) \
    do { \
        memset((buffer), 0, (buffer_size)); \
        (buffer)[0] = (op_code);            \
    } while(0)

#define U32_TO_U8(_val) \
    (uint8_t)((_val) & 0xff), \
    (uint8_t)(((_val) & 0xff00) >> 8), \
    (uint8_t)(((_val) & 0xff0000) >> 16), \
    (uint8_t)(((_val) & 0xff000000) >> 24)

struct packet_t {
    uint8_t op_code;
    uint8_t reserved;
    uint16_t payload_len;
    uint8_t payload[];
};

enum oper_codes {
    // incoming
    OP_SET_EDITABLE=1,
    OP_GET_EDITABLE,
    OP_CLEAR_DATA,
    OP_PUSH_DATA,
    OP_POP_DATA,
    OP_GET_DEBUG_CURSOR,
    OP_INC_DEBUG_CURSOR,
    OP_RESET_DEBUG_CURSOR,
    OP_RUN_SEQUENCES,

    // outgoing
    OP_IN_OK,
    OP_IN_ERR,
};

/**
 * @brief Process "SET EDITABLE" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
 */
size_t set_editable_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "GET EDITABLE" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
 */
size_t get_editable_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "CLEAR DATA" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
 */
size_t clear_data_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "PUSH DATA" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
 */
size_t push_data_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "POP DATA" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
size_t pop_data_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "GET DEBUG CURSOR" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
 */
size_t get_debug_cursor_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "INC DEBUG CURSOR" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
 */
size_t inc_debug_cursor_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "RESET DEBUG CURSOR" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
 */
size_t reset_debug_cursor_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "RUN SEQUENCES" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
 */
size_t run_sequences_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Generate response to a packet with unknown operation code.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
*/
size_t unknown_opcode_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Generate response to a packet with payload size exceeding buffer size.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 * @return Number of bytes written.
*/
size_t too_big_pl(uint8_t *buffer, size_t buffer_size);

#endif // _REQUEST_PROCESS_H_
