/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-14     Yifang       the first version
 */
#ifndef APPLICATIONS_BMP280_READ_H_
#define APPLICATIONS_BMP280_READ_H_

#include "bmp280_lib/bmp280.h"
#include "stm32f4xx_hal.h"
#include <board.h>

extern I2C_HandleTypeDef hi2c1;

float bmp280_read(void);

#endif /* APPLICATIONS_BMP280_READ_H_ */
