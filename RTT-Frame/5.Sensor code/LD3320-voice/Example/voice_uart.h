/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-14     Yifang       the first version
 */
#ifndef APPLICATIONS_VOICE_UART_H_
#define APPLICATIONS_VOICE_UART_H_

#include <rtthread.h>

#define VOICE_UART_NAME       "uart1"      /* �����豸���� */

/* ���ڽ�����Ϣ�ṹ*/
struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};
/* �����豸��� */
rt_device_t voice_serial;
/* ��Ϣ���п��ƿ� */
static struct rt_messagequeue voice_uart_rx_mq;

int voice_thread_init(void);

#endif /* APPLICATIONS_VOICE_UART_H_ */
