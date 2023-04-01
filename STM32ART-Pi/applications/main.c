/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "Capweath_Thread.h"
#include "Upcldd_Thread.h"
#include "Envmtor_Thread.h"
#include "drv_common.h"


#define LED_PIN GET_PIN(I, 8)

static rt_thread_t  capweth_thread;
static rt_thread_t  upcldd_thread;


int main(void)
{
    rt_err_t rt_ret;
    capweth_thread = rt_thread_create( CAPWETH_THREAD_NAME,Capweath_Thread,NULL,CAPWETH_THREAD_STACK_SIZE,CAPWETH_THREAD_PRIORITY,CAPWETH_THREAD_TICK);
    if(capweth_thread == RT_NULL)
    {
        rt_kprintf("rt_thread_create:create capweath_thread failing");
    }
    rt_ret = rt_thread_startup(capweth_thread);
    if(rt_ret == RT_NULL)
    {
        rt_kprintf("rt_thread_startup:startup capweath_thread failing");
    }

    upcldd_thread = rt_thread_create( UPCLDD_THREAD_NAME,Upcldd_Thread,NULL,UPCLDD_THREAD_STACK_SIZE,UPCLDD_THREAD_PRIORITY,UPCLDD_THREAD_TICK);
    if(capweth_thread == RT_NULL)
    {
        rt_kprintf("rt_thread_create:create capweath_thread failing");
    }
    rt_ret = rt_thread_startup(upcldd_thread);
    if(rt_ret == RT_NULL)
    {
        rt_kprintf("rt_thread_startup:startup capweath_thread failing");
    }

    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


