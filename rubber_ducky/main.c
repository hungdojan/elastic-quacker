#include "bsp/board.h"  // board_init
#include "pico/cyw43_arch.h"
#include "tusb.h"

int main(void) {
    board_init();
    tusb_init();
    if (cyw43_arch_init())
        return 1;

    while (1) {
        // TODO: my task
        tud_task(); // tinyusb device task
    }

    return 0;
}
