/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Yifang       the first version
 */
#include <rtthread.h>
#include <stdint.h>
#include "mpu9250.h"
#include "mpu9250_config.h"

uint8_t ak8963_WhoAmI = 0;
uint8_t mpu9250_WhoAmI = 0;
MPU9250 mpu;

/* Init function */
static int mpu9250_init()
{
    MPU9250_Init(&mpu);

    while(1)
    {
        ak8963_WhoAmI = mpu_r_ak8963_WhoAmI(&mpu);
        mpu9250_WhoAmI = mpu_r_WhoAmI(&mpu);
        MPU9250_ReadAccel(&mpu);
        MPU9250_ReadGyro(&mpu);
        MPU9250_ReadMag(&mpu);
        rt_kprintf("AK8963: 0x%x\nMPU9250: 0x%x\n", ak8963_WhoAmI,
                mpu9250_WhoAmI);
        rt_kprintf("AX:%d \tAY:%d\t AZ:%d\n", mpu.mpu_data.Accel_row[0],
                mpu.mpu_data.Accel_row[1], mpu.mpu_data.Accel_row[2]);
        rt_kprintf("AX:%.3f \tAY:%.3f\t AZ:%.3f\n", mpu.mpu_data.Accel[0],
                mpu.mpu_data.Accel[1], mpu.mpu_data.Accel[2]);
        rt_kprintf("GX:%d \tGY:%d\t GZ:%d\n", mpu.mpu_data.Gyro_row[0],
                mpu.mpu_data.Gyro_row[1], mpu.mpu_data.Gyro_row[2]);
        rt_kprintf("GX:%.3f \tGY:%.3f\t GZ:%.3f\n", mpu.mpu_data.Gyro[0],
                mpu.mpu_data.Gyro[1], mpu.mpu_data.Gyro[2]);
        rt_kprintf("MX:%d \tMY:%d\t MZ:%d\n", mpu.mpu_data.Magn_row[0],
                mpu.mpu_data.Magn_row[1], mpu.mpu_data.Magn_row[2]);
        rt_kprintf("MX:%.3f \tMY:%.3f\t MZ:%.3f\n", mpu.mpu_data.Magn[0],
                mpu.mpu_data.Magn[1], mpu.mpu_data.Magn[2]);
        rt_kprintf("*************************\n");

        HAL_Delay(50);
    }
}
MSH_CMD_EXPORT(mpu9250_init, mpu9250 sensor init function);
