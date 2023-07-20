/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-22     Yifang       the first version
 */
#ifndef APPLICATIONS_ROBOT_SYSTEM_H_
#define APPLICATIONS_ROBOT_SYSTEM_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "car_control.h"
#include "encoder_read.h"
#include "mpu9250_config.h"
#include "pwm_control.h"
#include "robot_init.h"

/************ 小车型号相关变量 **************************/

float Encoder_precision;                            // 编码器精度
float Wheel_perimeter;                              // 轮子周长，单位：m
float Wheel_spacing;                                // 主动轮轮距，单位：m
float Axle_spacing;                                 // 小车前后轴的轴距，单位：m

Motor_parameter MOTOR_A, MOTOR_B, MOTOR_C, MOTOR_D; // 电机的参数结构体

void robot_system_init(void);

#endif /* APPLICATIONS_ROBOT_SYSTEM_H_ */
