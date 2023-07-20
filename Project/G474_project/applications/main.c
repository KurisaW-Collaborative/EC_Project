/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "mpu9250_config.h"
#include "car_control.h"

/* defined the LED2 pin: PA5 */
#define LED2_PIN    GET_PIN(A, 5)

int main(void)
{
    // board init
    MX_I2C3_Init();

    // start mpu9250 to ctrl car balance
//    mpu9250_drv_init();

    /* set LED2 pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
