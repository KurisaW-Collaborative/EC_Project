/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-08     Yifang       the first version
 */
#ifndef APPLICATIONS_AIR_QUALITY_MTOR_H_
#define APPLICATIONS_AIR_QUALITY_MTOR_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define GP2Y_PIN    GET_PIN(B,13)

#define GP2Y_High rt_pin_write(GP2Y_PIN,PIN_HIGH)
#define GP2Y_Low  rt_pin_write(GP2Y_PIN,PIN_LOW)

#endif /* APPLICATIONS_AIR_QUALITY_MTOR_H_ */
