/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-20     Yifang       the first version
 */
#include "encoder_read.h"

struct pulse_dev car_pulse_dev[4] = {
    { ("pulse2"), 1 },
    { ("pulse3"), 2 },
    { ("pulse4"), 3 },
    { ("pulse5"), 4 }
};

struct pulse_dev_handle pulse_dev_handle_list[4];

//rt_device_t car_pulse_dev_handle

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

    /* 脉冲设备初始化 */
    for (i = 0; i < 4; i++)
    {
        pulse_dev_handle_list[i].pulse_dev_handle_name = RT_NULL;
        rt_kprintf("car_pulse_dev[%d].pulse_dev_name = %s\n", i, car_pulse_dev[i].pulse_dev_name);
        rt_kprintf("pulse_dev_handle_list[%d].pulse_dev_handle_name = %s\n", i, pulse_dev_handle_list[i].pulse_dev_handle_name);
    }

    /* 查找脉冲编码器设备并传回设备句柄 */
    for (i = 0; i < 4; i++)
    {
        rt_device_t dev1_handle = RT_NULL;

        pulse_dev_handle_list[i].index = i;
        pulse_dev_handle_list[i].pulse_dev_handle_name = (rt_device_t)rt_device_find(car_pulse_dev[i].pulse_dev_name);
        if (pulse_dev_handle_list[i].pulse_dev_handle_name == RT_NULL)
        {
            rt_kprintf("find %s device handle failed!\n", pulse_dev_handle_list[i].pulse_dev_handle_name);
            rt_kprintf("%s\n",pulse_dev_handle_list[i].pulse_dev_handle_name);
            return ret;
        }
        else
        {
            rt_kprintf("find %s device handle succeed!\n", pulse_dev_handle_list[i].pulse_dev_handle_name);
            rt_kprintf("%s\n",pulse_dev_handle_list[i].pulse_dev_handle_name);
        }
    }

    /* RT_ASSERT pulse encoder dev */
    for (i = 0; i < 4; i++)
    {
        RT_ASSERT(car_pulse_dev[i].pulse_dev_name != RT_NULL);
    }

    /* 以只读方式打开设备 */
    for (i = 0; i < 4; i++)
    {
        ret = rt_device_open(pulse_dev_handle_list[i].pulse_dev_handle_name, RT_DEVICE_OFLAG_RDONLY);
        if (ret != RT_EOK)
        {
            rt_kprintf("open %s device handle failed!\n", pulse_dev_handle_list[i].pulse_dev_handle_name);
            return ret;
        }
    }

    for (index = 0; index <= 100; index++)
    {
        rt_thread_mdelay(100);
        /* 读取脉冲编码器计数值 */
        ret = RT_EOK;

#ifndef USER_ENCODER_AVERAGE
        for (i = 0; i < 4; i++)
        {
            ret = rt_device_read(pulse_dev_handle_list[i].pulse_dev_handle_name, 0, &count, 1);
            if (ret == RT_NULL)
            {
                rt_kprintf("read %s device handle failed!\n", pulse_dev_handle_list[i].pulse_dev_handle_name);
                return ret;
            }
            else
            {
                rt_kprintf("Get %s: count %d\n", pulse_dev_handle_list[i].pulse_dev_handle_name, count);
            }
        }
#else
        for (i = 0; i < 4; i++)
        {
            ret = rt_device_read(pulse_dev_handle_list[i].pulse_dev_handle_name, 0, &count, 1);
            if (ret == RT_NULL)
            {
                rt_kprintf("read %s device handle failed!\n", pulse_dev_handle_list[i].pulse_dev_handle_name);
                return ret;
            }
            count += count;
        }
        rt_kprintf("The average pulse value is %d\n", count / 4);
#endif

        /* 清空脉冲编码器计数值 */
        for (i = 0; i < 4; i++)
        {
            rt_device_control(pulse_dev_handle_list[i].pulse_dev_handle_name, PULSE_ENCODER_CMD_CLEAR_COUNT, RT_NULL);
        }
    }

    /* 关闭编码器设备 */
    for (i = 0; i < 4; i++)
    {
        ret = rt_device_close(pulse_dev_handle_list[i].pulse_dev_handle_name);
        if (ret != RT_EOK)
        {
            rt_kprintf("close %s device handle failed!\n", pulse_dev_handle_list[i].pulse_dev_handle_name);
            return ret;
        }
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pulse_encoder_dev_read, pulse encoder read);
//INIT_APP_EXPORT(pulse_encoder_dev_read);
