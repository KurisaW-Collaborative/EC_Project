/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Yifang       the first version
 */
#include <stdio.h>
#include <board.h>
#include "bmp280_read.h"

I2C_HandleTypeDef hi2c1;

static BMP280_HandleTypedef bmp280;
static float pressure_t, temperature_t, humidity_t;

/* Init function */
int bmp280_drv_init(int argc, char *argv[])
{
    MX_I2C1_Init();

    bmp280_init_default_params(&bmp280.params);
    bmp280.addr = BMP280_I2C_ADDRESS_0;
    bmp280.i2c = &hi2c1;

    while (!bmp280_init(&bmp280, &bmp280.params))
    {
        printf("BMP280 initialization failed\n");
        HAL_Delay(2000);
    }
//    printf("bmp280.id is 0x%x\n",bmp280.id);
    bool bme280p = bmp280.id == BME280_CHIP_ID;
//    printf("BMP280: found %d\n",bme280p);

    rt_kprintf("[weather] bmp280_drv_init success!\r\n");

    return 0;
}
//MSH_CMD_EXPORT(bmp280_drv_init, bmp280 sensor init function);
//INIT_APP_EXPORT(bmp280_drv_init);

float bmp280_read(void)
{
//    rt_thread_mdelay(100);
    while (!bmp280_read_float(&bmp280, &temperature_t, &pressure_t, &humidity_t))
    {
        printf("pressure_t reading failed\n");
        HAL_Delay(2000);
    }

    rt_kprintf("Pressure: %.2f Pa\n", pressure_t);
}
MSH_CMD_EXPORT(bmp280_read,bmp280_read);
