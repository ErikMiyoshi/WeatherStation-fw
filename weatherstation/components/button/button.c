#include "driver/gpio.h"
#include "esp_attr.h"
#include "esp_timer.h"
#include <inttypes.h>
#include <stdio.h>

#include "bsp.h"
#include "button.h"

static button_t buttons[N_BUTTONS];

static void button_debounce_cb(void *arg) {
    button_t *btn = (button_t *)arg;

    if (gpio_get_level(btn->gpio) == 0) {
        btn->callback(btn->id);
    }

    gpio_intr_enable(btn->gpio);
}

static void IRAM_ATTR gpio_isr_handler(void *args) {
    button_t *btn = (button_t *)args;

    gpio_intr_disable(btn->gpio);
    esp_timer_start_once(btn->debounce_timer, DEBOUNCE_TIME);
}

button_t *button_init(int id, gpio_num_t gpio_num, button_cb cb) {
    button_t *btn = &buttons[id];

    btn->id = id;
    btn->gpio = gpio_num;
    btn->callback = cb;
    btn->debounce_timer = NULL;

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << gpio_num),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE};
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(gpio_num, gpio_isr_handler, (void *)btn);

    const esp_timer_create_args_t timer_args = {
        .callback = button_debounce_cb,
        .arg = btn,
        .name = "btn_db"};

    esp_timer_create(&timer_args, &btn->debounce_timer);
    return btn;
}