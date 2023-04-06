/**
 * @brief Defining list of functions used for generating response packets.
 *
 * This source code serves as the submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file request_process.c
 * @author Hung Do
 * @date 06/04/2023
 */
#include "request_process.h"

#define PUSH_ERR_MSG \
    "Could not push new key sequence. The list might be full. " \
    "Check if the device is in read-write mode"

#define POP_ERR_MSG \
    "List of key sequences is empty. Nothing to retrieve."

#define UNKNOWN_OPCODE_ERR_MSG \
    "Given request operation code is undefined. Valid operation codes " \
    "are within the range of 1-8. For more information check the documentation."

#define PAYLOAD_TOO_BIG_ERR_MSG \
    "Packet's payload is too big and cannot be processed."

#define PACKET_DBG 1

/**
 * @brief Create a response packet.
 *
 * @param op_code       Operation code of the packet.
 * @param msg           Packet's payload content.
 * @param msg_len       Payload's size.
 * @param [out] buffer  Buffer in which the packet content will be stored.
 * @param buffer_size   Output buffer's max size.
*/
static size_t create_response(enum oper_codes op_code, const void *msg, size_t msg_len,
                              uint8_t *buffer, size_t buffer_size) {
    if (buffer == NULL)
        return 0;

    memset(buffer, 0, buffer_size);
    struct packet_t *packet = (struct packet_t *)buffer;
    packet->op_code = op_code;
    if (msg == NULL || msg_len == 0) {
        packet->payload_len = 0;
    } else {
        packet->payload_len = msg_len;
        memcpy(packet->payload, msg, msg_len);
    }
    return packet->payload_len + sizeof(struct packet_t);
}

size_t set_editable_pl(uint8_t *buffer, size_t buffer_size) {
    struct packet_t *packet = (struct packet_t *)buffer;
    bool value = packet->payload[0];
    key_seqv_set_mode(value);

    return create_response(OP_IN_OK, NULL, 0, buffer, buffer_size);
}

size_t get_editable_pl(uint8_t *buffer, size_t buffer_size) {
    bool mode = key_seqv_is_read_write();

    return create_response(OP_IN_OK, &mode, 1, buffer, buffer_size);
}

size_t clear_data_pl(uint8_t *buffer, size_t buffer_size) {
    key_seqv_clear();

    return create_response(OP_IN_OK, NULL, 0, buffer, buffer_size);
}

size_t push_data_pl(uint8_t *buffer, size_t buffer_size) {
    struct key_seqv_t *new_keyseqv = (struct key_seqv_t *)
        (buffer + sizeof(struct packet_t)); // offset by packet header
    bool res = key_seqv_push_report(new_keyseqv);

    // create a response
    if (res)
        return create_response(OP_IN_OK, NULL, 0, buffer, buffer_size);
    return create_response(OP_IN_ERR,
                           PUSH_ERR_MSG,
                           strlen(PUSH_ERR_MSG) + 1,
                           buffer,
                           buffer_size
    );
}

size_t pop_data_pl(uint8_t *buffer, size_t buffer_size) {
    struct key_seqv_t pop_ks = {0, };
    bool res = key_seqv_pop_report(&pop_ks);

    // create a response
    if (res)
        return create_response(OP_IN_OK,
                               &pop_ks,
                               sizeof(struct key_seqv_t),
                               buffer,
                               buffer_size
        );
    return create_response(OP_IN_OK,
                           POP_ERR_MSG,
                           strlen(POP_ERR_MSG) + 1,
                           buffer,
                           buffer_size
    );
}

size_t get_debug_line_pl(uint8_t *buffer, size_t buffer_size) {
    uint8_t tmp_buffer[20] = {0, };
    size_t len = key_seqv_debug_report(tmp_buffer, 20);

    return create_response(OP_IN_OK, tmp_buffer, len, buffer, buffer_size);
}

size_t inc_debug_line_pl(uint8_t *buffer, size_t buffer_size) {
    key_seqv_increase_counter(true);

    // create a response
    return create_response(OP_IN_OK, NULL, 0, buffer, buffer_size);
}

size_t reset_debug_line_index_pl(uint8_t *buffer, size_t buffer_size) {
    key_seqv_reset_index_counter(true);

    // create a response
    return create_response(OP_IN_OK, NULL, 0, buffer, buffer_size);
}

size_t run_sequences(uint8_t *buffer, size_t buffer_size) {
    key_seqv_reset_index_counter(false);

    // create a response
    return create_response(OP_IN_OK, NULL, 0, buffer, buffer_size);
}

size_t unknown_opcode_pl(uint8_t *buffer, size_t buffer_size) {
    return create_response(OP_IN_ERR,
                           UNKNOWN_OPCODE_ERR_MSG,
                           strlen(UNKNOWN_OPCODE_ERR_MSG) + 1,
                           buffer,
                           buffer_size
    );
}

size_t too_big_pl(uint8_t *buffer, size_t buffer_size) {
    return create_response(OP_IN_ERR,
                           PAYLOAD_TOO_BIG_ERR_MSG,
                           strlen(PAYLOAD_TOO_BIG_ERR_MSG) + 1,
                           buffer,
                           buffer_size
    );
}

/* request_process.c */
