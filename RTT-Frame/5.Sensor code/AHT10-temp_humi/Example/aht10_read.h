/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-18     Yifang       the first version
 */
#ifndef APPLICATIONS_AHT10_LIB_AHT10_READ_H_
#define APPLICATIONS_AHT10_LIB_AHT10_READ_H_

struct AHT10_DATA
{
    float temperature;
    float humidity;
};

void aht10_drv_init(void);
float aht10_temp_take(void);
float aht10_humi_take(void);

struct AHT10_DATA AHT10_read();

#endif /* APPLICATIONS_AHT10_LIB_AHT10_READ_H_ */
