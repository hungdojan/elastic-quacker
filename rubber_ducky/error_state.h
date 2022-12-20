#ifndef _ERROR_STATE_H_
#define _ERROR_STATE_H_

#define UPDATE_LED(state, delay) \
    do { \
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state); \
        sleep_ms(delay); \
    } while (0)

enum error_state_t {
    NO_ERR,
    ERR_GET_REPORT_SIZE,
};

void enter_error_state(enum error_state_t err_state);

#endif // _ERROR_STATE_H_
