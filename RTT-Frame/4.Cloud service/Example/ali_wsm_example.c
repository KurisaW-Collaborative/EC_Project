/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-13     瓜子的皮       the first version
 */
#include "user_api.h"
static void event_handler(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    switch (msg->event_type)
    {
        case IOTX_MQTT_EVENT_DISCONNECT:
            rt_kprintf("MQTT client disconnected\n");
            break;
        case IOTX_MQTT_EVENT_SUBCRIBE_SUCCESS:
            rt_kprintf("MQTT client subscribe success\n");
            break;
        case IOTX_MQTT_EVENT_SUBCRIBE_NACK:
            rt_kprintf("MQTT client subscribe fail\n");
            break;
        case IOTX_MQTT_EVENT_PUBLISH_SUCCESS:
            rt_kprintf("MQTT client publish success\n");
            break;
        case IOTX_MQTT_EVENT_PUBLISH_NACK:
            rt_kprintf("MQTT client publish fail\n");
            break;
        case IOTX_MQTT_EVENT_PUBLISH_RECEIVED://在IOT_MQTT_Yield函数接收到数据后 设置该标志位触发该事件
            rt_kprintf("MQTT client received message\n");
            break;
        default:
            break;
    }
}

static void Ali_Topic_Handle(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    // 处理MQTT主题消息
    iotx_mqtt_topic_info_pt topic_info = (iotx_mqtt_topic_info_pt) msg->msg;
    rt_kprintf("recv message:%s\n", topic_info->ptopic);

}

int ALI(void)
{
    Ali_Mqtt_Config_t ali_mqtt_config = WSM_Ali_Mqtt_Config_Create();

        ali_mqtt_config->event_handling = event_handler;
        ali_mqtt_config->event_handling_pcontext = NULL;
        WSM_Ali_Connect(ali_mqtt_config);

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

        ali_mqtt_config->topic.send_topic = "/sys/if15rXROFnw/art_pi/thing/event/property/post";
        ali_mqtt_config->mesg.dup = 0;
        ali_mqtt_config->mesg.packet_id = 0;
        ali_mqtt_config->mesg.payload = payload;
        ali_mqtt_config->mesg.payload_len = strlen(payload);
        ali_mqtt_config->mesg.ptopic = ali_mqtt_config->topic.send_topic;//这步可以省略 只要配置ali_mqtt_config->topic.send_topic即可
        ali_mqtt_config->mesg.qos = IOTX_MQTT_QOS1;
        ali_mqtt_config->mesg.retain = 0;
        ali_mqtt_config->mesg.topic_len = strlen(ali_mqtt_config->topic.send_topic);
        WSM_Ali_Send(ali_mqtt_config);


        ali_mqtt_config->topic.subscribe_topic = "/sys/if15rXROFnw/art_pi/thing/event/property/post_reply";
        ali_mqtt_config->recv_message_handling = Ali_Topic_Handle;
        ali_mqtt_config->recv_message_handling_pcontext = NULL;
        ali_mqtt_config->recv_qos = IOTX_MQTT_QOS2;
        WSM_Ali_Recv( ali_mqtt_config);
        return 0;
}
MSH_CMD_EXPORT(ALI, AL);
