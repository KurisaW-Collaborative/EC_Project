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

rt_device_t voice_serial;
static struct rt_messagequeue voice_uart_rx_mq;

extern struct VOICE_TASK_FLAG vocie_task_flag[6];
extern rt_event_t voice_event;

/* �������ݻص����� */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;

    result = rt_mq_send(&voice_uart_rx_mq, &msg, sizeof(msg));
    if ( result == -RT_EFULL)
    {
        /* ��Ϣ������ */
        rt_kprintf("message queue full��\n");
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
        /* ����Ϣ�����ж�ȡ��Ϣ*/
        result = rt_mq_recv(&voice_uart_rx_mq, &msg, sizeof(msg), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* �Ӵ��ڶ�ȡ����*/
            rx_length = rt_device_read(msg.dev, 0, rx_buffer, msg.size);
            rx_buffer[rx_length] = '\0';
            /* ��ӡ���� */
            rt_kprintf("%s\n",rx_buffer);

            // �˴����������ݽ��յ�ִ�к���
            if(strcmp(rx_buffer,"weather") == 0)
            {
                /* ͨ�������豸 voice_serial �����ȡ������Ϣ */
                rt_device_write(voice_serial, 0, rx_buffer, rx_length);
                // �����ж�H7��UI�����Ƿ�ɹ�ִ�У�ִ�гɹ�����һ����־λ֪ͨ��ʹ�û���������

                rt_thread_mdelay(10000);
                // �жϱ�־λ�Ƿ���ȷ����ȷ��ִ��������߼�����
                _uart_send_impl(3);
//                vocie_task_flag[weather_fin].flag_val = 1;
//                rt_event_send(&voice_event, EVENT_WEATHER);

                rt_thread_mdelay(10000);
            }
            else if(strcmp(rx_buffer,"monitor") == 0)
            {
                /* ͨ�������豸 voice_serial �����ȡ������Ϣ */
                rt_device_write(voice_serial, 0, rx_buffer, rx_length);
                // �����ж�H7��UI�����Ƿ�ɹ�ִ�У�ִ�гɹ�����һ����־λ֪ͨ��ʹ�û���������
                rt_thread_mdelay(10000);
                // �жϱ�־λ�Ƿ���ȷ����ȷ��ִ��������߼�����
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

    /* ���Ҵ����豸 */
    voice_serial = rt_device_find(VOICE_UART_NAME);
    if (!voice_serial)
    {
        rt_kprintf("find %s failed!\n", VOICE_UART_NAME);
        return RT_ERROR;
    }

    /* ��ʼ����Ϣ���� */
    rt_mq_init(&voice_uart_rx_mq, "voice_uart_rx_mq",
               msg_pool,                 /* �����Ϣ�Ļ����� */
               sizeof(struct rx_msg),    /* һ����Ϣ����󳤶� */
               sizeof(msg_pool),         /* �����Ϣ�Ļ�������С */
               RT_IPC_FLAG_FIFO);        /* ����ж���̵߳ȴ������������ȵõ��ķ���������Ϣ */

    /* �� DMA ���ռ���ѯ���ͷ�ʽ�򿪴����豸 */
    rt_device_open(voice_serial, RT_DEVICE_FLAG_DMA_RX);

    /* ���ý��ջص����� */
    rt_device_set_rx_indicate(voice_serial, uart_input);

    /* ���� voice_serial �߳� */
    rt_thread_t thread = rt_thread_create("voice_serial", voice_uartl_thread_entry, RT_NULL, 1024, 25, 10);
    /* �����ɹ��������߳� */
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
/* ������ msh �����б��� */
//MSH_CMD_EXPORT(voice_thread_start, voice_thread_start);
//INIT_APP_EXPORT(voice_thread_start);
