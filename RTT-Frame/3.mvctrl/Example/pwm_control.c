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

#define DBG_LEVEL DBG_INFO
#define DBG_SECTION_NAME  "pwm_ctrl"
#include <rtdbg.h>

struct rt_device_pwm * pwm_drv = RT_NULL;

struct pwm_user_set pwm_config = {
    .pwm_device_name    = "pwm8",         /* pwm device pointer */
    .pwm_channel        = RT_NULL,              /* pwm device channel */
    .pwm_period         = PWM_PERIOD,           /* set pwm initial pwm_period */
    .pwm_pulse          = PWM_PERIOD * 0.8      /* set pwm initial pwm_pulse */
};


/* pwm init */
int user_pwm_init(void)
{
    rt_err_t ret;

    pwm_drv = (struct rt_device_pwm *)rt_device_find("pwm8");
    if(pwm_drv)
    {
        rt_kprintf("\n");
        LOG_I("--------------- Initializes the pwm pulse value ---------------");
        /* initial pwm */
        for(int i = 1; i < 5; i++)
        {
            pwm_config.pwm_channel = i;
            ret = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, pwm_config.pwm_pulse);
            if(ret == -RT_ENOSYS)
                LOG_E("%d. pwm set %d\r",i,ret);
            ret = RT_EOK;
            rt_pwm_enable(pwm_drv, i);
            LOG_I("[%d] PWM set: channel[%x]---period[%d]---pulse[%d]",ret, pwm_config.pwm_channel, pwm_config.pwm_period, pwm_config.pwm_pulse);
        }
    }
    else
    {
        LOG_E("pwm_drv not find!");
    }
    LOG_I("---------- Initializes the pwm pulse value finished！ ---------");
    rt_kprintf("\n");

    return ret;
}

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
        rt_kprintf("please input :pwm_set_pulse <pwm_dev> <percent>\r");
        err = - RT_ERROR;
        return err;
    }
    else
    {
        if(strcmp(argv[1],"pwm8")==0)
        {
            LOG_I("----------- Update the current pwm pulse value ------------");
            rt_kprintf("\n");
            current_pulse = pwm_config.pwm_period * atoi(argv[2]) / 100;

            for(int i = 1; i < 5; i++)
            {
                pwm_config.pwm_channel = i;
                err = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, current_pulse);
                if(err == -RT_ENOSYS)
                    LOG_E("%d. current pwm set %d\r", i, err);
                LOG_I("[channel %d] The current pwm duty cycle value was updated: %s", pwm_config.pwm_channel, argv[2]);
                err = RT_EOK;
            }
        }
        else
        {
            err = RT_EOK;
            return err;
        }
        rt_kprintf("\n");
        LOG_I("------ The current pwm pulse value has been updated. ------");

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


void user_pwm_switch_level(int level)
{
    int Level = level;
    rt_err_t err = RT_EOK;

    switch(Level)
    {
        case 1:
        {
            pwm_config.pwm_pulse = PWM_PERIOD * 0.4;
            for(int i = 1; i < 5; i++)
            {
                pwm_config.pwm_channel = i;
                err = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, pwm_config.pwm_pulse);
                if(err == -RT_ENOSYS)
                    LOG_E("%d. current pwm set %d\r", i, err);
                err = RT_EOK;
            }
            LOG_I("Level 1:The duty cycle is %d%", pwm_config.pwm_pulse / pwm_config.pwm_period * 100);
            break;
        }
        case 2:
        {
            pwm_config.pwm_pulse = PWM_PERIOD * 0.7;
            for(int i = 1; i < 5; i++)
            {
                pwm_config.pwm_channel = i;
                err = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, pwm_config.pwm_pulse);
                if(err == -RT_ENOSYS)
                    LOG_E("%d. current pwm set %d\r", i, err);
                err = RT_EOK;
            }
            LOG_I("Level 2:The duty cycle is %d%", pwm_config.pwm_pulse / pwm_config.pwm_period * 100);
            break;
        }
        case 3:
        {
            pwm_config.pwm_pulse = PWM_PERIOD * 1;
            for(int i = 1; i < 5; i++)
            {
                pwm_config.pwm_channel = i;
                err = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, pwm_config.pwm_pulse);
                if(err == -RT_ENOSYS)
                    LOG_E("%d. current pwm set %d\r", i, err);
                err = RT_EOK;
            }
            LOG_I("Level 3:The duty cycle is %d%", pwm_config.pwm_pulse / pwm_config.pwm_period * 100);
            break;
        }
        default:
            LOG_E("Please input the level value to change duty cycle!");
    }

}


int target_limit_int(int refer_value, int cri_value)
{
    if (refer_value < -cri_value)
        return -refer_value;
    else if (refer_value > cri_value)
        return cri_value;
    else
        return refer_value;
}


/*
 * 思考pwm_config.pwm_pulse这个值是否会改变,debug查看
 * 此处将pwm_config.pwm_pulse值替换成encoder值
 * */
void pwm_limit(int refer_value)
{
    rt_err_t ret = -RT_ENOSYS;

    for(int i = 1; i < 5; i++)
    {
        pwm_config.pwm_channel = i;
        ret = rt_pwm_set(pwm_drv, pwm_config.pwm_channel, pwm_config.pwm_period, pwm_config.pwm_pulse);
        if(ret == -RT_ENOSYS)
            LOG_E("%d. pwm set %d\r",i, ret);
        ret = RT_EOK;
    }


//    MOTOR_A.Motor_Pwm = target_limit_int(MOTOR_A.Motor_Pwm, refer_value);
//    MOTOR_B.Motor_Pwm = target_limit_int(MOTOR_B.Motor_Pwm, refer_value);
//    MOTOR_C.Motor_Pwm = target_limit_int(MOTOR_C.Motor_Pwm, refer_value);
//    MOTOR_D.Motor_Pwm = target_limit_int(MOTOR_D.Motor_Pwm, refer_value);
}
