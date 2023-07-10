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
#include "voice_ctrl.h"
#include "uart_trans_msg.h"

/* �������ݻص����� */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;

    result = rt_mq_send(&rx_mq, &msg, sizeof(msg));
    if ( result == -RT_EFULL)
    {
        /* ��Ϣ������ */
        rt_kprintf("message queue full��\n");
    }
    return result;
}

static void serial_thread_entry(void *parameter)
{
    struct rx_msg msg;
    rt_err_t result;
    rt_uint32_t rx_length;
    static char rx_buffer[RT_SERIAL_RB_BUFSZ + 1];

    while (1)
    {
        rt_memset(&msg, 0, sizeof(msg));
        /* ����Ϣ�����ж�ȡ��Ϣ*/
        result = rt_mq_recv(&rx_mq, &msg, sizeof(msg), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* �Ӵ��ڶ�ȡ����*/
            rx_length = rt_device_read(msg.dev, 0, rx_buffer, msg.size);
            rx_buffer[rx_length] = '\0';
            /* ͨ�������豸 uart1_serial �����ȡ������Ϣ */
            rt_device_write(uart1_serial, 0, rx_buffer, rx_length);
            /* ��ӡ���� */
            rt_kprintf("%s\n",rx_buffer);

            // �˴����������ݽ��յ�ִ�к���
            if(strcmp(rx_buffer,"weather") == 0)
            {
                // �����ж�H7��UI�����Ƿ�ɹ�ִ�У�ִ�гɹ�����һ����־λ֪ͨ��ʹ�û���������

                // �жϱ�־λ�Ƿ���ȷ����ȷ��ִ��������߼�����
                _uart_send_impl(3);
                rt_thread_mdelay(10000);
            }
            else if(strcmp(rx_buffer,"monitor") == 0)
            {
                // �����ж�H7��UI�����Ƿ�ɹ�ִ�У�ִ�гɹ�����һ����־λ֪ͨ��ʹ�û���������

                // �жϱ�־λ�Ƿ���ȷ����ȷ��ִ��������߼�����
                _uart_send_impl(4);
                rt_thread_mdelay(10000);
            }
        }
    }
}

static int uart_dma_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    static char msg_pool[256];
    char str[] = "hello RT-Thread!\r\n";

    /* ���Ҵ����豸 */
    uart1_serial = rt_device_find(SAMPLE_UART_NAME);
    if (!uart1_serial)
    {
        rt_kprintf("find %s failed!\n", SAMPLE_UART_NAME);
        return RT_ERROR;
    }

    /* ��ʼ����Ϣ���� */
    rt_mq_init(&rx_mq, "rx_mq",
               msg_pool,                 /* �����Ϣ�Ļ����� */
               sizeof(struct rx_msg),    /* һ����Ϣ����󳤶� */
               sizeof(msg_pool),         /* �����Ϣ�Ļ�������С */
               RT_IPC_FLAG_FIFO);        /* ����ж���̵߳ȴ������������ȵõ��ķ���������Ϣ */

    /* �� DMA ���ռ���ѯ���ͷ�ʽ�򿪴����豸 */
    rt_device_open(uart1_serial, RT_DEVICE_FLAG_DMA_RX);
    /* ���ý��ջص����� */
    rt_device_set_rx_indicate(uart1_serial, uart_input);
    /* �����ַ��� */
    rt_device_write(uart1_serial, 0, str, (sizeof(str) - 1));

    /* ���� uart1_serial �߳� */
    rt_thread_t thread = rt_thread_create("uart1_serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
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
//MSH_CMD_EXPORT(uart_dma_sample, uart device dma sample);
INIT_APP_EXPORT(uart_dma_sample);
