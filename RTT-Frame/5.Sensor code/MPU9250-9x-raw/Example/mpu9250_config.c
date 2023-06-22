/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Yifang       the first version
 */
#include <rtdevice.h>
#include <rtthread.h>

#include "board.h"
#include "./mpu9250_lib/mpu9250_drv.h"

struct Axisf acc_base;
struct Axisf gyro_base;
struct Axisf mag_base;

extern struct MPU9250_t mpu9250;

void mpu9250_drv_init(void)
{
    MX_I2C3_Init();

    MPU9250_Init();
    while(1)
    {
        GetImuData();
        imuUpdate(mpu9250.acc,mpu9250.gyro,mpu9250.mag);
    }
}
//MSH_CMD_EXPORT(mpu9250_drv_init,mpu9250_drv_init);
INIT_APP_EXPORT(mpu9250_drv_init);
