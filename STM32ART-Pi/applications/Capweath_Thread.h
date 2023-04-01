#ifndef __CAPWATH__H
#define __CAPWATH__H

#include <rtthread.h>
#include <rtdevice.h>

#define CAPWETH_THREAD_NAME     "capweath"
#define CAPWETH_THREAD_STACK_SIZE      512
#define CAPWETH_THREAD_TICK            10
#define CAPWETH_THREAD_PRIORITY        9

#define CAPHUTMP_THREAD_NAME    "caphutmp"
#define CAPBMP_THREAD_NAME      "capbmp"
#define CAPBH_THREAD_NAME       "capbh"

#define CAPHUTMP_THREAD_STACK_SIZE  512
#define CAPHUTMP_THREAD_TICK               10
#define CAPHUTMP_THREAD_PRIORITY           10

#define CAPBMP_THREAD_STACK_SIZE    512
#define CAPBMP_THREAD_PRIORITY             10
#define CAPBMP_THREAD_TICK                 10

#define CAPBH_THREAD_STACK_SIZE     512
#define CAPBH_THREAD_PRIORITY              10
#define CAPBH_THREAD_TICK                  10

void Capweath_Thread(void *parameter);//气象采集数据线程

#endif
