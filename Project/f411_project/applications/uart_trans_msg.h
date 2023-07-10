/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     Yifang       the first version
 */
#ifndef APPLICATIONS_UART_TRANS_MSG_H_
#define APPLICATIONS_UART_TRANS_MSG_H_

#define SAMPLE_UART_NAME       "uart1"      /* 串口设备名称 */

/* 串口接收消息结构*/
struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};
/* 串口设备句柄 */
rt_device_t uart1_serial;
/* 消息队列控制块 */
static struct rt_messagequeue rx_mq;

#endif /* APPLICATIONS_UART_TRANS_MSG_H_ */
