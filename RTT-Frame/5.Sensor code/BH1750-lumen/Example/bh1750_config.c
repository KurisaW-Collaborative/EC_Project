/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-05     Yifang       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "sensor.h"
#define DBG_ENABLE
#define DBG_SECTION_NAME "bh1750"
#define DBG_LEVEL DBG_LOG
#define DBG_COLOR
#include <rtdbg.h>

struct rt_sensor_data bh1750_data;
const char *bh1750_drv_name = "li_bh175";

rt_device_t bh1750_dev = RT_NULL;
static rt_size_t res, i;

void bh1750_drv_init(void *parameter)
{
    bh1750_dev = rt_device_find(bh1750_drv_name);
    if (bh1750_dev == RT_NULL)
    {
        rt_kprintf("Can't find device:%s\n", bh1750_drv_name);
        return;
    }

    if (rt_device_open(bh1750_dev, RT_DEVICE_FLAG_RDONLY) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return;
    }

    for (i = 0; i < 50; i++)
    {
        /* 从传感器读取一个数据 */
        res = rt_device_read(bh1750_dev, 0, &bh1750_data, 1);
        if (res != 1)
        {
            rt_kprintf("read data failed!size is %d", res);
        }
        else
        {
            rt_kprintf("num:%3d, light:%5d lux, timestamp:%5d\n", i, bh1750_data.data.light, bh1750_data.timestamp);
        }
        rt_thread_mdelay(100);
    }
    /* 关闭传感器设备 */
    rt_device_close(bh1750_dev);
}
MSH_CMD_EXPORT(bh1750_drv_init, bh1750 sensor device sample);

