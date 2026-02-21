#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"
#include "esp_timer.h"

#include "bsp.h"

#define DEBOUNCE_TIME 20000 // us

typedef void (*button_cb)(button_id_t id);

typedef struct button {
    button_id_t id;
    gpio_num_t gpio;
    button_cb callback;
    esp_timer_handle_t debounce_timer;
} button_t;

button_t *button_init(int id, gpio_num_t gpio_num, button_cb cb);

#endif