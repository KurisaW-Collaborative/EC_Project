/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-18     Yifang       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "aht10.h"
#include "aht10_read.h"

#define AHT_DEV_NAME "i2c2"

aht10_device_t aht10_dev = RT_NULL;

void aht10_drv_init(void)
{
    aht10_dev = aht10_init(AHT_DEV_NAME);
    if(aht10_dev == RT_NULL)
    {
        rt_kprintf("aht10_init failed!\n");
    }
    rt_kprintf("[weather] aht10_user_init success!\n");
}

struct AHT10_DATA AHT10_read()
{
    struct AHT10_DATA data;

    float temp_ini,humi_ini;

    temp_ini = aht10_read_temperature(aht10_dev);
    humi_ini = aht10_read_humidity(aht10_dev);

    data.temperature = temp_ini;
    data.humidity = humi_ini;

    // 返回结构体变量
    return data;
}


float aht10_temp_take(void)
{
    float temp = aht10_read_temperature(aht10_dev);

    return temp;
}
MSH_CMD_EXPORT(aht10_temp_take,aht10_temp_take);

float aht10_humi_take(void)
{
    float humi = aht10_read_humidity(aht10_dev);

    return humi;
}
MSH_CMD_EXPORT(aht10_humi_take,aht10_humi_take);
