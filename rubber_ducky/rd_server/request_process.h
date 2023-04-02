#ifndef _REQUEST_PROCESS_H_
#define _REQUEST_PROCESS_H_

#include "lwip/err.h"
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
    uint32_t payload_len;
    uint8_t payload[];
};

enum oper_codes {
    // incoming
    OP_SET_EDITABLE=1,
    OP_GET_EDITABLE,
    OP_CLEAR_DATA,
    OP_PUSH_DATA,
    OP_POP_DATA,
    OP_GET_LINE,
    OP_INC_LINE,
    OP_RESET_LINE_INDEX,

    // outgoing
    OP_IN_OK,
    OP_IN_ERR,
};

/**
 * @brief Process "SET EDITABLE" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
err_t set_editable_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "GET EDITABLE" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
err_t get_editable_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "CLEAR DATA" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
err_t clear_data_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "PUSH DATA" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
err_t push_data_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "POP DATA" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
err_t pop_data_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "GET LINE" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
err_t get_line_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "INC LINE" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
err_t inc_line_pl(uint8_t *buffer, size_t buffer_size);

/**
 * @brief Process "RESET LINE INDEX" packet.
 *
 * @param buffer      Received buffer with data.
 * @param buffer_size Buffer's max size.
 */
err_t reset_line_index_pl(uint8_t *buffer, size_t buffer_size);

#endif // _REQUEST_PROCESS_H_
