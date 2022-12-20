/**
 * @brief Definition of error state function.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file error_state.c
 * @author Hung Do
 * @date 21/12/2022
 */
#include "error_state.h"

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
