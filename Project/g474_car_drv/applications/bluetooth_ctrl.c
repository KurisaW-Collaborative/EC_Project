/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-22     Yifang       the first version
 */
/* ʵ�ִ����жϷ�ʽ���д����ַ��Ķ�ȡ */
#include <rtthread.h>
#include <rtdevice.h>

#include "car_control.h"

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "ble_ctrl"
#include <rtdbg.h>

char ch_buf = 0;

/* �����ź��� */
rt_sem_t uart3_rx_sem = RT_NULL;

struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;      /* ��ʼ�����ò��� */

/* �����豸��� */
rt_device_t serial_raspi;

/* ���ڽ���״̬��� */
rt_uint16_t USART_RX_STA;

#define uart_name "uart3"      /* �����豸���� */

static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_err_t result = RT_EOK;

    result = rt_sem_release(uart3_rx_sem);
    USART_RX_STA = 1;   //�յ����ݣ���־λ��1

    return result;
}

static char uart_getchar(void)
{
    /* �Ӵ��ڶ�ȡһ���ֽڵ����ݣ�û�ж�����ȴ������ź��� */
    while (rt_device_read(serial_raspi, -1, &ch_buf, 1) != 1)
    {
        /* �����ȴ������ź������ȵ��ź������ٴζ�ȡ���� */
        rt_sem_take(uart3_rx_sem, RT_WAITING_FOREVER);
        USART_RX_STA = 0;   //���ձ�־λ����
    }
    return ch_buf;
}


static void uart_raspi_thread_entry(void *parameter)
{
    /* menu */
//    LOG_I("\x1b[2J\x1b[H");//ִ������
    LOG_I("-------------------------------------------------");
    LOG_I("Please input your control mode or other function:");
    LOG_I("1. Car control      :please input (1)");
    LOG_I("2. Mpu6050 Function :please input (2)");
    LOG_I("3. exit menu        :please input <c> || <C>\r");
    LOG_I("-------------------------------------------------");

    while((ch_buf = (int)uart_getchar()) != RT_NULL)
    {
        LOG_I("Write data is 0x%x",ch_buf);
        //С�����ƽ���
        if(ch_buf == 0x31)
        {
//            LOG_I("\x1b[2J\x1b[H");//ִ������
            LOG_I("--> car go forward      :please input <f> || <F>\r");
            LOG_I("--> car go backup       :please input <b> || <B>\r");
            LOG_I("--> car turn left       :please input <l> || <L>\r");
            LOG_I("--> car turn right      :please input <r> || <R>\r");
            LOG_I("--> car stop            :please input <p> || <P>\r");
            LOG_I("--> [car speed] level 1       :please input <1>\r");
            LOG_I("--> [car speed] level 2       :please input <2>\r");
            LOG_I("--> [car speed] level 3       :please input <3>\r");
            LOG_I("--> car control exit    :please input <ctl+c>");

            while((ch_buf = (int)uart_getchar()) != RT_NULL)
            {
                //С������
                if (ch_buf == 'p')
                {
//                    LOG_I("\n0x%x:stop",ch_buf);
                    car_control_mode_set(0);

                    continue;
                }
                else if (ch_buf == 'w')
                {
//                    LOG_I("\n0x%x:car_forward",ch_buf);
                    car_control_mode_set(1);

                    continue;
                }
                else if (ch_buf == 's')
                {
//                    LOG_I("\n0x%x:car_backup",ch_buf);
                    car_control_mode_set(2);

                    continue;
                }
                else if (ch_buf == 'a')
                {
//                    LOG_I("\n0x%x:car_left",ch_buf);
                    car_control_mode_set(3);

                    continue;
                }
                else if (ch_buf == 'd')
                {
//                    LOG_I("\n0x%x:car_right",ch_buf);
                    car_control_mode_set(4);

                    continue;
                }
                else if (ch_buf == 'q')
                {
//                    LOG_I("\n0x%x:car_FL",ch_buf);
                    car_control_mode_set(5);

                    continue;
                }
                else if (ch_buf == 'e')
                {
//                    LOG_I("\n0x%x:car_FR",ch_buf);
                    car_control_mode_set(6);

                    continue;
                }
                else if (ch_buf == 'z')
                {
//                    LOG_I("\n0x%x:car_BL",ch_buf);
                    car_control_mode_set(7);

                    continue;
                }
                else if (ch_buf == 'c')
                {
//                    LOG_I("\n0x%x:car_BR",ch_buf);
                    car_control_mode_set(8);

                    continue;
                }
                else if (ch_buf == 'j')
                {
//                    LOG_I("\n0x%x:car_LCir",ch_buf);
                    car_control_mode_set(9);

                    continue;
                }
                else if (ch_buf == 'l')
                {
//                    LOG_I("\n0x%x:car_RCir",ch_buf);
                    car_control_mode_set(10);

                    continue;
                }
                else if(ch_buf == '1')
                {
                    user_pwm_switch_level(1);
                    LOG_I("user_pwm_switch_level 1");
                }
                else if(ch_buf == '2')
                {
                    user_pwm_switch_level(2);
                    LOG_I("user_pwm_switch_level 2");
                }
                else if(ch_buf == '3')
                {
                    user_pwm_switch_level(3);
                    LOG_I("user_pwm_switch_level 3");
                }
                else if(ch_buf == 'k')
                {
                    LOG_I("\ncar control exit");
                    break;
                }
            }
        }
        //�˳��˵�
        else if(ch_buf == 0x63)
        {
//            LOG_I("\x1b[2J\x1b[H");//ִ������
            LOG_I("exit menu successful!");
            break;
        }
    }
}

int uart_raspi_init(void)
{
    char *buf;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;  /* ��ʼ�����ò��� */

    uart3_rx_sem = rt_sem_create("uart3_rx_sem", 0, RT_IPC_FLAG_FIFO);

    serial_raspi = rt_device_find(uart_name);
    if(serial_raspi == RT_NULL)
    {
        LOG_E("find &s failed!\n",serial_raspi);
        return RT_ERROR;
    }

    /* step2���޸Ĵ������ò��� */
    config.baud_rate = BAUD_RATE_9600;        //�޸Ĳ�����Ϊ 9600
    config.data_bits = DATA_BITS_8;           //����λ 8
    config.stop_bits = STOP_BITS_1;           //ֹͣλ 1
    config.bufsz     = 128;                   //�޸Ļ����� buff size Ϊ 128
    config.parity    = PARITY_NONE;           //����żУ��λ

    rt_device_open(serial_raspi,RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM | RT_DEVICE_OFLAG_RDWR); /* �ж���ѯģʽ�򿪴����豸 */

    rt_device_control(serial_raspi, RT_DEVICE_CTRL_CONFIG, &config);

    /* ���ý��ջص����� */
    rt_device_set_rx_indicate(serial_raspi, uart_input);

    rt_device_write(serial_raspi, 0, &buf, sizeof(&buf));

    rt_thread_t ret = rt_thread_create("uart_raspi_thread", uart_raspi_thread_entry, RT_NULL, 2048, 19, 100);
    rt_thread_startup(ret);

    return 0;
}
INIT_APP_EXPORT(uart_raspi_init);
//MSH_CMD_EXPORT(uart_raspi_init,uart_raspi_init);
