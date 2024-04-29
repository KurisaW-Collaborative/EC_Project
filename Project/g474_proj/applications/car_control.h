/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-21     Yifang       the first version
 */
#ifndef APPLICATIONS_CAR_CONTROL_H_
#define APPLICATIONS_CAR_CONTROL_H_

#include <rtthread.h>
#include <rtdevice.h>

// 电机通道引脚结构体
struct motor_channel_pin
{
    rt_base_t   pin_handle;
    rt_int8_t   index;
};

// 定义车辆运动状态枚举
enum car_mode_set
{
    foreward,   // 向前
    reversal,   // 退后
    stop        // 停止
};

// 定义电机状态枚举
enum MotorState
{
    MOTOR_STOP,                 // 停止:0
    MOTOR_FORWARD,              // 向前运动:1
    MOTOR_BACKWARD,             // 向后运动:2
    MOTOR_LEFT,                 // 向左移动:3
    MOTOR_RIGHT,                // 向右移动:4
    MOTOR_FRONT_LEFT,           // 左前移动:5
    MOTOR_FRONT_RIGHT,          // 右前移动:6
    MOTOR_BACK_LEFT,            // 左后移动:7
    MOTOR_BACK_RIGHT,           // 右后移动:8
    MOTOR_CLOCKWISE_SPIN,       // 顺时针旋转:9
    MOTOR_ANTICLOCKWISE_SPIN    // 逆时针旋转:10
};

// 电机速度控制相关参数结构体
typedef struct
{
    float Encoder;          // 编码器数值，读取电机实时速度
//    int Motor_Pwm;        // 电机PWM数值，控制电机实时速度
    float Target;           // 电机目标速度值，控制电机目标速度
    float Velocity_KP;      // 速度控制PID参数
    float Velocity_KI;    // 速度控制PID参数
}Motor_parameter;

void car_control_mode_set(int status);
void car_pwm_channel_init(void);

#endif /* APPLICATIONS_CAR_CONTROL_H_ */
