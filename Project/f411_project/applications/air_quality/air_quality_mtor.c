/*
 * Copyright (c) 2006-2021, RT-Thread DevelodustDensityent Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-08     Yifang       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "air_quality_mtor.h"
#include "rtdef.h"
#include "stdint.h"
#include "voice_command/voice_ctrl.h"

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "pm_info"
#include <rtdbg.h>

#define ADC_DEV_PM_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_PM_CHANNEL     (10)           /* ADC 通道 */       //PB0

static rt_adc_device_t adc_pm_dev;
extern rt_event_t voice_event;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

float GP2Y_Value_read(void)
{
    rt_err_t ret;
    int i = 0;

    for(i; i < 5; i++)
    {
        /* 使能设备 */
        ret = rt_adc_enable(adc_pm_dev, ADC_DEV_PM_CHANNEL);

        GP2Y_Low;
        rt_thread_mdelay(28);
        voMeasured += rt_adc_read(adc_pm_dev,ADC_DEV_PM_CHANNEL); //PA0
        rt_thread_mdelay(4);
        GP2Y_High;

        ret = rt_adc_disable(adc_pm_dev, ADC_DEV_PM_CHANNEL);
    }

    voMeasured = voMeasured / 5;
    calcVoltage = ((voMeasured / 255.0) * 5 * 0.17 - 0.1) * 1000;
    voMeasured = 0.0;

    if(calcVoltage < 0)
    {
        calcVoltage = 0.0;
    }

    return calcVoltage;
}

void air_qua_level(float val)
{
    if (val < 35)
    {
//        LOG_I("The test result is: AQIL: [Level 1], AQII: [Excellent]");
    }
    else if (val > 35 && val < 75)
    {
//        LOG_I("The test result is: AQIL: [Level 2], AQII: [Good]");
    }
    else if (val > 75 && val < 115)
    {
//        LOG_I("The test result is: AQIL: [Level 3], AQII: [Light pollution]");
    }
    else if (val > 115 && val < 150)
    {
        LOG_I("The test result is: AQIL: [Level 4], AQII: [Moderate pollution]");
    }
    else if (val > 150 && val < 250)
    {
        LOG_I("The test result is: AQIL: [Level 5], AQII: [Heavy pollution]");
    }
    else
    {
//        rt_event_send(voice_event, 1 << monitor_fin);
        LOG_I("The test result is: AQIL: [Level 6], AQII: [Serious pollution]");
    }
}


void GP2Y_thread_entry(void)
{
    LOG_I("\n----------------------- Air quality classification ------------------------");
    LOG_I("Air Quality Rating: [Level 1]--->Air Quality Index: [Excellent]");
    LOG_I("Air Quality Rating: [Level 2]--->Air Quality Index: [Good]");
    LOG_I("Air Quality Rating: [Level 3]--->Air Quality Index: [Light pollution]");
    LOG_I("Air Quality Rating: [Level 4]--->Air Quality Index: [Moderate pollution]");
    LOG_I("Air Quality Rating: [Level 5]--->Air Quality Index: [Heavy pollution]");
    LOG_I("Air Quality Rating: [Level 6]--->Air Quality Index: [Serious pollution]");
    LOG_I("The air quality monitoring task has been successfully activated!");

    while(1)
    {
        float val = GP2Y_Value_read();
//        rt_kprintf("Reading GP2Y Value is %f ug/m3\n",val);
        rt_thread_mdelay(5000);

        air_qua_level(val);
    }
}

void GP2Y_thread_start(void)
{
    rt_thread_t tid = RT_NULL;

    /* 查找设备 */
    adc_pm_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_PM_NAME);
    if (adc_pm_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_PM_NAME);
        return RT_ERROR;
    }

    rt_pin_mode(GP2Y_PIN, PIN_MODE_OUTPUT);

    tid = rt_thread_create("pm_thread", GP2Y_thread_entry, RT_NULL, 1024, 21, 500);

    /* 如果获得线程控制块，启动这个线程 */
    if (tid != RT_NULL)
        rt_thread_startup(tid);
}
MSH_CMD_EXPORT(GP2Y_thread_start,GP2Y_thread_start);
