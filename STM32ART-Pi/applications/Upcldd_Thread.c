#include "Upcldd_Thread.h"

static rt_thread_t upnoisemtor_thread;
static rt_thread_t uppmtor_thread;
static rt_thread_t uphutmp_thread;
static rt_thread_t upbmp_thread;
static rt_thread_t upbh_thread;

static void Upnoisemtor_Thread_entry(void *parameter)
{
    // upnoisemtor_thread ���߳���ں���
}

static void Uppmtor_Thread_entry(void *parameter)
{
    // uppmtor_thread ���߳���ں���
}

static void Uphutmp_Thread_entry(void *parameter)
{
    // uphutmp_thread ���߳���ں���
}

static void Upbmp_Thread_entry(void *parameter)
{
    // upbmp_thread ���߳���ں���
}

static void Upbh_Thread_entry(void *parameter)
{
    // upbh_thread ���߳���ں���
}

void Upcldd_Thread(void *parameter)
{
    rt_err_t rt_ret;

    // ���� upnoisemtor_thread ���߳�
    upnoisemtor_thread = rt_thread_create(UPNOISEMTOR_THREAD_NAME, Upnoisemtor_Thread_entry, RT_NULL,
    UPNOISEMTOR_THREAD_STACK_SIZE, 10, 10);
    if (upnoisemtor_thread == RT_NULL)
    {
        rt_kprintf("rt_thread_create:create upnoisemtor_thread failing");
    }

    rt_ret = rt_thread_startup(upnoisemtor_thread);
    if (rt_ret == RT_ERROR)
    {
        rt_kprintf("rt_thread_startup:startup upnoisemtor_thread failing");
    }

    // ���� uppmtor_thread ���߳�
    uppmtor_thread = rt_thread_create(UPPMTOR_THREAD_NAME, Uppmtor_Thread_entry, RT_NULL,
    UPPMTOR_THREAD_STACK_SIZE, 10, 10);
    if (uppmtor_thread != RT_NULL)
    {
        rt_kprintf("rt_thread_create:create uppmtor_thread failing");
    }
    rt_ret = rt_thread_startup(uppmtor_thread);
    if (rt_ret == RT_ERROR)
    {
        rt_kprintf("rt_thread_startup:startup uppmtor_thread failing");
    }

    // ���� uphutmp_thread ���߳�
    uphutmp_thread = rt_thread_create(UPHUTMP_THREAD_NAME, Uphutmp_Thread_entry, RT_NULL,
    UPHUTMP_THREAD_STACK_SIZE, 10, 10);
    if (uphutmp_thread != RT_NULL)
    {
        rt_kprintf("rt_thread_create:create uphutmp_thread failing");
    }

    rt_ret = rt_thread_startup(uphutmp_thread);
    if (rt_ret == RT_ERROR)
    {
        rt_kprintf("rt_thread_startup:startup uphutmp_thread failing");
    }

    // ���� upbmp_thread ���߳�
    upbmp_thread = rt_thread_create(UPBMP_THREAD_NAME, Upbmp_Thread_entry, RT_NULL,
    UPBMP_THREAD_STACK_SIZE, 10, 10);
    if (upbmp_thread != RT_NULL)
    {
        rt_kprintf("rt_thread_create:create upbmp_thread failing");
    }
    rt_ret = rt_thread_startup(upbmp_thread);
    if (rt_ret == RT_ERROR)
    {
        rt_kprintf("rt_thread_startup:startup upbmp_thread failing");
    }

    // ���� upbh_thread ���߳�
    upbh_thread = rt_thread_create(UPBH_THREAD_NAME, Upbh_Thread_entry, RT_NULL,
    UPBH_THREAD_STACK_SIZE, 10, 10);
    if (upbh_thread != RT_NULL)
    {
        rt_kprintf("rt_thread_create:create upbh_thread failing");
    }
    rt_ret = rt_thread_startup(upbh_thread);
    if (rt_ret == RT_ERROR)
    {
        rt_kprintf("rt_thread_startup:startup upbh_thread failing");
    }
}
