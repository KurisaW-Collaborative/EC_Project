/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-22     Yifang       the first version
 */
/* 实现串口中断方式进行串口字符的读取 */
#include <rtthread.h>
#include <rtdevice.h>

#include "car_control.h"

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "ble_ctrl"
#include <rtdbg.h>

char ch_buf = 0;

/* 串口信号量 */
rt_sem_t uart3_rx_sem = RT_NULL;

struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;      /* 初始化配置参数 */

/* 串口设备句柄 */
rt_device_t serial_raspi;

/* 串口接收状态标记 */
rt_uint16_t USART_RX_STA;

#define uart_name "uart3"      /* 串口设备名称 */

static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_err_t result = RT_EOK;

    result = rt_sem_release(uart3_rx_sem);
    USART_RX_STA = 1;   //收到数据，标志位置1

    return result;
}

static char uart_getchar(void)
{


    /* 从串口读取一个字节的数据，没有读到则等待接收信号量 */
    while (rt_device_read(serial_raspi, -1, &ch_buf, 1) != 1)
    {
        /* 阻塞等待接收信号量，等到信号量后再次读取数据 */
        rt_sem_take(uart3_rx_sem, RT_WAITING_FOREVER);
        USART_RX_STA = 0;   //接收标志位清零
    }
    return ch_buf;
}


static void uart_ble_thread_entry(void *parameter)
{
    /* menu */
//    LOG_I("\x1b[2J\x1b[H");//执行清屏
    LOG_I("-------------------------------------------------");
    LOG_I("Please input your control mode or other function:");
    LOG_I("1. Car control      :please input (1)");
    LOG_I("2. Mpu9250 Function :please input (2)");
    LOG_I("3. exit menu        :please input <c> || <C>\r");
    LOG_I("-------------------------------------------------");

    while((ch_buf = (int)uart_getchar()) != RT_NULL)
    {
        LOG_I("Write data is 0x%x",ch_buf);
        //小车控制界面
        if(ch_buf == 0x31)
        {
//            LOG_I("\x1b[2J\x1b[H");//执行清屏
            LOG_I("--> MOTOR_STOP               :please input <p> || <P>\r");
            LOG_I("--> MOTOR_FORWARD            :please input <w> || <W>\r");
            LOG_I("--> MOTOR_BACKWARD           :please input <s> || <S>\r");
            LOG_I("--> MOTOR_LEFT               :please input <a> || <A>\r");
            LOG_I("--> MOTOR_RIGHT              :please input <d> || <D>\r");
            LOG_I("--> MOTOR_FRONT_LEFT         :please input <q> || <Q>\r");
            LOG_I("--> MOTOR_FRONT_RIGHT        :please input <e> || <E>\r");
            LOG_I("--> MOTOR_BACK_RIGHT         :please input <z> || <Z>\r");
            LOG_I("--> MOTOR_CLOCKWISE_SPIN     :please input <j> || <J>\r");
            LOG_I("--> MOTOR_ANTICLOCKWISE_SPIN :please input <l> || <L>\r");

            LOG_I("--> Car speed level 1         :please input <1>\r");
            LOG_I("--> Car speed level 2         :please input <2>\r");
            LOG_I("--> Car speed level 3         :please input <3>\r");


            while((ch_buf = (int)uart_getchar()) != RT_NULL)
            {
                //小车控制
                if (ch_buf == 'p' || ch_buf == 'P')
                {
//                    LOG_I("\n0x%x:stop",ch_buf);
                    car_control_mode_set(0);

                    continue;
                }
                else if (ch_buf == 'w' || ch_buf == 'W')
                {
//                    LOG_I("\n0x%x:car_forward",ch_buf);
                    car_control_mode_set(1);

                    continue;
                }
                else if (ch_buf == 's' || ch_buf == 'S')
                {
//                    LOG_I("\n0x%x:car_backup",ch_buf);
                    car_control_mode_set(2);

                    continue;
                }
                else if (ch_buf == 'a' || ch_buf == 'A')
                {
//                    LOG_I("\n0x%x:car_left",ch_buf);
                    car_control_mode_set(3);

                    continue;
                }
                else if (ch_buf == 'd' || ch_buf == 'D')
                {
//                    LOG_I("\n0x%x:car_right",ch_buf);
                    car_control_mode_set(4);

                    continue;
                }
                else if (ch_buf == 'q' || ch_buf == 'Q')
                {
//                    LOG_I("\n0x%x:car_FL",ch_buf);
                    car_control_mode_set(5);

                    continue;
                }
                else if (ch_buf == 'e' || ch_buf == 'E')
                {
//                    LOG_I("\n0x%x:car_FR",ch_buf);
                    car_control_mode_set(6);

                    continue;
                }
                else if (ch_buf == 'z' || ch_buf == 'Z')
                {
//                    LOG_I("\n0x%x:car_BL",ch_buf);
                    car_control_mode_set(7);

                    continue;
                }
                else if (ch_buf == 'c' || ch_buf == 'C')
                {
//                    LOG_I("\n0x%x:car_BR",ch_buf);
                    car_control_mode_set(8);

                    continue;
                }
                else if (ch_buf == 'j' || ch_buf == 'J')
                {
//                    LOG_I("\n0x%x:car_LCir",ch_buf);
                    car_control_mode_set(9);

                    continue;
                }
                else if (ch_buf == 'l' || ch_buf == 'L')
                {
//                    LOG_I("\n0x%x:car_RCir",ch_buf);
                    car_control_mode_set(10);

                    continue;
                }
                else if(ch_buf == '1')
                {
                    user_pwm_switch_level(1);
                    LOG_I("user_pwm_switch_level 1");
                    continue;
                }
                else if(ch_buf == '2')
                {
                    user_pwm_switch_level(2);
                    LOG_I("user_pwm_switch_level 2");
                    continue;
                }
                else if(ch_buf == '3')
                {
                    user_pwm_switch_level(3);
                    LOG_I("user_pwm_switch_level 3");
                    continue;
                }
                else if(ch_buf == 'k')
                {
                    LOG_I("\ncar control menu exit!");
                    break;
                }
            }
        }
        //退出菜单
        else if(ch_buf == 0x63)
        {
//            LOG_I("\x1b[2J\x1b[H");//执行清屏
            LOG_I("exit menu successful!");
            break;
        }
    }
}

int uart_raspi_init(void)
{
    char *buf;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;  /* 初始化配置参数 */

    uart3_rx_sem = rt_sem_create("uart3_rx_sem", 0, RT_IPC_FLAG_FIFO);

    serial_raspi = rt_device_find(uart_name);
    if(serial_raspi == RT_NULL)
    {
        LOG_E("find &s failed!\n",serial_raspi);
        return RT_ERROR;
    }

    /* step2：修改串口配置参数 */
    config.baud_rate = BAUD_RATE_9600;        //修改波特率为 9600
    config.data_bits = DATA_BITS_8;           //数据位 8
    config.stop_bits = STOP_BITS_1;           //停止位 1
    config.bufsz     = 128;                   //修改缓冲区 buff size 为 128
    config.parity    = PARITY_NONE;           //无奇偶校验位

    rt_device_open(serial_raspi,RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM | RT_DEVICE_OFLAG_RDWR); /* 中断轮询模式打开串口设备 */

    rt_device_control(serial_raspi, RT_DEVICE_CTRL_CONFIG, &config);

    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial_raspi, uart_input);

    rt_device_write(serial_raspi, 0, &buf, sizeof(&buf));

    rt_thread_t ret = rt_thread_create("uart_ble_thread", uart_ble_thread_entry, RT_NULL, 2048, 19, 100);
    rt_thread_startup(ret);

    return 0;
}
INIT_APP_EXPORT(uart_raspi_init);
//MSH_CMD_EXPORT(uart_raspi_init,uart_raspi_init);
