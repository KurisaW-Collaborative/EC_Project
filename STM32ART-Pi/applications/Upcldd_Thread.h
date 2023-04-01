#ifndef __UPCLDD_THREAD_H__
#define __UPCLDD_THREAD_H__

#include <rtthread.h>

#define UPCLDD_THREAD_NAME          "upcldd"
#define UPCLDD_THREAD_STACK_SIZE        512
#define UPCLDD_THREAD_PRIORITY             10
#define UPCLDD_THREAD_TICK                 10

#define UPNOISEMTOR_THREAD_NAME     "upnoisemtor"
#define UPPMTOR_THREAD_NAME         "uppmtor"
#define UPHUTMP_THREAD_NAME         "uphutmp"
#define UPBMP_THREAD_NAME           "upbmp"
#define UPBH_THREAD_NAME            "upbh"

#define UPNOISEMTOR_THREAD_STACK_SIZE    512
#define UPPMTOR_THREAD_STACK_SIZE        512
#define UPHUTMP_THREAD_STACK_SIZE        512
#define UPBMP_THREAD_STACK_SIZE          512
#define UPBH_THREAD_STACK_SIZE           512

void Upcldd_Thread(void *parameter);


#endif /* __UPCLDD_THREAD_H__ */
