/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-20     Yifang       the first version
 */
#include "encoder_read.h"
#include <stdio.h>
#include <stm32g474xx.h>
#include <board.h>
#include <rtthread.h>

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "encoder_read"
#include <rtdbg.h>

struct pulse_dev car_pulse_dev[4] = {
    { ("pulse2"), 1 },
    { ("pulse3"), 2 },
    { ("pulse4"), 3 },
    { ("pulse5"), 4 }
};

struct pulse_dev_handle pulse_dev_handle_list[4];

#ifdef BSP_USING_PULSE_ENCODER
int pulse_encoder_dev_read(void *parameter)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t index;
    rt_int32_t count;
    int i = 0;

    /* 脉冲设备初始化 */
    rt_kprintf("\n");
    for (i = 0; i < 4; i++)
    {
        pulse_dev_handle_list[i].pulse_dev_handle_name = RT_NULL;
        LOG_I("car_pulse_dev[%d].pulse_dev_name = %s", i, car_pulse_dev[i].pulse_dev_name);
        LOG_I("pulse_dev_handle_list[%d].pulse_dev_handle_name = %u", i, pulse_dev_handle_list[i].pulse_dev_handle_name);
    }

    /* 查找脉冲编码器设备并传回设备句柄 */
    for (i = 0; i < 4; i++)
    {
        pulse_dev_handle_list[i].index = i;
        pulse_dev_handle_list[i].pulse_dev_handle_name = (rt_device_t)rt_device_find(car_pulse_dev[i].pulse_dev_name);
        if (pulse_dev_handle_list[i].pulse_dev_handle_name == RT_NULL)
        {
            LOG_E("find %s device handle failed!", pulse_dev_handle_list[i].pulse_dev_handle_name);
            LOG_E("%s",pulse_dev_handle_list[i].pulse_dev_handle_name);
            return ret;
        }
        else
        {
            LOG_I("find %s device handle succeed!", pulse_dev_handle_list[i].pulse_dev_handle_name);
            LOG_I("%s",pulse_dev_handle_list[i].pulse_dev_handle_name);
        }
    }
    rt_kprintf("\n");

    /* RT_ASSERT pulse encoder dev */
    for (i = 0; i < 4; i++)
    {
        RT_ASSERT(car_pulse_dev[i].pulse_dev_name != RT_NULL);
    }

    /* 以只读方式打开设备 */
    for (i = 0; i < 4; i++)
    {
        ret = rt_device_open(pulse_dev_handle_list[i].pulse_dev_handle_name, RT_DEVICE_OFLAG_RDONLY);
        if (ret != RT_EOK)
        {
            LOG_I("open %s device handle failed!", pulse_dev_handle_list[i].pulse_dev_handle_name);
            return ret;
        }
        else
        {
            LOG_I("open %s device handle succeed!", pulse_dev_handle_list[i].pulse_dev_handle_name);
        }
    }
    rt_kprintf("\n");

//    for (index = 0; index <= 100; index++)
    while(1)
    {
        rt_thread_mdelay(500);
        /* 读取脉冲编码器计数值 */
        ret = RT_EOK;

#ifndef USER_ENCODER_AVERAGE
        for (i = 0; i < 4; i++)
        {
            ret = rt_device_read(pulse_dev_handle_list[i].pulse_dev_handle_name, 0, &count, 1);
            if (ret == RT_NULL)
            {
                LOG_I("read %s device handle failed!", pulse_dev_handle_list[i].pulse_dev_handle_name);
                return ret;
            }
            else
            {
                LOG_I("Get %s: count %u", pulse_dev_handle_list[i].pulse_dev_handle_name, count);
            }
        }
#else
        for (i = 0; i < 4; i++)
        {
            ret = rt_device_read(pulse_dev_handle_list[i].pulse_dev_handle_name, 0, &count, 1);
            if (ret == RT_NULL)
            {
                LOG_E("read %s device handle failed!", pulse_dev_handle_list[i].pulse_dev_handle_name);
                return ret;
            }
            count += count;
        }
        LOG_I("The average pulse value is %d", count / 4);
#endif

        /* 清空脉冲编码器计数值 */
        for (i = 0; i < 4; i++)
        {
            rt_device_control(pulse_dev_handle_list[i].pulse_dev_handle_name, PULSE_ENCODER_CMD_CLEAR_COUNT, RT_NULL);
        }
    }

    /* 关闭编码器设备 */
    for (i = 0; i < 4; i++)
    {
        ret = rt_device_close(pulse_dev_handle_list[i].pulse_dev_handle_name);
        if (ret != RT_EOK)
        {
            LOG_E("close %s device handle failed!", pulse_dev_handle_list[i].pulse_dev_handle_name);
            return ret;
        }
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pulse_encoder_dev_read, pulse encoder read);
#endif





Encoder OriginalEncoder; //Encoder raw data //编码器原始数据

int Read_Encoder(uint8_t TIMX)
{
    int Encoder_TIM;
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);

     switch(TIMX)
     {
         case 2:
         {
             Encoder_TIM= (short)(__HAL_TIM_GET_COUNTER(&htim2));
             LOG_I("Current [%d].MOTOR_LF.Encoder: %d", TIMX, Encoder_TIM);

             __HAL_TIM_SET_COUNTER(&htim2, 0);
             break;
         }
         case 3:
         {
             Encoder_TIM= (short)(__HAL_TIM_GET_COUNTER(&htim3));
             LOG_I("Current [%d].MOTOR_LF.Encoder: %d", TIMX, Encoder_TIM);

             __HAL_TIM_SET_COUNTER(&htim3, 0);
             break;
         }
         case 4:
         {
             Encoder_TIM= (short)(__HAL_TIM_GET_COUNTER(&htim4));
             LOG_I("Current [%d].MOTOR_LF.Encoder: %d", TIMX, Encoder_TIM);

             __HAL_TIM_SET_COUNTER(&htim4, 0);
             break;
         }
         case 5:
         {
             Encoder_TIM= (short)(__HAL_TIM_GET_COUNTER(&htim5));
             LOG_I("Current [%d].MOTOR_LF.Encoder: %d", TIMX, Encoder_TIM);

             __HAL_TIM_SET_COUNTER(&htim5, 0);
             break;
         }
         default:
             Encoder_TIM = 0;
     }

     return Encoder_TIM;
}
//MSH_CMD_EXPORT(Read_Encoder,Read_Encoder);


float Get_Vercel_Encoder(char target)
{
    float Encoder_A_pr, Encoder_B_pr, Encoder_C_pr, Encoder_D_pr;

    float rpm = 0.0;

    OriginalEncoder.A = Read_Encoder(2);
    OriginalEncoder.B = Read_Encoder(3);
    OriginalEncoder.C = Read_Encoder(4);
    OriginalEncoder.D = Read_Encoder(5);

    Encoder_A_pr = OriginalEncoder.A;
    Encoder_B_pr = OriginalEncoder.B;
    Encoder_C_pr = OriginalEncoder.C;
    Encoder_D_pr = OriginalEncoder.D;

    //编码器原始数据转换为车轮速度，单位m/s
    switch(target)
    {
        case 'A':
        {
            MOTOR_A.Encoder = Encoder_A_pr * CONTROL_FREQUENCY * Wheel_perimeter / Encoder_precision;
            LOG_I("MOTOR_A speed: %f m/s", MOTOR_A.Encoder);
            rpm = MOTOR_A.Encoder;
            return rpm;
        }
        case 'B':
        {
            MOTOR_B.Encoder = Encoder_B_pr * CONTROL_FREQUENCY * Wheel_perimeter / Encoder_precision;
            LOG_I("MOTOR_B speed: %f m/s", MOTOR_B.Encoder);
            rpm = MOTOR_B.Encoder;
            return rpm;
        }
        case 'C':
        {
            MOTOR_C.Encoder = Encoder_C_pr * CONTROL_FREQUENCY * Wheel_perimeter / Encoder_precision;
            LOG_I("MOTOR_C speed: %f m/s", MOTOR_C.Encoder);
            rpm = MOTOR_C.Encoder;
            return rpm;
        }
        case 'D':
        {
            MOTOR_D.Encoder = Encoder_D_pr * CONTROL_FREQUENCY * Wheel_perimeter / Encoder_precision;
            LOG_I("MOTOR_D speed: %f m/s", MOTOR_D.Encoder);
            rpm = MOTOR_D.Encoder;
            return rpm;
        }
    }
}

uint32_t ReverseResolveEncoderValue(float velocity)
{
    // 计算脉冲值
    uint32_t encoder_pulse = (uint16_t)(velocity * Encoder_precision * CONTROL_FREQUENCY / Wheel_perimeter);

    return encoder_pulse;
}

void encoder_read_thread_entry(void *parameter)
{
    rt_kprintf("\n");
    LOG_I("-------------- Starting read the encoder value: -----------");
    for(int i = 0; i < 10000; i++)
    {
        rt_kprintf("\n");
        LOG_I("[%d].MOTOR_A speed: %f m/s", i, MOTOR_A.Encoder);
        LOG_I("[%d].MOTOR_B speed: %f m/s", i, MOTOR_B.Encoder);
        LOG_I("[%d].MOTOR_C speed: %f m/s", i, MOTOR_C.Encoder);
        LOG_I("[%d].MOTOR_D speed: %f m/s", i, MOTOR_D.Encoder);
        rt_kprintf("\n");
        rt_thread_mdelay(1000);
    }
    LOG_I("------------ Reading the encoder value finished! ----------");
    rt_kprintf("\n");
}

rt_err_t encoder_read_thread(void)
{
    rt_thread_t ret = rt_thread_create("encoder_read_thread", encoder_read_thread_entry, RT_NULL, 2048, 19, 100);
    if(ret == RT_NULL)
    {
        LOG_E("encoder_read_thread create failed!\n");
    }
    rt_thread_startup(ret);

    return RT_EOK;
}
MSH_CMD_EXPORT(encoder_read_thread, encoder read thread);


void Set_Motor_Speed(uint8_t motor_num, double speed_percentage)
{
    // 设置范围为（0 ~ 100）
    if (speed_percentage < 0.0)
    {
        speed_percentage = 0.0;
    }
    else if (speed_percentage > 100.0)
    {
        speed_percentage = 100.0;
    }

    uint32_t pwm_duty = (uint32_t)(speed_percentage);

    switch (motor_num)
    {
    case 2:
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_ALL, pwm_duty);
        break;
    case 3:
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_ALL, pwm_duty);
        break;
    case 4:
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_ALL, pwm_duty);
        break;
    case 5:
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_ALL, pwm_duty);
        break;
    default:
        return;
    }
}


/*
 * @function：获取编码器脉冲值
 * @return：正确获取返回脉冲值，否则返回 -RT_ERROR
 * */
int encoder_value_take(uint8_t TIMx)
{
    int CaptureNumber = RT_NULL;
    switch(TIMx)
    {
    case 2:
        CaptureNumber = __HAL_TIM_GET_COUNTER(&htim2);
        __HAL_TIM_SET_COUNTER(&htim2,0);
        break;
    case 3:
        CaptureNumber = __HAL_TIM_GET_COUNTER(&htim3);
        __HAL_TIM_SET_COUNTER(&htim3,0);
        break;
    case 4:
        CaptureNumber = __HAL_TIM_GET_COUNTER(&htim4);
        __HAL_TIM_SET_COUNTER(&htim4,0);
        break;
    case 5:
        CaptureNumber = __HAL_TIM_GET_COUNTER(&htim5);
        __HAL_TIM_SET_COUNTER(&htim5,0);
        break;
    default:
        LOG_E("The timer handle is not defined, return exception!");
        return -RT_ERROR;
    }

    return CaptureNumber;
}


/*
 * @function：获取编码器方向：0->正方向         1->负方向
 * @return：正确获编码器方向，否则返回 RT_ERROR
 * */
rt_bool_t encoder_state_take(uint8_t TIMx)
{
    rt_bool_t State = RT_NULL;
    switch(TIMx)
    {
    case 2:
        State = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);
        break;
    case 3:
        State = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);
        break;
    case 4:
        State = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4);
        break;
    case 5:
        State = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5);
        break;
    default:
        LOG_E("The timer handle is not defined, return exception!");
        return -RT_ERROR;
    }

    return State;
}


/*
 * @function：开启编码器计数
 * @return：正确返回RT_EOK，否则返回 -RT_ERROR
 * */
rt_err_t encoder_start(uint8_t TIMx)
{
    switch(TIMx)
    {
    case 2:
        HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
        break;
    case 3:
        HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
        break;
    case 4:
        HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
        break;
    case 5:
        HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
        break;
    default:
        LOG_E("The timer handle is not defined, return exception!");
        return -RT_ERROR;
    }
    return RT_EOK;
}


/*
 * @function：关闭编码器计数
 * @return：正确返回RT_EOK，否则返回 -RT_ERROR
 * */
rt_err_t encoder_end(uint8_t TIMx)
{
    switch(TIMx)
    {
    case 2:
        HAL_TIM_Encoder_Stop(&htim2, TIM_CHANNEL_ALL);
        break;
    case 3:
        HAL_TIM_Encoder_Stop(&htim3, TIM_CHANNEL_ALL);
        break;
    case 4:
        HAL_TIM_Encoder_Stop(&htim4, TIM_CHANNEL_ALL);
        break;
    case 5:
        HAL_TIM_Encoder_Stop(&htim5, TIM_CHANNEL_ALL);
        break;
    default:
        LOG_E("The timer handle is not defined, return exception!");
        return -RT_ERROR;
    }
    return RT_EOK;
}
