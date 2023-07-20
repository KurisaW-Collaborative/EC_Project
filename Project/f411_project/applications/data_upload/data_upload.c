/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     Yifang       the first version
 */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <onenet.h>

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "upload_info"
#include <rtdbg.h>

#include "data_upload.h"

rt_thread_t onenet_thread;
//rt_thread_t weather_thread;

static int cmd_flag = 0;

enum weather_index
{
    TEMP_INDEX,
    HUMI_INDEX,
    LUX_INDEX,
    BMP_INDEX
};

struct WEATHER_STRUCT
{
    enum weather_index index;
    const char *data_stream_name;
    float val;
};

struct WEATHER_STRUCT weather_upload_struct[] =
{
    {TEMP_INDEX, "temperature", 0},
    {HUMI_INDEX, "humidity", 0},
    {LUX_INDEX, "lux", 0},
    {BMP_INDEX, "bmp", 0}
};

/*********************** 云端接收回调函数 **********************/

void onenet_cmd_rsp_cb(uint8_t *recv_data, size_t recv_size,uint8_t **resp_data,size_t *resp_size)
{
  /* 申请内存 */
    if(recv_size > 126) return;
    char data[128];
    rt_memcpy(data, recv_data, recv_size);
    data[recv_size] = '\0';

  /* 解析命令 */
    rt_kprintf("data:%s\nrecv size:%d\n:",data,recv_size);//打印接收到的命令

    if(!rt_strcmp(ACQUISITION_START,data))//如果命令为开启气象采集命令
    {
        rt_kprintf("The local system has received the command to start collecting meteorological data from the cloud, and will soon initiate the task.\n");
        //开启气象数据采集任务

        cmd_flag = 1;
    }
    else if(!rt_strcmp(ACQUISITION_END, data))//如果为关闭气象采集命令
    {
        rt_kprintf("The local system has received the command to stop collecting meteorological data from the cloud, and will soon delete the task.\n");
        //关闭气象采集命令
        cmd_flag = 0;
    }
}

void mqtt_recv_data_start()
{
    onenet_set_cmd_rsp_cb(onenet_cmd_rsp_cb);//设置接收回调函数
}

MSH_CMD_EXPORT(mqtt_recv_data_start,mqtt_recv_data_start);
void mqtt_recv_data_stop()
{
    onenet_set_cmd_rsp_cb(NULL);//设置接收回调函数
}
MSH_CMD_EXPORT(mqtt_recv_data_stop,mqtt_recv_data_stop);

/*********************************************/

/* upload random value to temperature */
static void onenet_upload_entry(void *parameter)
{
    while (1)
    {
        if(cmd_flag == 1)
        {
            LOG_I("----------------- Meteorological data collection task started -------------------");
            // 获取温度、湿度数值
//            struct AHT10_DATA aht10_upload_struct = AHT10_read();
//            weather_upload_struct[TEMP_INDEX].val = aht10_upload_struct.temperature;
//            weather_upload_struct[HUMI_INDEX].val = aht10_upload_struct.humidity;

            weather_upload_struct[TEMP_INDEX].val = aht10_temp_take();
            weather_upload_struct[HUMI_INDEX].val = aht10_humi_take();

            // 获取气压数值
            weather_upload_struct[BMP_INDEX].val = bmp280_read();

            // 获取光照信息数值
            weather_upload_struct[LUX_INDEX].val = bh1750_read();

            // 上传气象数据
            for (int i = 0; i < sizeof(weather_upload_struct) / sizeof(weather_upload_struct[0]); i++)
            {
                if (onenet_mqtt_upload_digit(weather_upload_struct[i].data_stream_name, weather_upload_struct[i].val) < 0)
                {
                    LOG_E("upload has an error, stop uploading");
                }
                else
                {
                    LOG_I("buffer : {\"%s\":%f}", weather_upload_struct[i].data_stream_name, weather_upload_struct[i].val);
                }
                rt_kprintf("\n");

                rt_thread_delay(rt_tick_from_millisecond(5 * 1000));
            }

            LOG_I("-------------- The meteorological data collection task is terminated ------------");

            rt_thread_mdelay(20000);
        }
        rt_kprintf("cmd_flag:%d\n",cmd_flag);

        if (onenet_mqtt_upload_string("gps", gps_upload_data) < 0)
        {
            LOG_E("upload has an error, stop uploading");
        }
        else
        {
            LOG_I("buffer : {\"gps\":%f}", gps_upload_data);
        }

        rt_thread_delay(rt_tick_from_millisecond(5 * 1000));
    }
}

void weather_task_suspend(void)
{
    rt_err_t result = -RT_ERROR;
    result = rt_thread_suspend(weather_thread);
    if(result != RT_EOK)
    {
        rt_kprintf("weather thread suspend failed!\n");
    }
    rt_kprintf("weather task has been suspended!\n");
}

void weather_task_startup(void)
{
    rt_err_t result = -RT_EOK;
    result = rt_thread_startup(weather_thread);
    if(result != RT_EOK)
    {
        rt_kprintf("rt_thread_startup weather_thread failed!\n");
    }
}

void onenet_upload_thread_start(void)
{
    weather_thread = rt_thread_create("weather_upload_th", weather_task_entry, RT_NULL, 2048, 22, 500);

    if (weather_thread == RT_NULL)
    {
        rt_kprintf("weather_thread create failed!\n");
    }
    rt_kprintf("weather task has been created!\n");

    onenet_thread = rt_thread_create("onenet_upload_th", onenet_upload_entry, RT_NULL, 2048, 23, 500);
    if (onenet_thread != RT_NULL)
    {
        rt_thread_startup(onenet_thread);
    }
    rt_kprintf("onenet upload task has been created!\n");
}
MSH_CMD_EXPORT(onenet_upload_thread_start, onenet_upload_thread_start);
