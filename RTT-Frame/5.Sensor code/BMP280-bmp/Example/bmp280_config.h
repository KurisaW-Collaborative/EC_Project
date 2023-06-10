/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Yifang       the first version
 */
#ifndef APPLICATIONS_USER_DRV_BMP280_BMP280_CONFIG_H_
#define APPLICATIONS_USER_DRV_BMP280_BMP280_CONFIG_H_

#include "bmp280.h"
#include "stm32f4xx_hal.h"
#include <board.h>

extern I2C_HandleTypeDef hi2c2;

void MX_I2C2_Init(void);

#endif /* APPLICATIONS_USER_DRV_BMP280_BMP280_CONFIG_H_ */
