/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-09     Yifang       the first version
 */
#ifndef APPLICATIONS_VOICE_CTRL_H_
#define APPLICATIONS_VOICE_CTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

// ���ڷ�����Ϣ��󳤶�
#define UART_SEND_MAX      32
#define UART_MSG_HEAD_LEN  2
#define UART_MSG_FOOT_LEN  2

// ���ڷ�����Ϣ��
#define U_MSG_AB      2
#define U_MSG_AC      3
#define U_MSG_AD      4
#define U_MSG_AF      5
#define U_MSG_AE      6
#define U_MSG_AI      7
#define U_MSG_AJ      8

// ������Ϣ��������
typedef union
{
    double d_double;
    int d_int;
    unsigned char d_ucs[8];
    char d_char;
    unsigned char d_uchar;
    unsigned long d_long;
    short d_short;
    float d_float;
}uart_param_t;

enum voice_use_number
{
    posture,        // 0.������̬�쳣��ʾ
    fire_level1,    // 1.�� Level1
    fire_level2,    // 2.�� Level2
    weather_fin,    // 3.�������ݵ�����ɣ�������ʾ�ɹ�
    monitor_fin,    // 4.�����쳣������ݵ�����ɣ�������ʾ�ɹ�
    low_battery     // 5.��������ʾ
};

struct VOICE_TASK_FLAG
{
    int flag_index;
    char *flag_name;
    rt_bool_t flag_val;
};

// ȫ���¼����������û�����
extern rt_event_t voice_event;

// ���������¼���
#define EVENT_POSTURE       (1 << 0)
#define EVENT_FIRE_L1       (1 << 1)
#define EVENT_FIRE_L2       (1 << 2)
#define EVENT_WEATHER       (1 << 3)
#define EVENT_MONITOR       (1 << 4)
#define EVENT_LOWBATTERY    (1 << 5)

void _uart_send_impl(int index);

// action: AB
void _uart_AB(unsigned char A2);

// action: AC
void _uart_AC(unsigned char A3);

// action: AD
void _uart_AD(unsigned char A4);

// action: AF
void _uart_AF(unsigned char A5);

// action: AE
void _uart_AE(unsigned char A6);

// action: AI
void _uart_AI(unsigned char A7);

// action: AJ
void _uart_AJ(unsigned char A8);

void voice_task_thread(void);


#ifdef __cplusplus
}
#endif

#endif /* APPLICATIONS_VOICE_CTRL_H_ */
