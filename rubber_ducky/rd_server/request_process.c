#include "request_process.h"

#define PUSH_ERR_MSG \
    "Could not push new key sequence. The list might be full. " \
    "Check if the device is in read-write mode"

#define POP_ERR_MSG \
    "List of key sequences is empty. Nothing to retrieve."

#define PACKET_DBG 1
#define CREATE_RESPONSE(msg, buffer) \
    do { \
        memset(buffer, 0, buffer_size);                      \
        struct packet_t *packet = (struct packet_t *)buffer; \
        packet->op_code = OP_IN_OK;                          \
        packet->payload_len = strlen(msg) + 1;               \
        memcpy(packet->payload, msg, packet->payload_len);   \
    } while (0);



err_t set_editable_pl(uint8_t *buffer, size_t buffer_size) {
#if PACKET_DBG
    CREATE_RESPONSE("SET EDITABLE", buffer);
#else
    bool value = buffer[2];
    key_seqv_set_mode(value);

    // create a response
    _RESPONSE_HEADER(OP_IN_OK, buffer, buffer_size);
#endif
    return ERR_OK;
}

err_t get_editable_pl(uint8_t *buffer, size_t buffer_size) {
#if PACKET_DBG
    CREATE_RESPONSE("GET EDITABLE", buffer);
#else
    bool mode = key_seqv_is_read_write();

    // create a response
    _RESPONSE_HEADER(OP_IN_OK, buffer, buffer_size);
    struct packet_t *packet = (struct packet_t *)buffer;
    packet->payload_len = 1;
    packet->payload[0] = (uint8_t) mode;
#endif
    return ERR_OK;
}

err_t clear_data_pl(uint8_t *buffer, size_t buffer_size) {
#if PACKET_DBG
    CREATE_RESPONSE("CLEAR DATA", buffer);
#else
    key_seqv_clear();

    // create a response
    _RESPONSE_HEADER(OP_IN_OK, buffer, buffer_size);
#endif
    return ERR_OK;
}

err_t push_data_pl(uint8_t *buffer, size_t buffer_size) {

#if PACKET_DBG
    CREATE_RESPONSE("PUSH DATA", buffer);
#else
    struct key_seqv_t *new_keyseqv = (struct key_seqv_t *)
        (buffer + sizeof(uint8_t) + sizeof(uint32_t)); // offset by packet header
    bool res = key_seqv_push_report(new_keyseqv);

    // create a response
    if (res) {
        _RESPONSE_HEADER(OP_IN_OK, buffer, buffer_size);
    } else {
        _RESPONSE_HEADER(OP_IN_ERR, buffer, buffer_size);
        struct packet_t *packet = (struct packet_t *)buffer;
        // TODO: check if functions exist
        packet->payload_len = strlen(PUSH_ERR_MSG) + 1;
        MEMCPY(packet->payload, PUSH_ERR_MSG, packet->payload_len);
    }
#endif

    return ERR_OK;
}

err_t pop_data_pl(uint8_t *buffer, size_t buffer_size) {
#if PACKET_DBG
    CREATE_RESPONSE("POP DATA", buffer);
#else
    struct key_seqv_t pop_ks = {0, };
    bool res = key_seqv_pop_report(&pop_ks);

    // create a response
    _RESPONSE_HEADER(OP_IN_OK, buffer, buffer_size);
    struct packet_t *packet = (struct packet_t *)buffer;
    if (res) {
        packet->payload_len = sizeof(struct key_seqv_t);
        memcpy(packet->payload, &pop_ks, packet->payload_len);
    } else {
        packet->payload_len = sizeof(POP_ERR_MSG) + 1;
        memcpy(packet->payload, POP_ERR_MSG, packet->payload_len);
    }
#endif
    return ERR_OK;
}

err_t get_line_pl(uint8_t *buffer, size_t buffer_size) {
    // create a response
#if PACKET_DBG
    CREATE_RESPONSE("GET LINE", buffer);
#else
    _RESPONSE_HEADER(OP_IN_OK, buffer, buffer_size);
    struct packet_t *packet = (struct packet_t *)buffer;
    size_t len = key_seqv_debug_report(packet->payload,
            buffer_size - (sizeof(uint8_t) + sizeof(uint32_t)));
    packet->payload_len = len;
#endif
    return ERR_OK;
}

err_t inc_line_pl(uint8_t *buffer, size_t buffer_size) {
#if PACKET_DBG
    CREATE_RESPONSE("INC LINE", buffer);
#else
    key_seqv_increase_counter(true);

    // create a response
    _RESPONSE_HEADER(OP_IN_OK, buffer, buffer_size);
#endif
    return ERR_OK;
}

err_t reset_line_index_pl(uint8_t *buffer, size_t buffer_size) {
#if PACKET_DBG
    CREATE_RESPONSE("RESET LINE INDEX", buffer);
#else
    key_seqv_reset_index_counter(true);

    // create a response
    _RESPONSE_HEADER(OP_IN_OK, buffer, buffer_size);
#endif
    return ERR_OK;
}
/* request_process.c */
