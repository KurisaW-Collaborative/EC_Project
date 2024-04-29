/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-04     Yifang       the first version
 */
#include "car_stabilize.h"
#include "./pid_lib/pid.h"
#include "encoder_read.h"

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "car_stab"
#include <rtdbg.h>

PID_TypeDef TPID1;
PID_TypeDef TPID2;
PID_TypeDef TPID3;
PID_TypeDef TPID4;

static double kp = 0.5;
static double ki = 0.1;
static double kd = 0.0;

struct PID_PARAM_ENCODER
{
    double speed;
    double PIDOut;
    PID_TypeDef TPID;
};

struct PID_PARAM_ENCODER pid_param_encoder[4];

void pid_thread_entry(void)
{
    double pluse_set_point,out_set_pluse;

    pluse_set_point = 0.0001;
    out_set_pluse = 2000;

    pid_param_encoder[0].TPID = TPID1;
    pid_param_encoder[1].TPID = TPID2;
    pid_param_encoder[2].TPID = TPID3;
    pid_param_encoder[3].TPID = TPID4;

    for(int i = 0; i < 4; i++)
    {
        PID(&pid_param_encoder[i].TPID,
            &pid_param_encoder[i].speed,
            &pid_param_encoder[i].PIDOut,
            &pluse_set_point,
            kp,
            ki,
            kd,
            _PID_P_ON_E,
            _PID_CD_DIRECT);

        PID_SetMode(&pid_param_encoder[i].TPID, _PID_MODE_AUTOMATIC);
        PID_SetSampleTime(&pid_param_encoder[i].TPID, 500);
        PID_SetOutputLimits(&pid_param_encoder[i].TPID, 1, 100);
    }

    while(1)
    {
        pid_param_encoder[0].speed = Get_Vercel_Encoder('A');
        pid_param_encoder[1].speed = Get_Vercel_Encoder('B');
        pid_param_encoder[2].speed = Get_Vercel_Encoder('C');
        pid_param_encoder[3].speed = Get_Vercel_Encoder('D');

        for(int i = 0; i < 4; i++)
        {
            PID_Compute(&pid_param_encoder[i].TPID);
            rt_kprintf(">[PIDOut%d]: %lf ", i, pid_param_encoder[i].PIDOut);

//            Set_Motor_Speed(i+2,out_set_pluse);
            rt_thread_mdelay(10);
        }
        rt_thread_mdelay(1000);

        rt_kprintf("\n");
    }
}

void pid_task(void)
{
    rt_thread_t pid_th_handle = rt_thread_create("pid_thread", pid_thread_entry, RT_NULL, 2048, 19, 100);
    if(pid_th_handle == RT_NULL)
    {
        LOG_E("encoder_read_thread create failed!\n");
    }
    rt_thread_startup(pid_th_handle);

    return RT_EOK;
}
MSH_CMD_EXPORT(pid_task,pid_task);

int range_compare(float value, float min_range, float max_range)
{
    return (value >= min_range && value <= max_range);
}

void car_posture_detect(int _yaw, int _pitch, int _roll)
{
    const float yaw_min = -60.0;
    const float yaw_max = 60.0;
    const float pitch_min = -10.0;
    const float pitch_max = 10.0;
    const float roll_min = -10.0;
    const float roll_max = 10.0;

    if (!range_compare(_yaw, yaw_min, yaw_max) && !range_compare(_pitch, pitch_min, pitch_max) && !range_compare(_roll, roll_min, roll_max))
    {
        // 向F4_TCP服务器发送姿态异常的通知
        rt_kprintf("posture error!\n");

        return 1;
    }

    return 0;
}
