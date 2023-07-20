/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-14     ���ӵ�Ƥ       the first version
 */
#ifndef APPLICATIONS_DATA_COMMUNICATION_DATA_COMMUNICATION_H_
#define APPLICATIONS_DATA_COMMUNICATION_DATA_COMMUNICATION_H_


#include <rtthread.h>
#include <rtdevice.h>
#include "user_ui/ui.h"

#define TEMPERATURE_TYPE    "temperature"
#define HUMIDITY_TYPE       "humidity"
#define AIR_PRESSURE_TYPE   "air_pressure"
#define ILLNUMINATION_TYPE   "illumination"
#define TIME_TYPE_HOUR      "time_hour"
#define TIME_TYPE_MINUTE    "time_minute"
#define TIME_TYPE_SECOND    "time_secnod"
#define TIME_TYPE_WDAY    "time_wday"

#define COMMUNICAtION_MAX_DATA_LEN 65
void set_communication_uart(char* uart_name);//����ʹ�õĴ���

void enable_lvgl_rsmg();//����ͨ������lvgl����
void disable_lvgl_rsmg();//�ر�ͨ������lvgl����
void communication_send(char* str);//�������ݸ�����������

#endif /* APPLICATIONS_DATA_COMMUNICATION_DATA_COMMUNICATION_H_ */
