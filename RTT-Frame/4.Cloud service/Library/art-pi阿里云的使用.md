在使用前应先把网络连接 可以阅读文档 对于rtthread studio中art-pi项目板载wifi使用.md

之后可阅读 [(98条消息) RT-Thread Studio学习（八）利用ESP8266连接阿里云IOT_rtthread esp8266_iqiaoqiao的博客-CSDN博客](https://blog.csdn.net/iqiaoqiao/article/details/116645355) 

**直接从添加阿里云IOT软件包开始阅读即可**

接下来开始具体介绍使用方法：

#### 1.api介绍

直接阅读软件包中的文档

![image-20230510084021522](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100840599.png)

关于mqtt的部分

![image-20230510084108625](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100841675.png)

#### 2.api的使用

使用api前建议先简单了解下mqtt协议，b站上很多视频，用不了一上午就可以基本了解

##### 建立与MQTT服务器的连接

```
void *IOT_MQTT_Construct(iotx_mqtt_param_t *pInitParams)
```

结构体中的内容都会有默认配置，只需要设置不使用默认配置的即可

![image-20230510085615592](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100856621.png)

##### 发送报文

```
int IOT_MQTT_Publish(void *handle, const char *topic_name, iotx_mqtt_topic_info_pt topic_msg)
```

第一个参数：服务器连接产生的句柄

第二个参数：阿里云中topic的名字

第三个参数：发送的信息，以及发送报文的一些选择

![](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100909779.png)

这个mesg结构体的具体参数了解mqtt后就能明白参数作用

##### 订阅topic（订阅后才可以进行消息接收，订阅和接收是分开的两步）

```
int IOT_MQTT_Subscribe(void *handle,
                       const char *topic_filter,
                       iotx_mqtt_qos_t qos,
                       iotx_mqtt_event_handle_func_fpt topic_handle_func,
                       void *pcontext)
```

handle：服务器连接产生的句柄

topic_filter：阿里云中topic的名字 可支持通配符

qos:   消息服务质量等级，可以是0、1或2。具体含义可以参考MQTT协议。

topic_handle_func:	该函数指针指向一个回调函数，用于处理接收到的订阅消息。在消息到达时，将调用此函数并传递主题名称和消息内容。

pcontext:回调函数的参数

![image-20230510092749979](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100927008.png)

#### 消息接收

```
int IOT_MQTT_Yield(void *handle, int timeout_ms);
```

handle：服务器连接产生的句柄

timeout_ms:持续时间

**这个函数才是真正开始消息接收的函数，无论另一端什么时候通过topic发送消息，接收端只有在维持这个函数的时候才可以收到消息**

![image-20230510093122896](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100931938.png)

#### 3.阿里云上的物模型的使用

可以阅读[阿里云物联网平台使用教程3-定义物模型-威武网 (v5w.com)](https://www.v5w.com/iot/aliyun/329.html)进行物模型的创建

![image-20230510094049445](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100940521.png)

在产品下可以看到有一些物模型专用的Topic，使用上报topic：/sys/if15bhaF5KF/${deviceName}/thing/event/property/post。

其中deviceName为上报设备的名称

如该设备

![image-20230510094401643](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100944682.png)

那么使用的topic名称就应该为/sys/if15bhaF5KF/art-pi/thing/event/property/post。

既然知道了需要通过哪个topic上报，那么IOT_MQTT_Publish（MQTT发送报文）的topic参数就应该填写为这个。

![image-20230510094731402](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305100947440.png)

物模型对数据格式也有一定要求，需要向上图中的格式进行发送。（**这里为了更加直观使用了字符串拼接的方法 实际使用推荐使用cjson直接构建结构体生成如上字符串**）

主要要修改的内容是params中的内容。

数据采用key:val的形式：key为图中的标识符 val值为物模型中的值 注意数据类型要与物模型中相同

![image-20230510102814264](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305101028297.png)

物模型结构体类型上报格式样例

![image-20230510102944899](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305101029931.png)
