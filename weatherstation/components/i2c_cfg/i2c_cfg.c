#include "driver/i2c_master.h"
#include "esp_log.h"
#include <stdio.h>

#include "i2c_cfg.h"

static const char *TAG = "i2c_config";

i2c_master_bus_handle_t bus_handle;
i2c_master_dev_handle_t dev_handle;

i2c_master_bus_handle_t i2c_init_master(gpio_num_t i2c_gpio_scl, gpio_num_t i2c_gpio_sda) {
    i2c_master_bus_config_t i2c_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = -1,
        .scl_io_num = i2c_gpio_scl,
        .sda_io_num = i2c_gpio_sda,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_config, &bus_handle));
    ESP_LOGI(TAG, "i2c master config complete");
    return bus_handle;
}

i2c_master_dev_handle_t i2c_add_device(i2c_device_cfg device) {
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = device.addr_len,
        .device_address = device.addr,
        .scl_speed_hz = device.speed,
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
    ESP_LOGI(TAG, "i2c add device config complete");
    return dev_handle;
}