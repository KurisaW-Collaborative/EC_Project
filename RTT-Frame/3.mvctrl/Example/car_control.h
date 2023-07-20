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

// ���ͨ�����Žṹ��
struct motor_channel_pin
{
    rt_base_t   pin_handle;
    rt_int8_t   index;
};

// ���峵���˶�״̬ö��
enum car_mode_set
{
    foreward,   // ��ǰ
    reversal,   // �˺�
    stop        // ֹͣ
};

// ������״̬ö��
enum MotorState
{
    MOTOR_STOP,                 // ֹͣ:0
    MOTOR_FORWARD,              // ��ǰ�˶�:1
    MOTOR_BACKWARD,             // ����˶�:2
    MOTOR_LEFT,                 // �����ƶ�:3
    MOTOR_RIGHT,                // �����ƶ�:4
    MOTOR_FRONT_LEFT,           // ��ǰ�ƶ�:5
    MOTOR_FRONT_RIGHT,          // ��ǰ�ƶ�:6
    MOTOR_BACK_LEFT,            // ����ƶ�:7
    MOTOR_BACK_RIGHT,           // �Һ��ƶ�:8
    MOTOR_CLOCKWISE_SPIN,       // ˳ʱ����ת:9
    MOTOR_ANTICLOCKWISE_SPIN    // ��ʱ����ת:10
};

// ����ٶȿ�����ز����ṹ��
typedef struct
{
    float Encoder;          // ��������ֵ����ȡ���ʵʱ�ٶ�
//    int Motor_Pwm;        // ���PWM��ֵ�����Ƶ��ʵʱ�ٶ�
    float Target;           // ���Ŀ���ٶ�ֵ�����Ƶ��Ŀ���ٶ�
    float Velocity_KP;      // �ٶȿ���PID����
    float Velocity_KI;    // �ٶȿ���PID����
}Motor_parameter;

void car_control_mode_set(int status);
void car_pwm_channel_init(void);

#endif /* APPLICATIONS_CAR_CONTROL_H_ */
