/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-05     Yifang       the first version
 */
#ifndef APPLICATIONS_USER_DRV_BH1750_SENSOR_ROHM_BH1750_H_
#define APPLICATIONS_USER_DRV_BH1750_SENSOR_ROHM_BH1750_H_

#include <sensor.h>

int rt_hw_bh1750_init(const char *name, struct rt_sensor_config *cfg);

#endif /* APPLICATIONS_USER_DRV_BH1750_SENSOR_ROHM_BH1750_H_ */
