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

/************ С���ͺ���ر��� **************************/

float Encoder_precision;                            // ����������
float Wheel_perimeter;                              // �����ܳ�����λ��m
float Wheel_spacing;                                // �������־࣬��λ��m
float Axle_spacing;                                 // С��ǰ�������࣬��λ��m

Motor_parameter MOTOR_A, MOTOR_B, MOTOR_C, MOTOR_D; // ����Ĳ����ṹ��

void robot_system_init(void);

#endif /* APPLICATIONS_ROBOT_SYSTEM_H_ */
