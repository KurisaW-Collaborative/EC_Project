/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-20     Yifang       the first version
 */

#include "pwm_control.h"
#include "string.h"

struct pwm_user_set pwm_config = {
    .pwm_device_name    = "pwm8",         /* pwm device pointer */
    .pwm_channel        = RT_NULL,              /* pwm device channel */
    .pwm_period         = PWM_PERIOD,           /* set pwm initial pwm_period */
    .pwm_pulse          = 1000000               /* set pwm initial pwm_pulse */
};

struct rt_device_pwm * pwm_drv = RT_NULL;

/* pwm init */
int user_pwm_init(void)
{
    rt_err_t ret;

    pwm_drv = (struct rt_device_pwm *)rt_device_find("pwm8");
    if(pwm_drv)
    {
        rt_kprintf("\n********** Initializes the pwm pulse value **********\n");
        /* initial pwm */
        for(int i = 1; i < 5; i++)
        {
            pwm_config.pwm_channel = i;
            ret = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, pwm_config.pwm_pulse);
            if(ret > 0)
                rt_kprintf("%d. pwm set %d\r\n",i,ret);
            ret = RT_EOK;
            rt_pwm_enable(pwm_drv, i);
        }
    }
    else
    {
        rt_kprintf("pwm_drv not find!\n");
    }

    return ret;
}
//INIT_APP_EXPORT(user_pwm_init);
MSH_CMD_EXPORT(user_pwm_init,user_pwm_init);

/* pwm set pulse with user's configuration,and it can be modify! */
int pwm_ex_set_pulse(int argc,char **argv)
{
    rt_uint32_t current_pulse = 0;
    rt_err_t err = RT_EOK;
    if(argc == 1)
    {
        err = RT_EOK;
        return err;
    }
    else if(argc == 2)
    {
        rt_kprintf("please input :pwm_set_pulse <pwm_dev> <percent>\r\n");
        err = - RT_ERROR;
        return err;
    }
    else
    {
        if(strcmp(argv[1],"pwm8")==0)
        {
            rt_kprintf("\n********** Set the current pwm pulse value **********\n");
            current_pulse = pwm_config.pwm_period * atoi(argv[2]) / 100;

            for(int i = 1; i < 5; i++)
            {
                pwm_config.pwm_channel = i;
                err = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, current_pulse);
                if(err < 0)
                    rt_kprintf("%d. current pwm set %d\r\n",i,err);
                err = RT_EOK;
            }

            rt_kprintf("The current pwm pulse value has been updated.\n");
        }
        else
        {
            err = RT_EOK;
            return err;
        }
        return err;
    }
}
MSH_CMD_EXPORT(pwm_ex_set_pulse, <input percent(%)>to set the pwm pulse);

rt_err_t pwm_set_pulse(struct rt_device_pwm * pwm_dev,rt_uint32_t pulse_val)
{
    rt_err_t ret = RT_EOK;

    RT_ASSERT(pwm_dev);

    ret = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, pulse_val);

    return ret;
}

rt_err_t pwm_enable(struct rt_device_pwm * pwm_dev)
{
    rt_err_t ret = RT_EOK;

    ret = rt_pwm_enable(pwm_dev, pwm_config.pwm_channel);
    return ret;
}

rt_err_t pwm_disable(struct rt_device_pwm * pwm_dev)
{
    rt_err_t ret = RT_EOK;

    ret = rt_pwm_disable(pwm_dev, 0);
    return ret;
}
