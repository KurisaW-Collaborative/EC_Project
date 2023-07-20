/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-05     Yifang       the first version
 */
#include "stm32g4xx.h"
#include "encoder_read.h"

#define PULSES_PER_REVOLUTION  1560  // ���������ÿת��������
#define SAMPLE_TIME_MS         1000   // ����ʱ���������룩

uint32_t pulse_count = 0;  // ����������������
float speed_rps = 0.0f;    // ���ת�٣�תÿ�룩

uint32_t last_encoder_value = 0; // ��һ�εı���������ֵ

extern TIM_HandleTypeDef htim2;


#include <rtthread.h>
#include <rtdevice.h>

#define HWTIMER_DEV_NAME   "timer15"     /* ��ʱ������ */

/* ��ʱ����ʱ�ص����� */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    uint16_t current_encoder_value = (short)(__HAL_TIM_GET_COUNTER(&htim2));
    __HAL_TIM_SET_COUNTER(&htim2,0);


    uint16_t pulse_delta = current_encoder_value - last_encoder_value;
    rt_kprintf("pulse_delta1 is %d\n",pulse_delta);
    speed_rps = pulse_delta / PULSES_PER_REVOLUTION / ((float)SAMPLE_TIME_MS / 1000.0f);
    rt_kprintf("\n\nspeed_rps: %f\n\n",speed_rps);


    int16_t pulse_direction = (current_encoder_value > last_encoder_value) ? 1 : -1;

    // ������õ����������ӵ���������
    pulse_count += pulse_direction * pulse_delta;

    // ������һ�εı���������ֵΪ��ǰ����ֵ
    last_encoder_value = current_encoder_value;

    return 0;
}

void timer_th_entry(void)
{
    while(1)
    {
//        uint32_t current_encoder_value = encoder_value_take(2);
//        uint32_t pulse_delta = current_encoder_value - last_encoder_value;
//
//        if (pulse_delta > UINT16_MAX / 2)
//        {
//          // �������������������UINT32_MAX
//          pulse_delta += UINT16_MAX;
//        }
//
//        // ��������ֵ�ж��������ķ���
//        int32_t pulse_direction = (current_encoder_value > last_encoder_value) ? 1 : -1;
//
//        // ������õ����������ӵ���������
//        pulse_count += pulse_direction * pulse_delta;
//
//        // ������һ�εı���������ֵΪ��ǰ����ֵ
//        last_encoder_value = current_encoder_value;

    }
}

static int hwtimer_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;      /* ��ʱ����ʱֵ */
    rt_device_t hw_dev = RT_NULL;   /* ��ʱ���豸��� */
    rt_hwtimer_mode_t mode;         /* ��ʱ��ģʽ */
    rt_uint32_t freq = 10000;               /* ����Ƶ�� */

    /* ���Ҷ�ʱ���豸 */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return RT_ERROR;
    }

    /* �Զ�д��ʽ���豸 */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    /* ���ó�ʱ�ص����� */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* ���ü���Ƶ��(��δ���ø��Ĭ��Ϊ1Mhz �� ֧�ֵ���С����Ƶ��) */
    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);
    /* ����ģʽΪ�����Զ�ʱ������δ���ã�Ĭ����HWTIMER_MODE_ONESHOT��*/
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* ���ö�ʱ����ʱֵΪ1s��������ʱ�� */
    timeout_s.sec = 1;      /* �� */
    timeout_s.usec = 0;     /* ΢�� */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    /* ��ʱ2000ms */
    rt_thread_mdelay(2000);

    /* ��ȡ��ʱ����ǰֵ */
    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    rt_thread_t timer_th = rt_thread_create("timer_th", timer_th_entry, RT_NULL, 2048, 19, 100);
    if(timer_th == RT_NULL)
    {
        rt_kprintf("encoder_read_thread create failed!\n");
    }
    HAL_TIM_Base_Start_IT(&htim15);
    encoder_start(2);

    rt_thread_startup(timer_th);



    return ret;
}
/* ������ msh �����б��� */
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);
