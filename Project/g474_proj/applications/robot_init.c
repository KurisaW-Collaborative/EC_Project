/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-21     Yifang       the first version
 */

#include "robot_system.h"

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "robot_init"
#include <rtdbg.h>

float Encoder_precision;                            // ����������
float Wheel_perimeter;                              // �����ܳ�����λ��m
float Wheel_spacing;                                // �������־࣬��λ��m
float Axle_spacing;                                 // С��ǰ�������࣬��λ��m

//��ʼ�������˲����ṹ��
Robot_Parament_Init  Robot_Parament;

void Robot_Init(double wheelspan, float axlespan, float gearratio, float encoderaccuracy,float wheeldiameter)
{
    rt_kprintf("\n");
    LOG_I("--------------- Initializes the robot parameter ---------------");
    //wheelspacing, Mec_Car is half wheelspacing
    //�־� ���ֳ�Ϊ���־�
    Robot_Parament.WheelSpan = wheelspan;
    //axlespacing, Mec_Car is half axlespacing
    //��� ���ֳ�Ϊ�����
    Robot_Parament.AxleSpan = axlespan;
    //motor_gear_ratio
    //������ٱ�
    Robot_Parament.GearRatio = gearratio;
    //Number_of_encoder_lines
    //����������(����������)
    Robot_Parament.EncoderAccuracy = encoderaccuracy;
    //Diameter of driving wheel
    //������ֱ��
    Robot_Parament.WheelDiameter = wheeldiameter;
    LOG_I("[wheelspan: %lf]", wheelspan);
    LOG_I("[axlespan: %f]", axlespan);
    LOG_I("[gearratio: %f]", gearratio);
    LOG_I("[encoder_accuracy: %f]", encoderaccuracy);
    rt_kprintf("\n");

    //Encoder value corresponding to 1 turn of motor (wheel)
    //���(����)ת1Ȧ��Ӧ�ı�������ֵ
    Encoder_precision = EncoderMultiples * Robot_Parament.EncoderAccuracy * Robot_Parament.GearRatio;
    //Driving wheel circumference
    //�������ܳ�
    Wheel_perimeter = Robot_Parament.WheelDiameter * PI;
    //wheelspacing, Mec_Car is half wheelspacing
    //�־� ���ֳ�Ϊ���־�
    Wheel_spacing = Robot_Parament.WheelSpan;
    //axlespacing, Mec_Car is half axlespacing
    //��� ���ֳ�Ϊ�����
    Axle_spacing = Robot_Parament.AxleSpan;
    LOG_I("[Encoder_precision: %f]", Encoder_precision);
    LOG_I("[Wheel_perimeter: %f]", Wheel_perimeter);
    LOG_I("[Axle_spacing: %f]", Axle_spacing);

    LOG_I("---------- Initializes the robot parameter finished! ----------");
    rt_kprintf("\n");
}
