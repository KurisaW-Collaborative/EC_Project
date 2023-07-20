/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-13     瓜子的皮       the first version
 */
#include "../ui.h"


struct rt_messagequeue ui_tigger_mq;
static rt_uint8_t msg_pool[2048];
static int events;

static bool thread_using_flag =1;
static bool first_init =1 ;

#define GET_BIT(x, bit) ((x & (1 << bit)) >> bit)   /* 获取第bit位 */
static void show_tigger_ui_entry()
{
    while (1)
    {
        show_main_ui();
        for(int i =0; i!=10;i++) rt_thread_mdelay(3000);
        show_kinestate_ui();
        for(int i =0; i!=10;i++) rt_thread_mdelay(1000);

        if (GET_BIT(events, 0))
        {
            show_error_ui();
            set_error_info("Urban harsh environment");
            rt_thread_mdelay(3000);
        }
        if (GET_BIT(events, 1))
        {
            show_error_ui();
            set_error_info("Attitude anomaly");
            rt_thread_mdelay(3000);
        }
        if (GET_BIT(events, 2))
        {
            show_warning_ui();
            set_warning_info("Fire Warning");
            rt_thread_mdelay(3000);
        }
        if (GET_BIT(events, 3))
        {
            show_warning_ui();
            set_warning_info("Electric Warning");
            rt_thread_mdelay(3000);
        }
    }
}

static void ui_tigger_event_entry()
{

    if(thread_using_flag)
    {
        while(1)
        {
            if(thread_using_flag)
            {
                rt_uint8_t buf = 0;
                rt_mq_recv(&ui_tigger_mq, &buf, sizeof(buf), 3000);
                switch(buf)
                {
                    case BAD_ENVIRONMENT_START   : events |= (1 << 0) ; break;
                    case BAD_ENVIRONMENT_END     : events &= ~(1 << 0); break;
                    case ABNORMAL_ATTITUDE_START : events |= (1 << 1) ; break;
                    case ABNORMAL_ATTITUDE_END   : events &= ~(1 << 1); break;
                    case FIRE_HAZARD_START       : events |= (1 << 2) ; break;
                    case FIRE_HAZARD_END         : events &= ~(1 << 2); break;
                    case LOW_BATTERY_START       : events |= (1 << 3) ; break;
                    case LOW_BATTERY_END         : events &= ~(1 << 3); break;
                }
            }
            else
                return ;

        }
    }
    return ;
}



void ui_tigger_start()
{
    if(first_init)
     {
        rt_mq_init(&ui_tigger_mq,"ui_tigger_mq",&msg_pool[0],1,sizeof(msg_pool),RT_IPC_FLAG_PRIO);       /* 如果有多个线程等待，优先级大小的方法分配消息 */
        rt_thread_t show_tigger_ui = rt_thread_create("show_tigger_ui", show_tigger_ui_entry, RT_NULL, 4096, 10, 10);
        if (show_tigger_ui != RT_NULL)
            rt_thread_startup(show_tigger_ui);
        first_init = 0;
     }

    rt_thread_t ui_tigger_event = rt_thread_create("ui_tigger_event_entry", ui_tigger_event_entry, RT_NULL, 4096, 10, 10);

     if (ui_tigger_event != RT_NULL)
     {
         rt_thread_startup(ui_tigger_event);
     }
}
//INIT_APP_EXPORT(ui_tigger_start);
MSH_CMD_EXPORT(ui_tigger_start,ui_tigger_start);

void ui_tigger_end()
{
    thread_using_flag = 0;
}
//INIT_APP_EXPORT(ui_tigger_event);
