/**
 * @brief Implementation of TCP server using lwIP library.
 *
 * This source code serves as the submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file tcp_server.c
 * @author Hung Do
 * @date 06/04/2023
 */
#include "tcp_server.h"
#include "request_process.h"

/**
 * @brief Clean up function for lost/ended connections.
 *
 * @param arg  Connection's argument structure.
 * @param tpcb Client's tcp_pcb.
 * @return ERR_OK when no error occured during clean up; ERR_ABRT otherwise.
 */
static err_t close_connection(void *arg, struct tcp_pcb *tpcb) {
    struct client_data_t *cd = (struct client_data_t *)arg;
    err_t err = ERR_OK;
    if (cd == NULL || cd->pcb != tpcb)
        return ERR_VAL;

    if (tpcb != NULL) {
        tcp_arg(tpcb, NULL);
        tcp_recv(tpcb, NULL);
        tcp_sent(tpcb, NULL);
        tcp_poll(tpcb, NULL, 0);
        tcp_err(tpcb, NULL);

        err = tcp_close(tpcb);
        if (err != ERR_OK) {
            tcp_abort(tpcb);
            err = ERR_ABRT;
        }
        free(cd);
    }
    return err;
}

/** Callback function that is called after receiving data from the client. */
static err_t recv_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    struct client_data_t *cd = (struct client_data_t *)arg;

    if (cd == NULL || cd->pcb != tpcb ||
        err != ERR_OK || p == NULL) {
        return close_connection(arg, tpcb);
    }

    pbuf_copy_partial(p, cd->buffer, MIN(CLIENT_BUFFER_SIZE, p->tot_len), 0);
    size_t packet_len = p->tot_len;
    struct packet_t *packet = (struct packet_t *)cd->buffer;

    // packet too big
    if (packet->payload_len > CLIENT_BUFFER_SIZE - sizeof(struct packet_t)) {
        packet_len = too_big_pl(cd->buffer, CLIENT_BUFFER_SIZE);
    } else {
        // check operation codes
        switch (packet->op_code) {
            case OP_SET_EDITABLE:
                packet_len = set_editable_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            case OP_GET_EDITABLE:
                packet_len = get_editable_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            case OP_CLEAR_DATA:
                packet_len = clear_data_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            case OP_PUSH_DATA:
                packet_len = push_data_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            case OP_POP_DATA:
                packet_len = pop_data_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            case OP_GET_DEBUG_LINE:
                packet_len = get_debug_line_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            case OP_INC_DEBUG_LINE:
                packet_len = inc_debug_line_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            case OP_RESET_DEBUG_LINE_INDEX:
                packet_len = reset_debug_line_index_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            case OP_RUN_SEQUENCES:
                packet_len = run_sequences(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
            default:
                packet_len = unknown_opcode_pl(cd->buffer, CLIENT_BUFFER_SIZE);
                break;
        }
    }

    tcp_write(tpcb, cd->buffer, packet_len, 0);
    tcp_recved(tpcb, p->tot_len);
    pbuf_free(p);
    return err;

}

/** Callback function that is called after no data is send after POLL_INTERVAL time. */
static err_t poll_cb(void *arg, struct tcp_pcb *tpcb) {
    return close_connection(arg, tpcb);
}

/** Callback function that is called after server send data. */
static err_t sent_cb(void *arg, struct tcp_pcb *tpcb, uint16_t len) {
    (void)len;
    struct client_data_t *cd = (struct client_data_t *)arg;
    if (cd == NULL)
        return ERR_OK;

    if (cd->buffer[0] == 0) {
        return close_connection(arg, tpcb);
    }
    return ERR_OK;
}

/** Callback function that is called when error occurs during the communication. */
static void err_cb(void *arg, err_t err) {
    struct client_data_t *cd = (struct client_data_t *)arg;
    if (err != ERR_ABRT && cd != NULL) {
        tcp_close(cd->pcb);
    }
}

/** Callback function that is called when new client is connected. */
static err_t accept_cb(void *arg, struct tcp_pcb *client_pcb, err_t err) {
    (void)arg;
    if (client_pcb == NULL || err != ERR_OK)
        return ERR_VAL;

    struct client_data_t *cd = (struct client_data_t *)calloc(1, sizeof(struct client_data_t));
    if (cd == NULL)
        return ERR_MEM;

    cd->pcb = client_pcb;

    tcp_arg(client_pcb, cd);
    tcp_sent(client_pcb, sent_cb);
    tcp_recv(client_pcb, recv_cb);
    tcp_poll(client_pcb, poll_cb, POLL_INTERVAL);
    tcp_err(client_pcb, err_cb);

    return ERR_OK;
}

bool init_server(struct server_data_t *sd, uint16_t port) {
    if (sd == NULL)         goto err_initial_state;

    struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
    if (pcb == NULL)        goto err_initial_state;

    err_t err = tcp_bind(pcb, IP_ANY_TYPE, port);
    if (err != ERR_OK)      goto err_post_pcb_state;

    sd->pcb = tcp_listen_with_backlog_and_err(pcb, 2, &err);
    if (sd->pcb == NULL)    goto err_post_pcb_state;

    tcp_arg(sd->pcb, sd);
    tcp_accept(sd->pcb, accept_cb);

    return true;

err_post_pcb_state:
    tcp_close(pcb);
err_initial_state:
    return false;
}

void close_server(struct server_data_t *sd) {
    if (sd != NULL && sd->pcb != NULL) {
        tcp_arg(sd->pcb, NULL);
        tcp_close(sd->pcb);
        sd->pcb = NULL;
    }
}

/* tcp_server.c */
