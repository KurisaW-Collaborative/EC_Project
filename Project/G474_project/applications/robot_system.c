/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-22     Yifang       the first version
 */
#include "robot_system.h"

void robot_system_init(void)
{
    car_pwm_channel_init();
    user_pwm_init();

    Robot_Init(Akm_WheelSpan, Akm_AxleSpan, MG513_GearRatio_30, MG513_EncoderAccuracy_13, Mecanum_85);
}
INIT_APP_EXPORT(robot_system_init);
