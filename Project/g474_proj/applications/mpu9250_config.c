/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Yifang       the first version
 */
#include "mpu9250_config.h"
#include <board.h>

struct Axisf acc_base;
struct Axisf gyro_base;
struct Axisf mag_base;

extern struct MPU9250_t mpu9250;

void mpu_thread_entry(void)
{
    while(1)
    {
        GetImuData();
        imuUpdate(mpu9250.acc,mpu9250.gyro,mpu9250.mag);
        rt_thread_mdelay(1000);
    }
}

void mpu9250_drv_init(void)
{
    MPU9250_Init();
    rt_kprintf("mpu9250 device initial successful!\n");

    rt_kprintf("---------------------------------- mpu9250 use tip -----------------------------------------\n");
    rt_kprintf("You can open the waveforms of Euler angles by defining the 'EULER_ANGLE_DATA' macro.\n");
    rt_kprintf("Or you can view the nine-axis raw waveform data by defining the 'AXIS_ORIGIN_DATA' macro.\n");

    rt_thread_t mpu_thread = rt_thread_create("mpu_th", mpu_thread_entry, RT_NULL, 1024, 26, 50);
    if(mpu_thread == RT_NULL)
    {
        rt_kprintf("mpu_th create failed!\n");
    }
    rt_thread_startup(mpu_thread);
}
MSH_CMD_EXPORT(mpu9250_drv_init,mpu9250_drv_init);
//INIT_APP_EXPORT(mpu9250_drv_init);
