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
    MOTOR_STOP,                 // ֹͣ
    MOTOR_FORWARD,              // ��ǰ�˶�
    MOTOR_BACKWARD,             // ����˶�
    MOTOR_LEFT,                 // �����ƶ�
    MOTOR_RIGHT,                // �����ƶ�
    MOTOR_FRONT_LEFT,           // ��ǰ�ƶ�
    MOTOR_FRONT_RIGHT,          // ��ǰ�ƶ�
    MOTOR_BACK_LEFT,            // ����ƶ�
    MOTOR_BACK_RIGHT,           // �Һ��ƶ�
    MOTOR_CLOCKWISE_SPIN,       // ˳ʱ����ת
    MOTOR_ANTICLOCKWISE_SPIN    // ��ʱ����ת
};

// ����ٶȿ�����ز����ṹ��
typedef struct
{
    float Encoder;          // ��������ֵ����ȡ���ʵʱ�ٶ�
    float Motor_Pwm;        // ���PWM��ֵ�����Ƶ��ʵʱ�ٶ�
    float Target;           // ���Ŀ���ٶ�ֵ�����Ƶ��Ŀ���ٶ�
    float Velocity_KP;      // �ٶȿ���PID����
    float   Velocity_KI;    // �ٶȿ���PID����
}Motor_parameter;

void car_pwm_channel_set(int fl_sta, int fr_sta, int bl_sta, int br_sta);
void car_control_mode_set(int status);

#endif /* APPLICATIONS_CAR_CONTROL_H_ */
