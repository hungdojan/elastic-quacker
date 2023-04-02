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

    bool tmp = true;
    pbuf_copy_partial(p, cd->buffer, MIN(CLIENT_BUFFER_SIZE, p->tot_len), 0);
    struct packet_t *packet = (struct packet_t *)cd->buffer;
    switch (packet->op_code) {
        case OP_SET_EDITABLE:
            err = set_editable_pl(cd->buffer, CLIENT_BUFFER_SIZE);
            break;
        case OP_GET_EDITABLE:
            err = get_editable_pl(cd->buffer, CLIENT_BUFFER_SIZE);
            break;
        case OP_CLEAR_DATA:
            err = clear_data_pl(cd->buffer, CLIENT_BUFFER_SIZE);
            break;
        case OP_PUSH_DATA:
            err = push_data_pl(cd->buffer, CLIENT_BUFFER_SIZE);
            break;
        case OP_POP_DATA:
            err = pop_data_pl(cd->buffer, CLIENT_BUFFER_SIZE);
            break;
        case OP_GET_LINE:
            err = get_line_pl(cd->buffer, CLIENT_BUFFER_SIZE);
            break;
        case OP_INC_LINE:
            err = inc_line_pl(cd->buffer, CLIENT_BUFFER_SIZE);
            break;
        case OP_RESET_LINE_INDEX:
            err = reset_line_index_pl(cd->buffer, CLIENT_BUFFER_SIZE);
            break;
        default:
            tmp = false;
            break;
    }

    if (tmp)
        tcp_write(tpcb, cd->buffer, packet->payload_len + sizeof(uint8_t) + sizeof(size_t), 0);
    else
        tcp_write(tpcb, cd->buffer, p->tot_len, 0);
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
