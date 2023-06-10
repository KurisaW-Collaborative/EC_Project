/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Yifang       the first version
 */
#ifndef APPLICATIONS_USER_DRV_MPU9250_MPU9250_CONFIG_H_
#define APPLICATIONS_USER_DRV_MPU9250_MPU9250_CONFIG_H_

#include <rtdevice.h>
#include "drv_gpio.h"
#include "stm32f4xx_hal.h"

#define MPU9250_SPI         hspi1
#define MPU9250_CS_PIN      GET_PIN(A,8)

extern SPI_HandleTypeDef hspi1;

void MX_SPI1_Init(void);

#endif /* APPLICATIONS_USER_DRV_MPU9250_MPU9250_CONFIG_H_ */
