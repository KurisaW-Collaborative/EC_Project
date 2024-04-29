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
#include "robot_system.h"

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

// 编码器结构体
typedef struct
{
    int A;
    int B;
    int C;
    int D;
}Encoder;

int pulse_encoder_dev_read(void *parameter);
float Get_Vercel_Encoder(char target);
rt_err_t encoder_read_thread(void);

void Set_Motor_Speed(uint8_t motor_num, double speed_percentage);
int encoder_value_take(uint8_t TIMx);
rt_bool_t encoder_state_take(uint8_t TIMx);
rt_err_t encoder_start(uint8_t TIMx);
rt_err_t encoder_end(uint8_t TIMx);

uint32_t ReverseResolveEncoderValue(float velocity); // 反向解析返回脉冲值

#endif /* APPLICATIONS_ENCODER_READ_H_ */
