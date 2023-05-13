/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-11     瓜子的皮       the first version
 */
#include "user_api.h"

static void *mqtt_client = NULL;
/* MQTT客户端事件回调函数 */
//static void event_handler(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
//{
//    switch (msg->event_type)
//    {
//        case IOTX_MQTT_EVENT_DISCONNECT:
//            rt_kprintf("MQTT client disconnected\n");
//            break;
//        case IOTX_MQTT_EVENT_SUBCRIBE_SUCCESS:
//            rt_kprintf("MQTT client subscribe success\n");
//            break;
//        case IOTX_MQTT_EVENT_SUBCRIBE_NACK:
//            rt_kprintf("MQTT client subscribe fail\n");
//            break;
//        case IOTX_MQTT_EVENT_PUBLISH_SUCCESS:
//            rt_kprintf("MQTT client publish success\n");
//            break;
//        case IOTX_MQTT_EVENT_PUBLISH_NACK:
//            rt_kprintf("MQTT client publish fail\n");
//            break;
//        case IOTX_MQTT_EVENT_PUBLISH_RECEIVED://在IOT_MQTT_Yield函数接收到数据后 设置该标志位触发该事件
//            rt_kprintf("MQTT client received message\n");
//            break;
//        default:
//            break;
//    }
//}

void Ali_Topic_Handle(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    // 处理MQTT主题消息
    iotx_mqtt_topic_info_pt topic_info = (iotx_mqtt_topic_info_pt) msg->msg;
    rt_kprintf("recv message:%s\n", topic_info->ptopic);

}

int Ali_Connect_Init(Ali_Mqtt_Config_t ali_handle)
{
    static iotx_mqtt_param_t mqtt_params;

    memset(&mqtt_params, 0x0, sizeof(mqtt_params));
    mqtt_params.handle_event.h_fp = ali_handle->event_handling;
    mqtt_params.handle_event.pcontext = ali_handle->event_handling_pcontext;

    if (!mqtt_client)
        mqtt_client = IOT_MQTT_Construct(&mqtt_params); //为空则建立连接　如果已经建立过则无需再建立连接

    ali_handle->connect_handle = mqtt_client;
    if (mqtt_client == NULL)
    {
        rt_kprintf("MQTT client create failed\n");
        return -1;
    }
    int rc = IOT_MQTT_CheckStateNormal(mqtt_client);
    if (rc == 1)
        rt_kprintf("MQTT client status is success\n", rc);
    else
    {
        rt_kprintf("MQTT client status is failed,err: %d");
        return -1;
    }
    ali_handle->connect_status = CONNECTING;
    return 0;
}

void Ali_Send(void* parameter)
{
    char *topic = "/sys/if15bhaF5KF/art-pi/thing/event/property/post";
//    char *payload = "{"
//            "\"id\":\"123\","
//            "\"version\":\"1.0\","
//            "\"params\":{"
//                "\"GeoLocation\":{"
//                    "\"Longitude\":1.12,"
//                    "\"Latitude\":1.13"
//                    "},"
//                "\"demo\":\"1000\""
//                 "},"
//            "\"method\":\"thing.event.property.post\""
//            "}";
    char *payload = "{"
            "\"id\":\"123\","
            "\"version\":\"1.0\","
            "\"params\":{"
            "\"Longitude\":1,"
            "\"Latitude\":1,"
            "\"demo\":\"1005\""
            "},"
            "\"method\":\"thing.event.property.post\""
            "}";
    int rc;
    iotx_mqtt_topic_info_t mesg;
    mesg.dup = 0;
    mesg.packet_id = 0;
    mesg.payload = payload;
    mesg.payload_len = strlen(payload);
    mesg.ptopic = topic;
    mesg.qos = IOTX_MQTT_QOS0;
    mesg.retain = 0;
    mesg.topic_len = strlen(topic);
    rc = IOT_MQTT_Publish(mqtt_client, topic, &mesg);

    if (rc < 0)
    {
        rt_kprintf("publish failed, res = %d", rc);
        return;
    }
    rt_thread_delay(1000);
}

void Ali_Recv(void* parameter)
{
    int rc;
    char *topic = "/sys/if15bhaF5KF/art-pi/thing/event/property/post_reply";
    rc = IOT_MQTT_Subscribe(mqtt_client, topic, IOTX_MQTT_QOS0, Ali_Topic_Handle, NULL);
    if (rc < 0)
    {
        rt_kprintf("MQTT subscribe failed: %d\n", rc);
        return;
    }
    while (1)
    {
        IOT_MQTT_Yield(mqtt_client, 100);
    }
}

Ali_Mqtt_Config_t WSM_Ali_Mqtt_Config_Create()
{
    Ali_Mqtt_Config_t new_ali_mqtt_config = (Ali_Mqtt_Config_t) rt_malloc(sizeof(Ali_Mqtt_Config));
    if (new_ali_mqtt_config == NULL)
    {
        rt_kprintf("In Ali_Mqtt_Config_Create,Failed to rt_malloc \n");
        return NULL;
    }

    new_ali_mqtt_config->heartbeat_duration = 100;
//    new_ali_mqtt_config->topic.using = rt_mutex_create(NULL, RT_IPC_FLAG_FIFO);
//    if (new_ali_mqtt_config->topic.using == RT_NULL)
//    {
//        rt_kprintf("In Ali_Mqtt_Config_Create,Failed to create mutex\n");
//        return NULL;
//    }
    return new_ali_mqtt_config;
}

void WSM_Ali_Mqtt_Config_Free(Ali_Mqtt_Config_t ali_mqtt_config)
{
    if (ali_mqtt_config == NULL)
    {
        rt_kprintf("please first using Ali_Mqtt_Config_Create\n");
        return;
    }

    if(ali_mqtt_config->connect_status == CONNECTING )
    {
        IOT_MQTT_Destroy(ali_mqtt_config->connect_handle);
        ali_mqtt_config->connect_status = UNUNITED;
    }
//    rt_mutex_delete(ali_mqtt_config->topic.using);
    rt_free((void*) ali_mqtt_config);
}

void Mqtt_Yield(void *time)
{
    while(1)
    {
        IOT_MQTT_Yield(mqtt_client, (int)time);
    }
}

//开启连接并开始mqtt心跳
void WSM_Ali_Connect(Ali_Mqtt_Config_t ali_mqtt_config)
{
    int err = 0;
    err = Ali_Connect_Init(ali_mqtt_config);
    if (err == -1)
    {
        rt_kprintf("In WSM_Ali_Connect Ali_Init failed\n");
        return;
    }


    rt_thread_t mqtt_yield_thread = rt_thread_create("Ali_Send_Thread", Mqtt_Yield, (void *) ali_mqtt_config->heartbeat_duration,
                                                        4096, 10,20);
   rt_thread_startup(mqtt_yield_thread);
}

void Ali_Send_Thread(void* parameter)
{
    Ali_Mqtt_Config_t ali_mqtt_config = parameter;

    ali_mqtt_config->mesg.ptopic = ali_mqtt_config->topic.send_topic;
    iotx_mqtt_topic_info_t mesg = ali_mqtt_config->mesg;
    IOT_MQTT_Publish(ali_mqtt_config->connect_handle, ali_mqtt_config->topic.send_topic, &mesg);



    return;
}

int WSM_Ali_Send(Ali_Mqtt_Config_t ali_mqtt_config)
{
    if (ali_mqtt_config == NULL)
    {
        rt_kprintf("please first using Ali_Mqtt_Config_Create\n");
        return -1;
    }

    if (ali_mqtt_config->connect_status == UNUNITED)
    {
        rt_kprintf("In WSM_Ali_Send,Not in the connected state");
    }

    rt_thread_t send_thread = rt_thread_create("Ali_Send_Thread", Ali_Send_Thread, (void *) ali_mqtt_config, 4096, 10,
            20);
    rt_thread_startup(send_thread);

    return 0;
}


int WSM_Ali_Recv(Ali_Mqtt_Config_t ali_mqtt_config)
{
    if (ali_mqtt_config == NULL)
    {
        rt_kprintf("please first using Ali_Mqtt_Config_Create\n");
        return -1;
    }

    if (ali_mqtt_config->connect_status == UNUNITED)
    {
        rt_kprintf("In WSM_Ali_Subscribe,Not in the connected state");
    }

    int err = IOT_MQTT_Subscribe(ali_mqtt_config->connect_handle, ali_mqtt_config->topic.subscribe_topic, ali_mqtt_config->recv_qos,
                                        ali_mqtt_config->recv_message_handling, ali_mqtt_config->recv_message_handling_pcontext);
    if (err == -1)
    {
        rt_kprintf("MQTT subscribe failed\n");
        return -1;
    }

    err = IOT_MQTT_Unsubscribe(ali_mqtt_config->connect_handle, ali_mqtt_config->topic.subscribe_topic);

    if (err == -1)
    {
        rt_kprintf("MQTT Unsubscribe failed\n");
        return -1;
    }
    return 0;
}
