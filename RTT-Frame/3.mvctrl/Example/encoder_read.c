/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-20     Yifang       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "encoder_read.h"

struct pulse_dev car_pulse_dev = {
    .lfp_dev = "pulse2",
    .rfp_dev = "pulse3",
    .lbp_dev = "pulse4",
    .rbp_dev = "pulse5"
};

struct pulse_dev_handle pulse_encoder_dev[4];

int pulse_encoder_dev_read(void *parameter)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t index;
    rt_int32_t count;
    int i = 0;

    void MX_TIM2_Init(void);
    void MX_TIM3_Init(void);
    void MX_TIM4_Init(void);
    void MX_TIM5_Init(void);

    /* 脉冲设备句柄初始化 */
    for (i = 0; i < 4; i++)
    {
        pulse_encoder_dev[i].index = i + 1;
        snprintf(pulse_encoder_dev[i].pulse_dev_handle_name, sizeof(pulse_encoder_dev[i].pulse_dev_handle_name),
                 "pulse_encoder_dev%d", i + 1);
    }

    rt_device_t pulse_encoder_dev1 = RT_NULL;   /* 脉冲编码器设备句柄 */
    rt_device_t pulse_encoder_dev2 = RT_NULL;   /* 脉冲编码器设备句柄 */
    rt_device_t pulse_encoder_dev3 = RT_NULL;   /* 脉冲编码器设备句柄 */
    rt_device_t pulse_encoder_dev4 = RT_NULL;   /* 脉冲编码器设备句柄 */

    /* 查找脉冲编码器设备并传回设备句柄 */
    pulse_encoder_dev1 = rt_device_find(car_pulse_dev.lbp_dev);
    pulse_encoder_dev2 = rt_device_find(car_pulse_dev.lfp_dev);
    pulse_encoder_dev3 = rt_device_find(car_pulse_dev.rbp_dev);
    pulse_encoder_dev4 = rt_device_find(car_pulse_dev.rfp_dev);

    RT_ASSERT(pulse_encoder_dev1 != RT_NULL);
    RT_ASSERT(pulse_encoder_dev2 != RT_NULL);
    RT_ASSERT(pulse_encoder_dev3 != RT_NULL);
    RT_ASSERT(pulse_encoder_dev4 != RT_NULL);

    /* 以只读方式打开设备 */
    for (i = 0; i < 4; i++)
    {
        ret = rt_device_open(pulse_encoder_dev[i].pulse_dev_handle_name, RT_DEVICE_OFLAG_RDONLY);
        if (ret != RT_EOK)
        {
            rt_kprintf("open %s device failed!\n", pulse_encoder_dev[i].pulse_dev_handle_name);
            return ret;
        }
    }

    for (index = 0; index <= 10; index++)
    {
        rt_thread_mdelay(500);
        /* 读取脉冲编码器计数值 */
        ret = RT_EOK;

#ifndef USER_ENCODER_AVERAGE
        for (i = 0; i < 4; i++)
        {
            ret = rt_device_read(pulse_encoder_dev[i].pulse_dev_handle_name, 0, &count, 1);
            if (ret != RT_EOK)
            {
                rt_kprintf("read %s device failed!\n", pulse_encoder_dev[i].pulse_dev_handle_name);
                return ret;
            }
            else
            {
                rt_kprintf("Get %s: count %d\n", pulse_encoder_dev[i].pulse_dev_handle_name, count);
            }
        }
#else
        for (i = 0; i < 4; i++)
        {
            ret = rt_device_read(pulse_encoder_dev[i].pulse_dev_handle_name, 0, &count, 1);
            if (ret != RT_EOK)
            {
                rt_kprintf("read %s device failed!\n", pulse_encoder_dev[i].pulse_dev_handle_name);
                return ret;
            }
            count += count;
        }
        rt_kprintf("The average pulse value is %d\n", count / 4);
#endif

        /* 清空脉冲编码器计数值 */
        for (i = 0; i < 4; i++)
        {
            rt_device_control(pulse_encoder_dev[i].pulse_dev_handle_name, PULSE_ENCODER_CMD_CLEAR_COUNT, RT_NULL);
        }
    }

    for (i = 0; i < 4; i++)
    {
        ret = rt_device_close(pulse_encoder_dev[i].pulse_dev_handle_name);
        if (ret != RT_EOK)
        {
            rt_kprintf("close %s device failed!\n", pulse_encoder_dev[i].pulse_dev_handle_name);
            return ret;
        }
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pulse_encoder_dev_read, pulse encoder read);
