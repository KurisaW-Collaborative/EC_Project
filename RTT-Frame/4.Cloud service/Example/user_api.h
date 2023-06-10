/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-11     瓜子的皮       the first version
 */
#ifndef APPLICATIONS_USER_API_USER_API_H_
#define APPLICATIONS_USER_API_USER_API_H_

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "ui.h"
#include "rtthread.h"
#include "mqtt_api.h"
#include "rtdef.h"

#define START_USING_NEWTHREAD 1
#define NO_START_USING_NEWTHREAD 0

typedef enum Connect_status{
    UNUNITED = 0,
    CONNECTING,
}Connect_status;

typedef struct Mqtt_Topic{
    char* send_topic;//通过该topic发送报文
    char* subscribe_topic;//订阅该topic报文
    rt_mutex_t using;
}Mqtt_Topic;

typedef struct Ali_Mqtt_Config{
    void* connect_handle;//mqtt连接句柄
    Mqtt_Topic topic;
    void (*recv_message_handling)(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg);
    void* recv_message_handling_pcontext;
    void (*event_handling)(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg);
    void* event_handling_pcontext;
    iotx_mqtt_topic_info_t mesg;

    Connect_status connect_status ;
    iotx_mqtt_qos_t recv_qos;//服务等级

    int heartbeat_duration ;//心跳持续时间
}Ali_Mqtt_Config;

typedef Ali_Mqtt_Config* Ali_Mqtt_Config_t;

Ali_Mqtt_Config_t WSM_Ali_Mqtt_Config_Create();
void WSM_Ali_Mqtt_Config_Free(Ali_Mqtt_Config_t ali_mqtt_config);
void WSM_Ali_Connect(Ali_Mqtt_Config_t ali_mqtt_config);
void WSM_Ali_Disconnect(Ali_Mqtt_Config_t ali_mqtt_config);
int WSM_Ali_Send(Ali_Mqtt_Config_t ali_mqtt_config);
int WSM_Ali_Recv(Ali_Mqtt_Config_t ali_mqtt_config);

#endif /* APPLICATIONS_USER_API_USER_API_H_ */
