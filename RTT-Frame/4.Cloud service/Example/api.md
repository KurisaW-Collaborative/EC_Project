### //这是对阿里云物联网mqtt服务的二次封装

### 结构体介绍

```c
 typedef struct Mqtt_Topic{
    char* send_topic;//通过该topic发送报文
    char* subscribe_topic;//订阅该topic报文
}Mqtt_Topic;

typedef struct {
    uint16_t        packet_id;//包标识符（Packet Identifier），用于标识特定的MQTT消息。通常在发布消息时分配，用于在收到确认或回复时进行匹配。
    uint8_t         qos;//服务质量等级（Quality of Service），指示消息的传递质量和可靠性。取值范围为0、1或2，分别对应不同的传输保证级别。
    uint8_t         dup;//：重复标志（Duplicate Flag），用于指示消息是否是重复发送的副本。值为1表示是重复发送的消息，值为0表示不是重复发送的消息。
    uint8_t         retain;//retain：保留标志（Retain Flag），用于指示服务器是否应该保留该消息的最新副本，并将其传递给新的订阅者。值为1表示服务器应该保留消息，值为0表示不应该保留消息。
    uint16_t        topic_len;//topic_len：主题长度（Topic Length），指示主题字符串的长度（不包括结尾的空字
    uint32_t        payload_len;//负载长度（Payload Length），指示负载数据的长度。发送数据的长度
    const char     *ptopic;//目标主题（topic）
    const char     *payload;//负载信息指针，指向包含负载数据的缓冲区
}iotx_mqtt_topic_info_t;

struct Ali_Mqtt_Config{
    void* connect_handle;//mqtt连接句柄 由内部函数处理 无需配置
    
    Mqtt_Topic topic;//topic结构体 结构体含义看上方结构体说明
    void (*recv_message_handling)(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg);//接收消息后的回调函数 在订阅topic（想要接收消息时设置） 
    void* recv_message_handling_pcontext;//接收消息后回调函数的参数 
    void (*event_handling)(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg);//事件回调函数 在建立mqtt函数时调用 发送连接 断开 发送 接收等事件都会进行调用
    void* event_handling_pcontext;//回调函数的参数
    
    iotx_mqtt_topic_info_t mesg;//发送消息的信息控制 如服务等级 是否重发等 结构体含义看上方结构体说明
    iotx_mqtt_qos_t recv_qos;//接收消息时设置的服务等级  上面iotx_mqtt_topic_info_t结构体重的qos是发送时的服务等级

    int heartbeat_duration;//心跳持续时间
    
    Connect_status connect_status ;//连接状态  由内部函数处理 无需配置
}

```

### 函数说明

```c
Ali_Mqtt_Config_t WSM_Ali_Mqtt_Config_Create();
//Ali_Mqtt_Config结构体的创建 里面包含了一些初始化工作 使用Ali_Mqtt_Config结构体的创建结构体时应该使用该函数创建出的结构体
void WSM_Ali_Mqtt_Config_Free(Ali_Mqtt_Config_t ali_mqtt_config);
//释放Ali_Mqtt_Config结构体 
void WSM_Ali_Connect(Ali_Mqtt_Config_t ali_mqtt_config);
//进行对阿里云的连接函数 参数传递为WSM_Ali_Mqtt_Config_Create()创建后的结构体
//可选配置 heartbeat_duration 心跳持续时间（心跳时才可进行数据发送接收，心跳由内部函数进行，这里可选设置时间）
//可选配置 ali_mqtt_config结构体中的event_handling函数指针 及其参数event_handling_pcontext 用于建立连接后对事件的回调处理

int WSM_Ali_Send(Ali_Mqtt_Config_t ali_mqtt_config);
//向阿里云发送信息的函数 
//必须配置 ali_mqtt_config结构体中的结构体topic中的send_topic 用于确定发送的主题
//必须配置Ali_Mqtt_Config_t结构体中的mesg结构体 用于发送消息的信息控制 如服务等级 是否重发等

int WSM_Ali_Recv(Ali_Mqtt_Config_t ali_mqtt_config);
//必须配置 Ali_Mqtt_Config_t结构体中的结构体topic中的subscribe_topic 用于确定接收的主题
//必须配置 Ali_Mqtt_Config_t结构体中的recv_qos 用于确定接收时的服务等级
//可选配置 可选配置 ali_mqtt_config结构体中的recv_message_handling函数指针 及其参数recv_message_handling_pcontext; 用于建立连接后对事件的回调处理
```

### 使用示例

```c
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

int main(){
//1 创建Ali_Mqtt_Config_t结构体
	Ali_Mqtt_Config_t ali_mqtt_config = WSM_Ali_Mqtt_Config_Create();
//2 将创建的结构体与mqtt连接相关联 并且设置事件回调函数
    ali_mqtt_config->event_handling = event_handler;
    ali_mqtt_config->event_handling_pcontext = NULL;
	WSM_Ali_Connect(Ali_Mqtt_Config_t ali_mqtt_config);

//之后便可以使用接收或者发送功能了
    
//3.1 使用发送功能
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
	//payload为想要发送的内容
    
    ali_mqtt_config->topic.send_topic = "/*/*/*";
    ali_mqtt_config->mesg.dup = 0;
    ali_mqtt_config->mesg.packet_id = 0;
    ali_mqtt_config->mesg.payload = payload;
    ali_mqtt_config->mesg.payload_len = strlen(payload);
    ali_mqtt_config->mesg.ptopic = ali_mqtt_config->topic.send_topic;//这步可以省略 只要配置ali_mqtt_config->topic.send_topic即可
    ali_mqtt_config->mesg.qos = IOTX_MQTT_QOS0;
    ali_mqtt_config->mesg.retain = 1;
    ali_mqtt_config->mesg.topic_len = strlen(ali_mqtt_config->topic.send_topic);
    WSM_Ali_Send(ali_mqtt_config);

    
//3.2 使用接收功能
 	ali_mqtt_config->recv_message_handling = Ali_Topic_Handle;
    ali_mqtt_config->recv_message_handling_pcontext = NULL;
    ali_mqtt_config->recv_qos = IOTX_MQTT_QOS2;
    WSM_Ali_Recv( ali_mqtt_config);
    
    WSM_Ali_Mqtt_Config_Free(ali_mqtt_config);
}
```

### 注意事项

1.发送和接收都是要经过服务器来进行中转的，两者是独立的。当上报数据时，若想要接收数据方还没有设置接收服务器的消息（topic订阅），并且发送方发送时也没有配置需要服务器保留该消息（保留最新消息   ali_mqtt_config->mesg.retain = 0;这条语句），那么接收数据方将不会接收到这次数据（错过就错过了）。

当然，如果设置了保留，那么在接收方订阅topic时，服务器会发送这条保留的数据给接收方。



2.Ali_Mqtt_Config_t结构体应该一个模块创建一个，不要多个模块混用，因为可能在上报数据或接收数据时忘记修改一些配置，从而没有达到想要的效果。


独立创建，重新配置，繁琐一些但出现问题的概率会降低。
