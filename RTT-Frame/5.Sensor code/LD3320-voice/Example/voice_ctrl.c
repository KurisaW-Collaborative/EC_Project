/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-09     Yifang       the first version
 */
#include <rtthread.h>
#include "voice_ctrl.h"
#include "uart_trans_msg.h"

extern rt_device_t uart1_serial;

// 串口通信消息头
const unsigned char g_uart_send_head[] = { 0xaa, 0x55 };

// 串口通信消息尾
const unsigned char g_uart_send_foot[] = { 0x55, 0xaa };

enum voice_use_number
{
    posture,        // 0.车身姿态异常提示
    fire_level1,    // 1.火警 Level1
    fire_level2,    // 2.火警 Level2
    weather_fin,    // 3.气象数据调出完成，语音提示成功
    monitor_fin,    // 4.城市异常监测数据调出完成，语音提示成功
    low_battery     // 5.电量低提示
};

struct voice_number
{
    enum voice_use_number index;
    const unsigned char data_frame[6];
};

struct voice_number voice_data_number[6] =
{
    {.index = posture, .data_frame = {0xAA, 0x55, 0x02, 0x02, 0x55, 0xAA}},        // 车身姿态异常提示
    {.index = fire_level1, .data_frame = {0xAA, 0x55, 0x03, 0x03, 0x55, 0xAA}},    // 火警 Level1
    {.index = fire_level2, .data_frame = {0xAA, 0x55, 0x04, 0x04, 0x55, 0xAA}},    // 火警 Level2
    {.index = weather_fin, .data_frame = {0xAA, 0x55, 0x05, 0x05, 0x55, 0xAA}},    // 气象数据调出完成，语音提示成功
    {.index = monitor_fin, .data_frame = {0xAA, 0x55, 0x06, 0x06, 0x55, 0xAA}},    // 城市异常监测数据调出完成，语音提示成功
    {.index = low_battery, .data_frame = {0xAA, 0x55, 0x07, 0x07, 0x55, 0xAA}}     // 电量低提示
};

void _uart_send_impl(int index)
{
    unsigned char *data_frame = RT_NULL;
    int data_frame_size = 0;

    switch (index)
    {
        case posture:
            data_frame = voice_data_number[posture].data_frame;
            data_frame_size = sizeof(voice_data_number[posture].data_frame);
            break;
        case fire_level1:
            data_frame = voice_data_number[fire_level1].data_frame;
            data_frame_size = sizeof(voice_data_number[fire_level1].data_frame);
            break;
        case fire_level2:
            data_frame = voice_data_number[fire_level2].data_frame;
            data_frame_size = sizeof(voice_data_number[fire_level2].data_frame);
            break;
        case weather_fin:
            data_frame = voice_data_number[weather_fin].data_frame;
            data_frame_size = sizeof(voice_data_number[weather_fin].data_frame);
            break;
        case monitor_fin:
            data_frame = voice_data_number[monitor_fin].data_frame;
            data_frame_size = sizeof(voice_data_number[monitor_fin].data_frame);
            break;
        case low_battery:
            data_frame = voice_data_number[low_battery].data_frame;
            data_frame_size = sizeof(voice_data_number[low_battery].data_frame);
            break;
        default:
            rt_kprintf("Invalid voice index\n");
            return;
    }

    for (int i = 0; i < data_frame_size; i++)
    {
        rt_device_write(uart1_serial, 0, &(data_frame[i]), 1);
    }

    rt_memset(data_frame, 0, data_frame_size);

    rt_kprintf("Voice data frame sent successfully\n");
}


/*
 * @function: action: AB
 * @descrition: 车身姿态异常提示
 * @message style: AA 55 02 02 55 AA
 * */
void _uart_AB(unsigned char A2)
{
    uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};

    for (i = 0; i < UART_MSG_HEAD_LEN; i++)
    {
        buff[i + 0] = g_uart_send_head[i];
    }

    buff[2] = U_MSG_AB;
    param.d_uchar = A2;
    buff[3] = param.d_uchar;

    for (i = 0; i < UART_MSG_FOOT_LEN; i++)
    {
        buff[i + 4] = g_uart_send_foot[i];
    }

//    _uart_send_impl(buff, 6);
}
MSH_CMD_EXPORT(_uart_AB,_uart_AB);

/*
 * @function: action: AC
 * @descrition: 火警 Level1
 * @message style: AA 55 03 03 55 AA
 * */
void _uart_AC(unsigned char A3)
{
    uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};

    for (i = 0; i < UART_MSG_HEAD_LEN; i++)
    {
        buff[i + 0] = g_uart_send_head[i];
    }

    buff[2] = U_MSG_AC;
    param.d_uchar = A3;
    buff[3] = param.d_uchar;

    for (i = 0; i < UART_MSG_FOOT_LEN; i++)
    {
        buff[i + 4] = g_uart_send_foot[i];
    }
//    _uart_send_impl(buff, 6);
}
MSH_CMD_EXPORT(_uart_AC,_uart_AC);

/*
 * @function: action: AD
 * @descrition: 火警 Level2
 * @message style: AA 55 04 04 55 AA
 * */
void _uart_AD(unsigned char A4)
{
    uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};

    for (i = 0; i < UART_MSG_HEAD_LEN; i++)
    {
        buff[i + 0] = g_uart_send_head[i];
    }

    buff[2] = U_MSG_AD;
    param.d_uchar = A4;
    buff[3] = param.d_uchar;

    for (i = 0; i < UART_MSG_FOOT_LEN; i++)
    {
        buff[i + 4] = g_uart_send_foot[i];
    }

//    _uart_send_impl(buff, 6);
}
MSH_CMD_EXPORT(_uart_AD,_uart_AD);

/*
 * @function: action: AF
 * @descrition: 气象数据调出完成，语音提示成功
 * @message style: AA 55 05 05 55 AA
 * */
void _uart_AF(unsigned char A5)
{
    uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};

    for (i = 0; i < UART_MSG_HEAD_LEN; i++)
    {
        buff[i + 0] = g_uart_send_head[i];
    }

    buff[2] = U_MSG_AF;
    param.d_uchar = A5;
    buff[3] = param.d_uchar;

    for (i = 0; i < UART_MSG_FOOT_LEN; i++)
    {
        buff[i + 4] = g_uart_send_foot[i];
    }

//    _uart_send_impl(buff, 6);
}
MSH_CMD_EXPORT(_uart_AF,_uart_AF);

/*
 * @function: action: AE
 * @descrition: 城市异常监测数据调出完成，语音提示成功
 * @message style: AA 55 06 06 55 AA
 * */
void _uart_AE(unsigned char A6)
{
    uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};

    for (i = 0; i < UART_MSG_HEAD_LEN; i++)
    {
        buff[i + 0] = g_uart_send_head[i];
    }

    buff[2] = U_MSG_AE;
    param.d_uchar = A6;
    buff[3] = param.d_uchar;

    for (i = 0; i < UART_MSG_FOOT_LEN; i++)
    {
        buff[i + 4] = g_uart_send_foot[i];
    }

//    _uart_send_impl(buff, 6);
}
MSH_CMD_EXPORT(_uart_AE,_uart_AE);

/*
 * @function: action: AI
 * @descrition: 电量低提示
 * @message style: AA 55 07 07 55 AA
 * */
void _uart_AI(unsigned char A7)
{
    uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};

    for (i = 0; i < UART_MSG_HEAD_LEN; i++)
    {
        buff[i + 0] = g_uart_send_head[i];
    }

    buff[2] = U_MSG_AI;
    param.d_uchar = A7;
    buff[3] = param.d_uchar;

    for (i = 0; i < UART_MSG_FOOT_LEN; i++)
    {
        buff[i + 4] = g_uart_send_foot[i];
    }

//    _uart_send_impl(buff, 6);
}
MSH_CMD_EXPORT(_uart_AI,_uart_AI);

/*
 * @function: action: AJ
 * @descrition: 串口测试
 * @message style: AA 55 08 08 55 AA
 * */
void _uart_AJ(unsigned char A8)
{
    uart_param_t param;
    int i = 0;
    unsigned char buff[UART_SEND_MAX] = {0};

    for (i = 0; i < UART_MSG_HEAD_LEN; i++)
    {
        buff[i + 0] = g_uart_send_head[i];
    }

    buff[2] = U_MSG_AJ;
    param.d_uchar = A8;
    buff[3] = param.d_uchar;

    for (i = 0; i < UART_MSG_FOOT_LEN; i++)
    {
        buff[i + 4] = g_uart_send_foot[i];
    }

//    _uart_send_impl(buff, 6);
}
