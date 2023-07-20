/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     Yifang       the first version
 */

#define DBG_TAG "nmea"
#define DBG_LVL DBG_LOG
#include "gps_recv.h"

#include <rtthread.h>
#include <rtdevice.h>

#define GPS_DEVICE_NAME     "uart2" // 换用finsh命令行的串口设备

char gps_upload_data[128];

/* 串口接收消息结构*/
struct gps_rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};

static rt_device_t gps_serial;
static struct rt_messagequeue gps_rx_mq;

/* 接收数据回调函数 */
static rt_err_t gps_uart_input(rt_device_t dev, rt_size_t size)
{
    struct gps_rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;

    result = rt_mq_send(&gps_rx_mq, &msg, sizeof(msg));
    if (result == -RT_EFULL)
    {
        /* 消息队列满 */
        rt_kprintf("message queue full！\n");
    }
    return result;
}

static double char_to_double(char* str)
{
    double ret = 0;
    int i =0;
    for(;str[i] != '.';i++)
    {
        ret *=10;
        ret += str[i] - '0';
    }
    i++;

    int len = 1;
    double decimals = 0;
    for(;str[i] != '\0';i++)
    {
        len = len *10;
        decimals *=10;
        decimals += str[i] - '0';
    }
    decimals = decimals / len;
    ret += decimals;
    return ret;
}

static void parse_jw(char *str ,gpsINFO* info)
{
    int i = 0;
    char gps_analy_data[RT_SERIAL_RB_BUFSZ + 1];
    int ss_index = 0;
    while(str[i++] != ',');
    //解析纬度
    for(;str[i] != ',';i++)
    {
        gps_analy_data[ss_index++] = str[i];
    }
    i++;
    gps_analy_data[ss_index] = '\0';
    info->lat = char_to_double(gps_analy_data);
    while(str[i++] != ',');
    //解析纬度

    rt_memset(gps_analy_data, 0, sizeof (gps_analy_data));
    ss_index = 0;
    for(;str[i] != ',';i++)
    {
        gps_analy_data[ss_index++] = str[i];
    }
    i++;
    gps_analy_data[ss_index] = '\0';
    info->lon = char_to_double(gps_analy_data);
}

static void nmea_thread_entry(void *parameter)
{
    struct gps_rx_msg msg;
    rt_err_t result;
    rt_uint32_t rx_length;
    static char rx_buffer[RT_SERIAL_RB_BUFSZ + 1];

    gpsINFO info = {0,0};          //GPS解码后得到的信息

    char gpsstr_buffer[RT_SERIAL_RB_BUFSZ + 1];
    int gpsstr_buffer_index =0;
    while (1)
    {
        rt_memset(&msg, 0, sizeof(msg));
        /* 从消息队列中读取消息*/
        result = rt_mq_recv(&gps_rx_mq, &msg, sizeof(msg), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            /* 从串口读取数据*/
            rx_length = rt_device_read(msg.dev, 0, rx_buffer, msg.size);

            rx_buffer[rx_length] = '\0';

            int flag = 0;
            for(int i=0 ; i != rx_length; i++)
            {
                if(rx_buffer[i] == '\n')
                {
                    flag =1;
                    break;
                }
                gpsstr_buffer[gpsstr_buffer_index++] = rx_buffer[i];
            }

            if(!flag) continue;


            gpsstr_buffer[gpsstr_buffer_index] = '\0';
            if(rt_strstr(gpsstr_buffer, "$GNGLL") != NULL)
            {
                parse_jw(gpsstr_buffer,&info);
            }
            else
            {
                gpsstr_buffer_index = 0;
                rt_memset(&gpsstr_buffer, 0, sizeof(gpsstr_buffer));
                continue;
            }

            gpsstr_buffer_index = 0;
            rt_memset(&gpsstr_buffer, 0, sizeof(gpsstr_buffer));

            snprintf(gps_upload_data, 128, "wd:%f,jd:%f", info.lat/100, info.lon/100);
        }
    }
}
//参数为nmea库想要解析的串口名称
int gps_thread_start(void)
{
    rt_err_t ret = RT_EOK;
    static char msg_pool[256];

    /* 查找串口设备 */
    gps_serial = rt_device_find(GPS_DEVICE_NAME);
    /* 初始化消息队列 */
    rt_mq_init(&gps_rx_mq, "gps_rx_mq", msg_pool, sizeof(struct gps_rx_msg), sizeof(msg_pool), RT_IPC_FLAG_FIFO);

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    config.baud_rate = BAUD_RATE_9600;        //修改波特率为 9600
    config.data_bits = DATA_BITS_8;           //数据位 8
    config.stop_bits = STOP_BITS_1;           //停止位 1
    config.bufsz     = 128;                   //修改缓冲区 buff size 为 128
    config.parity    = PARITY_NONE;           //无奇偶校验位

    rt_device_control(gps_serial, RT_DEVICE_CTRL_CONFIG, &config);

    rt_device_open(gps_serial,  RT_DEVICE_FLAG_INT_RX); /* 以 DMA 接收及轮询发送方式打开串口设备 */
    rt_device_set_rx_indicate(gps_serial, gps_uart_input); /* 设置接收回调函数 */

    rt_thread_t gps_thread = rt_thread_create("nmea", nmea_thread_entry, RT_NULL, 4096, 25, 10); /* 创建 gps_serial 线程 */

    /* 创建成功则启动线程 */
    if (gps_thread != RT_NULL)
    {
        rt_thread_startup(gps_thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}
MSH_CMD_EXPORT(gps_thread_start,gps_thread_start);
