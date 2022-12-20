/**
 * @brief Declaration of error state function.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file error_state.h
 * @author Hung Do
 * @date 21/12/2022
 */
#ifndef _ERROR_STATE_H_
#define _ERROR_STATE_H_
#include "pico/cyw43_arch.h"

/// Update LED state for set amount of time.
#define UPDATE_LED(state, delay) \
    do { \
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state); \
        sleep_ms(delay); \
    } while (0)

enum error_state_t {
    NO_ERR,                 /**< No error */
    ERR_GET_REPORT_SIZE,    /**< Error occured in get report; 1 blink */
};

/**
 * @brief To enter the error state.
 * Board is stuck in infinite loop where it blinks the LED.
 * User can define an error base on number of blinks in one second.
 *
 * @param err_state Type of error.
 */
void enter_error_state(enum error_state_t err_state);

#endif // _ERROR_STATE_H_
