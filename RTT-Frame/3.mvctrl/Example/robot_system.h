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

/************ 小车型号相关变量 **************************/
//Encoder accuracy
//编码器精度
float Encoder_precision;
//Wheel circumference, unit: m
//轮子周长，单位：m
float Wheel_perimeter;
//Drive wheel base, unit: m
//主动轮轮距，单位：m
float Wheel_spacing;
//The wheelbase of the front and rear axles of the trolley, unit: m
//小车前后轴的轴距，单位：m
float Axle_spacing;


#endif /* APPLICATIONS_ROBOT_SYSTEM_H_ */
