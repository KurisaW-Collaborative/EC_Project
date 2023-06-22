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

/************ С���ͺ���ر��� **************************/
//Encoder accuracy
//����������
float Encoder_precision;
//Wheel circumference, unit: m
//�����ܳ�����λ��m
float Wheel_perimeter;
//Drive wheel base, unit: m
//�������־࣬��λ��m
float Wheel_spacing;
//The wheelbase of the front and rear axles of the trolley, unit: m
//С��ǰ�������࣬��λ��m
float Axle_spacing;


#endif /* APPLICATIONS_ROBOT_SYSTEM_H_ */
