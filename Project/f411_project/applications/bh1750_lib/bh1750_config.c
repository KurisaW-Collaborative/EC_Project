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
#include <board.h>

extern I2C_HandleTypeDef hi2c3;

#include "bh1750_lib/bh1750.h"

static float BH1750_lux;
BH1750_Data sensor;

void bh1750_drv_init(void)
{
    MX_I2C3_Init();

    sensor = BH1750_Init(CONT_HI_RES, ADDR_0V, &hi2c3);

    rt_kprintf("[weather] bh1750_drv_init success!\r\n");
}
//MSH_CMD_EXPORT(bh1750_drv_init, bh1750 sensor device sample);
//INIT_APP_EXPORT(bh1750_drv_init);

float bh1750_read(void)
{
    BH1750_lux = BH1750_Read(&sensor);
//    rt_kprintf("BH1750_lux:%f\n",BH1750_lux);

    return BH1750_lux;
}
MSH_CMD_EXPORT(bh1750_read,bh1750_read);

