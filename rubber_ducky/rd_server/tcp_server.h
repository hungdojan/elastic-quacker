/**
 * @brief Implementation of TCP server using lwIP library.
 *
 * This source code serves as the submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file tcp_server.h
 * @author Hung Do
 * @date 06/04/2023
 */
#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/ip_addr.h"

#define CLIENT_BUFFER_SIZE 1024
#define POLL_INTERVAL 10

#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

struct network_data_t {
    ip_addr_t mask;
    ip_addr_t gateway;
};

struct server_data_t {
    struct tcp_pcb *pcb;
};

struct client_data_t {
    struct tcp_pcb *pcb;
    uint8_t buffer[CLIENT_BUFFER_SIZE];
};

/**
 * @brief Initialize TCP server.
 *
 * @param sd    Reference to server data structure.
 * @param port  Application port.
 * @return Whether the initialization ended successfully.
 */
bool init_server(struct server_data_t *sd, uint16_t port);

/**
 * @brief Close TCP server and free allocated resources.
 *
 * @param sd Reference ot server data structure.
 */
void close_server(struct server_data_t *sd);

#endif // _TCP_SERVER_H_
