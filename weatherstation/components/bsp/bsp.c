#include "bsp.h"
#include <stdio.h>

static const gpio_num_t button_map[N_BUTTONS] = {
    [ID_BUTTON_LEFT] = GPIO_NUM_19,
    [ID_BUTTON_CENTER] = GPIO_NUM_16,
    [ID_BUTTON_RIGHT] = GPIO_NUM_4};

gpio_num_t button_get_gpio(button_id_t id) {
    return button_map[id];
}