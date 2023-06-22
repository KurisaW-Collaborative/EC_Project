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

//初始化机器人参数结构体
Robot_Parament_Init  Robot_Parament;

void Robot_Init(double wheelspan, float axlespan, float gearratio, float encoderaccuracy,float wheeldiameter)
{
    //wheelspacing, Mec_Car is half wheelspacing
    //轮距 麦轮车为半轮距
    Robot_Parament.WheelSpan = wheelspan;
    //axlespacing, Mec_Car is half axlespacing
    //轴距 麦轮车为半轴距
    Robot_Parament.AxleSpan = axlespan;
    //motor_gear_ratio
    //电机减速比
    Robot_Parament.GearRatio = gearratio;
    //Number_of_encoder_lines
    //编码器精度(编码器线数)
    Robot_Parament.EncoderAccuracy = encoderaccuracy;
    //Diameter of driving wheel
    //主动轮直径
    Robot_Parament.WheelDiameter = wheeldiameter;


    //Encoder value corresponding to 1 turn of motor (wheel)
    //电机(车轮)转1圈对应的编码器数值
    Encoder_precision = EncoderMultiples * Robot_Parament.EncoderAccuracy * Robot_Parament.GearRatio;
    //Driving wheel circumference
    //主动轮周长
    Wheel_perimeter = Robot_Parament.WheelDiameter * PI;
    //wheelspacing, Mec_Car is half wheelspacing
    //轮距 麦轮车为半轮距
    Wheel_spacing = Robot_Parament.WheelSpan;
    //axlespacing, Mec_Car is half axlespacing
    //轴距 麦轮车为半轴距
    Axle_spacing = Robot_Parament.AxleSpan;
}
