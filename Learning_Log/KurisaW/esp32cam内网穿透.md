## 参考教程

* [使用一键安装工具快速搭建 ESP-IDF 开发环境 (Windows)](https://zhuanlan.zhihu.com/p/636993133)

## 注意事项

* esp-idf：ESP-IDF v4.4.4-dirty
* esp-who：idf v3.3.1
* 例程：examples\single_chip\camera_web_server

## 配置项

* Step1：`(Top) → Camera Web Server → WiFi Settings`

![image-20230704093529846](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202307040935302.png)

此处注意需要将`ESP-WHO Face Detection`功能关闭，在esp-who v3.3.1分支的例程估计应该对esp-idf版本有所要求，至少idf v4.4.4不可以，路径：`(Top) → Camera Web Server`

* Step2：修改http server的length，不然会运行过程报错，需要加大Length，路径：`(Top) → Component config → HTTP Server`

![image-20230704093813578](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202307040938656.png)

* Step3：在我们本次使用的例程：camera_web_server中会用到`rtc_gpio_desc`相关的配置，需要我们在menuconfig中使能，路径：`(Top) → Component config → Driver configurations → RTCIO configuration`

![image-20230704094052597](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202307040940682.png)

## 烧录

ESP-CAM的IO0引脚与GND短接，然后按一下RST键，同时使用USB转TTL工具进行连接，注意需要连接5V供电,

## 命令

```
idf.py menuconfig

idf.py build

idf.py -p COM20 flash

idf.py -p COM20 monitor
```

## 报错

### 1.error: 'rtc_gpio_desc' undeclared

![image-20230702114023474](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202307021140053.png)

解决：

```c
idf.py menuconfig

(Top) → Component config → Driver configurations → RTCIO configuration

[*] Support array `rtc_gpio_desc` for ESP32
```

## 内网穿透

* stream流无法访问问题解决：在指定端口号后面加上后缀'/stream'即可，[参考文章](https://www.arduino.cn/thread-104188-1-1.html)
* 内网穿透平台：[StarryFrp](https://frp.starryfrp.com/console/index)

## 访问端口

首先需要在一台主机中启用frpc服务，配置文件frpc.ini需要提前配置好，参考官网

这是我的frpc.ini配置，可供参考

![image-20230704094421172](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202307040944258.png)

根据下图提示启用frpc服务

![image-20230704094250465](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202307040942557.png)

访问ip

```c
http://cn-cd-txy-1.starryfrp.com:28168/stream
```

