/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-10     Yifang       the first version
 */
#include <rtthread.h>
#include "voice_uart.h"
#include "voice_ctrl.h"

extern struct VOICE_TASK_FLAG vocie_task_flag[6];
extern rt_event_t voice_event;

/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;

    result = rt_mq_send(&voice_uart_rx_mq, &msg, sizeof(msg));
    if ( result == -RT_EFULL)
    {
        /* 消息队列满 */
        rt_kprintf("message queue full！\n");
    }
    return result;


    return RT_EOK;
}

static void voice_uartl_thread_entry(void *parameter)
{
    struct rx_msg msg;
    rt_err_t result;
    rt_uint32_t rx_length;
    static char rx_buffer[RT_SERIAL_RB_BUFSZ + 1];
//
    while (1)
    {
        rt_memset(&msg, 0, sizeof(msg));
        /* 从消息队列中读取消息*/
        result = rt_mq_recv(&voice_uart_rx_mq, &msg, sizeof(msg), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* 从串口读取数据*/
            rx_length = rt_device_read(msg.dev, 0, rx_buffer, msg.size);
            rx_buffer[rx_length] = '\0';
            /* 打印数据 */
            rt_kprintf("%s\n",rx_buffer);

            // 此处做串口数据接收的执行函数
            if(strcmp(rx_buffer,"weather") == 0)
            {
                /* 通过串口设备 voice_serial 输出读取到的消息 */
                rt_device_write(voice_serial, 0, rx_buffer, rx_length);
                // 首先判断H7的UI任务是否成功执行，执行成功后发送一个标志位通知，使用互斥量保护

                rt_thread_mdelay(10000);
                // 判断标志位是否正确，正确后执行下面的逻辑代码
                _uart_send_impl(3);
//                vocie_task_flag[weather_fin].flag_val = 1;
//                rt_event_send(&voice_event, EVENT_WEATHER);

                rt_thread_mdelay(10000);
            }
            else if(strcmp(rx_buffer,"monitor") == 0)
            {
                /* 通过串口设备 voice_serial 输出读取到的消息 */
                rt_device_write(voice_serial, 0, rx_buffer, rx_length);
                // 首先判断H7的UI任务是否成功执行，执行成功后发送一个标志位通知，使用互斥量保护
                rt_thread_mdelay(10000);
                // 判断标志位是否正确，正确后执行下面的逻辑代码
                _uart_send_impl(4);
//                vocie_task_flag[monitor_fin].flag_val = 1;
//                rt_event_send(&voice_event, EVENT_MONITOR);
                rt_thread_mdelay(10000);
            }
        }
    }
}

int voice_thread_start(void)
{
    rt_err_t ret = RT_EOK;
    static char msg_pool[256];

    /* 查找串口设备 */
    voice_serial = rt_device_find(VOICE_UART_NAME);
    if (!voice_serial)
    {
        rt_kprintf("find %s failed!\n", VOICE_UART_NAME);
        return RT_ERROR;
    }

    /* 初始化消息队列 */
    rt_mq_init(&voice_uart_rx_mq, "voice_uart_rx_mq",
               msg_pool,                 /* 存放消息的缓冲区 */
               sizeof(struct rx_msg),    /* 一条消息的最大长度 */
               sizeof(msg_pool),         /* 存放消息的缓冲区大小 */
               RT_IPC_FLAG_FIFO);        /* 如果有多个线程等待，按照先来先得到的方法分配消息 */

    /* 以 DMA 接收及轮询发送方式打开串口设备 */
    rt_device_open(voice_serial, RT_DEVICE_FLAG_DMA_RX);

    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(voice_serial, uart_input);

    /* 创建 voice_serial 线程 */
    rt_thread_t thread = rt_thread_create("voice_serial", voice_uartl_thread_entry, RT_NULL, 1024, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
//MSH_CMD_EXPORT(voice_thread_start, voice_thread_start);
//INIT_APP_EXPORT(voice_thread_start);
