/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-08     Yifang       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "noise_mtor.h"
#include "filter.h"
#include "voice_command/voice_ctrl.h"

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "noise_info"
#include <rtdbg.h>

static rt_adc_device_t adc_noise_dev;
extern rt_event_t voice_event;

#define ADC_DEV_NOISE_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_NOISE_CHANNEL     (4)           /* ADC 通道 */       //PA4

static rt_thread_t noise_thread = RT_NULL;

void lm386_data_filter(void)
{
    double lm386_rawData[50];
    double cov_rate = 0.0;

    while(1)
    {
        for(int i = 0; i < 50; i++)
        {
            lm386_rawData[i] = lm386_get_data();
        }

        int array_size = sizeof(lm386_rawData) / sizeof(lm386_rawData[0]);

        cov_rate = cov_filter(lm386_rawData, array_size);

        rt_kprintf("$%f;",cov_rate);
//        rt_kprintf("cov_rate: %.2f%%\n", cov_rate);

        memset(lm386_rawData, 0, sizeof(lm386_rawData));
        cov_rate = 0.0;

//        rt_thread_mdelay(1000);
    }
}
//INIT_APP_EXPORT(lm386_data_filter);

double lm386_get_data(void)
{
    rt_uint32_t value;
    double voltage;

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);

    value = HAL_ADC_GetValue(&hadc1);
//    LOG_I("The value is: %d", value);
    voltage = value / 4096.0 * 3.3;
//    LOG_I("The voltage is: %0.2f\n", voltage);

//    rt_kprintf("$%d;", value);

    HAL_ADC_Stop(&hadc1);

    return voltage;
}

void LM386_thread_entry(void)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t ad_value;
    double cov_rate_ref, cov_rate_real;
    double lm386_rawData[100],lm386_newdata[5];

    int vol_index = 0;
    int16_t tick_cout_1, tick_cout_2, mid_tick_cout = 0;

    LOG_I("---------------------- Environmental noise detection --------------------");
    LOG_I("The noise monitoring task has been successfully activated!");
    LOG_I("You can modify the noise recognition rate in the noise mtor.c file.");

//    LOG_I("Start collecting discrete values of quiet environment sound. Keep the surrounding environment quiet!");
//    for(int i = 0; i < 100; i++)
//    {
//        lm386_rawData[i] = lm386_get_data();
//        rt_hw_us_delay(100);
//    }
//
//    int array_size = sizeof(lm386_rawData) / sizeof(lm386_rawData[0]);
//
//    cov_rate_ref = cov_filter(lm386_rawData, array_size);
//
//    LOG_I("discrete values of quiet environment sound is :%0.2ff", cov_rate_ref);

//    memset(lm386_rawData, 0, sizeof(lm386_rawData));

    while(1)
    {
        if(rt_pin_read(LM386_PIN) == PIN_HIGH)
        {
            ++vol_index;

            if(vol_index == 1)
            {
                tick_cout_1 = rt_tick_get();
//                rt_kprintf("[%d]",tick_cout_1);
            }
            else if(vol_index > 400)
            {
                tick_cout_2 = rt_tick_get();
                mid_tick_cout = tick_cout_2 - tick_cout_1;
                // 此处扩大mid_tick_cout值可提高噪声识别精度
                if(mid_tick_cout > 4000)
                {
//                    rt_event_send(voice_event, EVENT_MONITOR);
                    LOG_I("[%d][%d][%d]The ambient noise is too loud!", mid_tick_cout,tick_cout_1 = rt_tick_get(), vol_index);
                    rt_pin_write(LM386_PIN, PIN_LOW);

                    vol_index = 0;
                }
            }
        }
        else
        {
//            rt_thread_mdelay(1000);
//            LOG_I("\n\n\nIt's quiet around here.\n\n\n");
//            rt_pin_write(LM386_PIN, PIN_HIGH);
        }


//        for(int i = 0; i < 5; i++)
//        {
//            lm386_newdata[i] = lm386_get_data();
//            rt_hw_us_delay(100);
//        }
//
//        cov_rate_real = cov_filter(lm386_newdata, array_size);
//
//        for(int j = 0; j < 10; j++)
//        {
//            cov_rate_real += cov_rate_real;
//        }
//
//        cov_rate_real = cov_rate_real / 10;
//
//        if((cov_rate_real > (cov_rate_ref * 1.15)) || cov_rate_real < (cov_rate_ref * 0.85))
//        {
//            LOG_I("cov_rate_real : %.2ff",cov_rate_real);
//            LOG_I("The discrete value of ambient sound is too large, which has exceeded the noise index!");
//        }
//        else
//        {
//            LOG_I("cov_rate_real : %.2ff",cov_rate_real);
//        }
//        rt_kprintf("$%f %f;", cov_rate_ref, cov_rate_real);
//        rt_thread_mdelay(500);
    }
}

void LM386_thread_delete(void)
{
    rt_thread_delete(noise_thread);
}
//MSH_CMD_EXPORT(LM386_thread_delete,LM386_thread_delete);

void LM386_thread_start(void)
{
    rt_pin_mode(LM386_PIN, PIN_MODE_INPUT);
    rt_pin_mode(LM386_ADC_PIN, PIN_MODE_INPUT);

    noise_thread = rt_thread_create("noise_thread", LM386_thread_entry, RT_NULL, 4096, 22, 1000);

    /* 如果获得线程控制块，启动这个线程 */
    if (noise_thread != RT_NULL)
        rt_thread_startup(noise_thread);
}
MSH_CMD_EXPORT(LM386_thread_start,LM386_thread_start);
//INIT_APP_EXPORT(LM386_thread_start);
