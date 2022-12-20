#include "error_state.h"
#include "pico/cyw43_arch.h"

void enter_error_state(enum error_state_t err_state) {
    switch (err_state) {
        case ERR_GET_REPORT_SIZE:
            while (true) {
                UPDATE_LED(true, 200);
                UPDATE_LED(false, 800);
            }
            break;
        default:
            break;
    }
}

/* error_state.c */
