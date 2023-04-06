/**
 * @brief Main file with initialization functions.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file main.c
 * @author Hung Do
 * @date 21/12/2022
 */
#include "bsp/board.h"          // board_init
#include "keyseqv/key_seqv.h"   // struct key_seqv_t, key_seqv_get_report
#include "pico/cyw43_arch.h"    // cyw43_arch_init
#include "tusb.h"
#include "usb_general.h"        // get_enable_key_seqv, active_delay
#include "tcp_server.h"         // init_server
#include "dhcpserver/dhcpserver.h"

/**
 * @brief Send a key sequence using HID report.
 *
 * @return uint32_t Delay time in ms.
 */
uint32_t send_report() {
    struct key_seqv_t key_sqv;
    if (!tud_hid_ready())
        return 0;

    if (!get_enable_key_seqv() || !key_seqv_get_report(&key_sqv)) {
        tud_hid_keyboard_report(0, 0, NULL);
        return 0;
    }

    uint8_t *keycode = key_sqv.report.keycode[0] ?
                       key_sqv.report.keycode : NULL;

    // TODO: function `tud_hid_n_report` might enable custom reports
    // increase counter when report was successfully sent
    if (tud_hid_keyboard_report(0, key_sqv.report.modifier, keycode)) {
        key_seqv_increase_counter(false);
        return key_sqv.delay;
    }
    return 0;
}

int main(void) {
    // init board and library
    board_init();
    if (cyw43_arch_init())
        return 1;

#if WIFI_ENABLE
    struct server_data_t *sd = (struct server_data_t *)calloc(1, sizeof(struct server_data_t));
    if (sd == NULL)
        return 1;

    // enable access point
    cyw43_arch_enable_ap_mode(WIFI_SSID, WIFI_PSWD, CYW43_AUTH_WPA2_AES_PSK);

    // define network's IP range
    struct network_data_t nd;
    IP4_ADDR(ip_2_ip4(&(nd.gateway)), 192, 168, 4, 1);
    IP4_ADDR(ip_2_ip4(&(nd.mask)), 255, 255, 255, 252);

    dhcp_server_t dhcp_server;
    dhcp_server_init(&dhcp_server, &(nd.gateway), &(nd.mask));

    init_server(sd, 5000);
#endif // WIFI_ENABLE

    tusb_init();

    // initial booting delay
    active_delay(1500000);

    // main program loop
    uint32_t delay = 0;
    while (1) {
        tud_task(); // tinyusb device task
        delay = send_report();
        sleep_ms(delay);
    }
#if WIFI_ENABLE
    close_server(sd);
    dhcp_server_deinit(&dhcp_server);
    free(sd);
#endif // WIFI_ENABLE
    cyw43_arch_deinit();
    return 0;
}

/* main.c */
