/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-21     Yifang       the first version
 */
#ifndef APPLICATIONS_ENCODER_READ_H_
#define APPLICATIONS_ENCODER_READ_H_

//#define USER_ENCODER_AVERAGE      /* 是否开启脉冲均值数计算 */

struct pulse_dev
{
    rt_device_t lfp_dev;      /* 左前轮脉冲编码器设备 */
    rt_device_t rfp_dev;      /* 右前轮脉冲编码器设备 */
    rt_device_t lbp_dev;      /* 左后轮脉冲编码器设备 */
    rt_device_t rbp_dev;      /* 右后轮脉冲编码器设备 */
};

struct pulse_dev_handle
{
    char pulse_dev_handle_name[20];
    rt_int8_t index;
};

int pulse_encoder_dev_read(void *parameter);

#endif /* APPLICATIONS_ENCODER_READ_H_ */
