 /*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-21     Yifang       the first version
 */
#include "car_control.h"
#include <board.h>

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "car_ctrl"
#include <rtdbg.h>

struct motor_channel_pin motor_channel_pin_handle[8] = {
        {.pin_handle = GET_PIN(C, 4),     .index = 1},      // FAN1，左前轮
        {.pin_handle = GET_PIN(C, 5),     .index = 2},      // FAN2
        {.pin_handle = GET_PIN(B, 10),    .index = 3},      // FBN1，右前轮
        {.pin_handle = GET_PIN(B, 5),     .index = 4},      // FBN2

        {.pin_handle = GET_PIN(C, 1),     .index = 5},      // BAN1，左后轮
        {.pin_handle = GET_PIN(C, 0),     .index = 6},      // BAN2
        {.pin_handle = GET_PIN(B, 0),     .index = 7},      // BBN1，右后轮
        {.pin_handle = GET_PIN(A, 4),     .index = 8},      // BBN2
};

void car_pwm_channel_init(void)
{
    int i;
    // 默认引脚为输出模式
    rt_kprintf("\n");
    LOG_I("----------------- Initializes the pwm channel: ---------------");
    for(i = 0; i < 8; i++)
    {
        rt_pin_mode(motor_channel_pin_handle[i].pin_handle, PIN_MODE_OUTPUT);
        LOG_I("Set motor channel pin[%x]    PIN_MODE_OUTPUT",motor_channel_pin_handle[i].pin_handle);
    }

    // 设置引脚初始化为低电平
    for(i = 0; i < 8; i++)
    {
        rt_pin_write(motor_channel_pin_handle[i].pin_handle, PIN_LOW);
        LOG_I("Set motor channel pin[%x]    status: PIN_LOW",motor_channel_pin_handle[i].pin_handle);
    }
    LOG_I("---------- Initializes the pwm pulse value finished! ----------");
    rt_kprintf("\n");
}
//INIT_BOARD_EXPORT(car_pwm_channel_init);



void car_pwm_channel_set(int fl_sta, int fr_sta, int bl_sta, int br_sta)
{
    /* fl_sta set */
    switch(fl_sta)
    {
    case foreward:
        rt_pin_write(motor_channel_pin_handle[0].pin_handle, PIN_HIGH);
        rt_pin_write(motor_channel_pin_handle[1].pin_handle, PIN_LOW);
        break;
    case reversal:
        rt_pin_write(motor_channel_pin_handle[0].pin_handle, PIN_LOW);
        rt_pin_write(motor_channel_pin_handle[1].pin_handle, PIN_HIGH);
        break;
    case stop:
        rt_pin_write(motor_channel_pin_handle[0].pin_handle, PIN_LOW);
        rt_pin_write(motor_channel_pin_handle[1].pin_handle, PIN_LOW);
        break;
    }


    /* fr_sta set */
    switch(fr_sta)
    {
    case foreward:
        rt_pin_write(motor_channel_pin_handle[2].pin_handle, PIN_HIGH);
        rt_pin_write(motor_channel_pin_handle[3].pin_handle, PIN_LOW);
        break;
    case reversal:
        rt_pin_write(motor_channel_pin_handle[2].pin_handle, PIN_LOW);
        rt_pin_write(motor_channel_pin_handle[3].pin_handle, PIN_HIGH);
        break;
    case stop:
        rt_pin_write(motor_channel_pin_handle[2].pin_handle, PIN_LOW);
        rt_pin_write(motor_channel_pin_handle[3].pin_handle, PIN_LOW);
        break;
    }


    /* bl_sta set */
    switch(bl_sta)
    {
    case foreward:
        rt_pin_write(motor_channel_pin_handle[4].pin_handle, PIN_HIGH);
        rt_pin_write(motor_channel_pin_handle[5].pin_handle, PIN_LOW);
        break;
    case reversal:
        rt_pin_write(motor_channel_pin_handle[4].pin_handle, PIN_LOW);
        rt_pin_write(motor_channel_pin_handle[5].pin_handle, PIN_HIGH);
        break;
    case stop:
        rt_pin_write(motor_channel_pin_handle[4].pin_handle, PIN_LOW);
        rt_pin_write(motor_channel_pin_handle[5].pin_handle, PIN_LOW);
        break;
    }


    /* br_sta set */
    switch(br_sta)
    {
    case foreward:
        rt_pin_write(motor_channel_pin_handle[6].pin_handle, PIN_HIGH);
        rt_pin_write(motor_channel_pin_handle[7].pin_handle, PIN_LOW);
        break;
    case reversal:
        rt_pin_write(motor_channel_pin_handle[6].pin_handle, PIN_LOW);
        rt_pin_write(motor_channel_pin_handle[7].pin_handle, PIN_HIGH);
        break;
    case stop:
        rt_pin_write(motor_channel_pin_handle[6].pin_handle, PIN_LOW);
        rt_pin_write(motor_channel_pin_handle[7].pin_handle, PIN_LOW);
        break;
    }
}



void car_control_mode_set(int status)
{
    switch(status)
    {
    case MOTOR_STOP:
        car_pwm_channel_set(2, 2, 2, 2);
        LOG_I("The car control mode is: MOTOR_STOP!");
        break;
    case MOTOR_FORWARD:
        car_pwm_channel_set(0, 0, 0, 0);
        LOG_I("The car control mode is: MOTOR_FORWARD!");
        break;
    case MOTOR_BACKWARD:
        car_pwm_channel_set(1, 1, 1, 1);
        LOG_I("The car control mode is: MOTOR_BACKWARD!");
        break;
    case MOTOR_LEFT:
        car_pwm_channel_set(1, 0, 0, 1);
        LOG_I("The car control mode is: MOTOR_LEFT!");
        break;
    case MOTOR_RIGHT:
        car_pwm_channel_set(0, 1, 1, 0);
        LOG_I("The car control mode is: MOTOR_RIGHT!");
        break;
    case MOTOR_FRONT_LEFT:
        car_pwm_channel_set(2, 0, 0, 2);
        LOG_I("The car control mode is: MOTOR_FRONT_LEFT!");
        break;
    case MOTOR_FRONT_RIGHT:
        car_pwm_channel_set(0, 2, 2, 0);
        LOG_I("The car control mode is: MOTOR_FRONT_RIGHT!");
        break;
    case MOTOR_BACK_LEFT:
        car_pwm_channel_set(1, 2, 2, 1);
        LOG_I("The car control mode is: MOTOR_BACK_LEFT!");
        break;
    case MOTOR_BACK_RIGHT:
        car_pwm_channel_set(2, 1, 1, 2);
        LOG_I("The car control mode is: MOTOR_BACK_RIGHT!");
        break;
    case MOTOR_CLOCKWISE_SPIN:
        car_pwm_channel_set(0, 1, 0, 1);
        LOG_I("The car control mode is: MOTOR_CLOCKWISE_SPIN!");
        break;
    case MOTOR_ANTICLOCKWISE_SPIN:
        car_pwm_channel_set(1, 0, 1, 0);
        LOG_I("The car control mode is: MOTOR_ANTICLOCKWISE_SPIN!");
        break;
    default:
        LOG_E("Invalid car control mode!");
        break;
    }
}
