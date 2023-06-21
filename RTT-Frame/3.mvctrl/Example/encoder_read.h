/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-21     Yifang       the first version
 */
#ifndef APPLICATIONS_ENCODER_READ_H_
#define APPLICATIONS_ENCODER_READ_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

struct pulse_dev
{
    rt_device_t pulse_dev_name;
    rt_int8_t index;
};

struct pulse_dev_handle
{
    rt_device_t pulse_dev_handle_name;
    rt_int8_t index;
};

int pulse_encoder_dev_read(void *parameter);

#endif /* APPLICATIONS_ENCODER_READ_H_ */
