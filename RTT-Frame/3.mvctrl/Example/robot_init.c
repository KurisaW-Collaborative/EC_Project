/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-21     Yifang       the first version
 */

#include "robot_init.h"
#include "robot_system.h"

//��ʼ�������˲����ṹ��
Robot_Parament_Init  Robot_Parament;

void Robot_Init(double wheelspan, float axlespan, float gearratio, float encoderaccuracy,float wheeldiameter)
{
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
}
