#include "Capweath_Thread.h"

static rt_thread_t caphutmp_thread;
static rt_thread_t capbmp_thread;
static rt_thread_t capbh_thread;

static void Caphutmp_Thread_entry(void *parameter)//气象采集数据线程子线程温湿度采集线程
{
}

static void Capbmp_Thread_entry(void *parameter)
{

}

static void Capbh_Thread_entry(void *parameter)
{

}

void Capweath_Thread(void *parameter)//气象采集数据线程
{
    rt_err_t rt_ret;
    caphutmp_thread = rt_thread_create(CAPHUTMP_THREAD_NAME,Caphutmp_Thread_entry,NULL,CAPHUTMP_THREAD_STACK_SIZE, CAPHUTMP_THREAD_PRIORITY,CAPHUTMP_THREAD_TICK);
    if(caphutmp_thread == RT_NULL)
    {
            rt_kprintf("rt_thread_create:create caphutmp_thread_entry failing");
    }
    rt_ret = rt_thread_startup( caphutmp_thread);
    if(rt_ret == RT_ERROR)
    {
            rt_kprintf("rt_thread_startup:startup caphutmp_thread_entry failing");
    }

    capbmp_thread = rt_thread_create(CAPBMP_THREAD_NAME,Capbmp_Thread_entry,NULL,CAPBMP_THREAD_STACK_SIZE, CAPBMP_THREAD_PRIORITY,CAPBMP_THREAD_TICK);
    if(capbmp_thread == RT_NULL)
    {
            rt_kprintf("Capbmp_Thread_entry:create Capbmp_Thread_entry failing");
    }
    rt_ret = rt_thread_startup( capbmp_thread);
    if(rt_ret == RT_ERROR)
    {
            rt_kprintf("rt_thread_startup:startup Capbmp_Thread_entry failing");
    }

    capbh_thread = rt_thread_create(CAPBH_THREAD_NAME,Caphutmp_Thread_entry,NULL,CAPBH_THREAD_STACK_SIZE,  CAPBH_THREAD_PRIORITY,CAPBH_THREAD_TICK);
    if(capbh_thread == RT_NULL)
    {
            rt_kprintf("rt_thread_create:create caphutmp_thread_entry failing");
    }
    rt_ret = rt_thread_startup( capbh_thread);
    if(rt_ret == RT_ERROR)
    {
            rt_kprintf("rt_thread_startup:startup caphutmp_thread_entry failing");
    }
}
