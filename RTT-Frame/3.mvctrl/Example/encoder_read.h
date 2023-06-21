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

//#define USER_ENCODER_AVERAGE      /* �Ƿ��������ֵ������ */

struct pulse_dev
{
    rt_device_t lfp_dev;      /* ��ǰ������������豸 */
    rt_device_t rfp_dev;      /* ��ǰ������������豸 */
    rt_device_t lbp_dev;      /* ���������������豸 */
    rt_device_t rbp_dev;      /* �Һ�������������豸 */
};

struct pulse_dev_handle
{
    char pulse_dev_handle_name[20];
    rt_int8_t index;
};

int pulse_encoder_dev_read(void *parameter);

#endif /* APPLICATIONS_ENCODER_READ_H_ */
