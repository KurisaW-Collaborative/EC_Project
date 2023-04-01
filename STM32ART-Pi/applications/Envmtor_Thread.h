#ifndef __ENVMTOR_THREAD_H__
#define __ENVMTOR_THREAD_H__

#include <rtthread.h>

#define NOISEMTOR_THREAD_NAME       "noisemtor"
#define NOISEMTOR_THREAD_STACK_SIZE 512
#define NOISEMTOR_THREAD_PRIORITY   10
#define NOISEMTOR_THREAD_TICK       10

#define PMTOR_THREAD_NAME           "pmtor"
#define PMTOR_THREAD_STACK_SIZE     512
#define PMTOR_THREAD_PRIORITY       10
#define PMTOR_THREAD_TICK       10


// 线程入口函数声明
void Envmtor_Thread(void *parameter);

#endif /* __ENVMTOR_THREAD_H__ */
