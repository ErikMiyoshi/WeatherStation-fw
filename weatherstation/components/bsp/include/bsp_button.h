#ifndef BSP_BUTTON_H
#define BSP_BUTTON_H

#include "driver/gpio.h"

#define N_BUTTONS 3

typedef enum {
    ID_BUTTON_LEFT = 0,
    ID_BUTTON_CENTER,
    ID_BUTTON_RIGHT,
} button_id_t;

gpio_num_t button_get_gpio(button_id_t id);

#endif