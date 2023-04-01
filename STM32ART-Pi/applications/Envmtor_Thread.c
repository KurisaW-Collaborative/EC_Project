#include "Envmtor_Thread.h"

static rt_thread_t noisemtor_thread;
static rt_thread_t pmtor_thread;


static void Noisemtor_Thread_entry(void *parameter)
{
    // Noisemtor_Thread_s �̵߳���ں���
}

static void Pmtor_Thread_entry(void *parameter)
{
    // Pmtor_Thread_s �̵߳���ں���
}

void Envmtor_Thread(void *parameter)
{
    rt_err_t rt_ret;

    // ���� Noisemtor_Thread_s ���߳�
    noisemtor_thread = rt_thread_create(NOISEMTOR_THREAD_NAME, Noisemtor_Thread_entry, RT_NULL,
                                        NOISEMTOR_THREAD_STACK_SIZE,
                                        NOISEMTOR_THREAD_PRIORITY,
                                        NOISEMTOR_THREAD_TICK);
    if (noisemtor_thread != RT_NULL)
    {
        rt_kprintf("Failed to create noisemtor_thread_s\n");
    }
    rt_ret = rt_thread_startup(noisemtor_thread);
    if (rt_ret == RT_ERROR)
    {
        rt_kprintf("rt_thread_startup:startup noisemtor_thread failing");
    }

    // ���� Pmtor_Thread_s ���߳�
    pmtor_thread = rt_thread_create(PMTOR_THREAD_NAME, Pmtor_Thread_entry, RT_NULL,
                                    PMTOR_THREAD_STACK_SIZE,
                                    PMTOR_THREAD_PRIORITY,
                                    PMTOR_THREAD_TICK);
    if (pmtor_thread != RT_NULL)
    {
        rt_kprintf("Failed to create pmtor_thread_s\n");
    }
    rt_ret = rt_thread_startup(pmtor_thread);
    if (rt_ret == RT_ERROR)
    {
        rt_kprintf("rt_thread_startup:startup pmtor_thread failing");
    }
}
