/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-21     Yifang       the first version
 */
#ifndef APPLICATIONS_ROBOT_INIT_H_
#define APPLICATIONS_ROBOT_INIT_H_

typedef struct
{
    float WheelSpan;        // 轮距（半轮轮距）
    float AxleSpan;         // 轴距（半轴距）
    int GearRatio;          // 电机减速比
    int EncoderAccuracy;    // 编码器精度（编码器线数）
    float WheelDiameter;    // 主动轮直径
}Robot_Parament_Init;

#define PI 3.1415f  // PI

#define Akm_WheelSpan              0.162f      // 轮距 麦轮是一半
#define Akm_AxleSpan               0.144f      // 轴距 麦轮是一半
#define Mecanum_60                 0.060f      // 麦轮轮胎直径，明天测量下

#define MG513_GearRatio_30          30         // 电机减速比
#define MG513_EncoderAccuracy_13    13         // 编码器精度

#define EncoderMultiples           4           // 编码器倍频数，取决于编码器初始化设置
#define CONTROL_FREQUENCY          170         // 编码器数据读取频率

void Robot_Init(double wheelspan, float axlespan, float gearratio,float encoderaccuracy,float wheeldiameter);

#endif /* APPLICATIONS_ROBOT_INIT_H_ */
