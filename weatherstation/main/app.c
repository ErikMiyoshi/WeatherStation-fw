#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

#include "button.h"

const char *TAG = "main";

void app_main(void) {
    while (1) {
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
