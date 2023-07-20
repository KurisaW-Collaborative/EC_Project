/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-20     Yifang       the first version
 */
#ifndef APPLICATIONS_PWM_CONTROL_H_
#define APPLICATIONS_PWM_CONTROL_H_

#include "robot_system.h"

#define PWM_DEV_NAME   ("pwm8")

#define PWM_PERIOD  100000  //max:385506

struct pwm_user_set
{
    struct rt_device_pwm        *pwm_device_name;        /* pwm device */
    rt_int8_t                    pwm_channel;            /* pwm channel */
    rt_uint32_t                  pwm_period;             /* pwm period */
    rt_uint32_t                  pwm_pulse;              /* pwm pulse */
};

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

int user_pwm_init(void);
rt_err_t pwm_set_pulse(struct rt_device_pwm * pwm_dev,rt_uint32_t pulse_val);
rt_err_t pwm_enable(struct rt_device_pwm * pwm_dev);
rt_err_t pwm_disable(struct rt_device_pwm * pwm_dev);

void user_pwm_switch_level(int level);

#endif /* APPLICATIONS_PWM_CONTROL_H_ */
