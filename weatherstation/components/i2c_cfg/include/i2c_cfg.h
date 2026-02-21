#ifndef I2C_CFG_H
#define I2C_CFG_H

#include "driver/i2c_master.h"

typedef struct {
    i2c_addr_bit_len_t addr_len;
    uint16_t addr;
    uint32_t speed;
} i2c_device_cfg;

i2c_master_bus_handle_t i2c_init_master(gpio_num_t i2c_gpio_scl, gpio_num_t i2c_gpio_sda);
i2c_master_dev_handle_t i2c_add_device(i2c_device_cfg device);

#endif