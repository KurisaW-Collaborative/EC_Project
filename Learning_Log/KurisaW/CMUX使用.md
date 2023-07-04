## 1.什么是CMUX

CMUX（Connection Multiplexing ），即连接（串口）多路复用，其功能主要在一个真实的物理通道上虚拟多个通道，每个虚拟通道上的连接和数据通讯可独立进行。

CMUX 软件包常用于蜂窝模块串口复用功能（PPP + AT 模式），以及串口硬件资源受限的设备。

## 2.CMUX特点

CMUX 软件包特点如下：

- 支持通过真实串口虚拟出多个串口；
- 支持所有基于 GSM0707/ 0710 协议的蜂窝模块；
- 支持无缝接入 PPP 功能；

## 3.CMUX架构

![image-20230626100031608](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306261000679.png)

- CMUX 是一种类似于传输层的协议，用户使用时无法感知该层；数据传输依赖一个真实串口传输，cmux 层负责解析数据用以分发到不同的 virtual uart ；从而实现一个真实串口虚拟出多个 UART 的目的
- CMUX 在应用场景中多用于 UART, 如有必要也可以支持 SPI 方式

## 4.名词解释

* CMUX：多串口协议
* DLC：数据链路连接
* DM：断开模式
* FCS：帧校验序列
* UIH：未编号的带校验头的信息
* UI：未编号的信息
* MSC：modem状态命令
* HDLC：高级数据链路控制

## 5.CMUX协议

多路复用协议提供在单个物理通信通道之上虚拟出多个并行的逻辑通信通道的能力，一般应用于TE(Terminal Equipment)与MS(Mobile Station)之间，**TE相当于智能手机的AP端，MS相当于智能手机的MODEM端。**多路复用协议的实现效果如图：

![image-20230626100512624](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306261005728.png)

蓝色部分为MUX多路复用层，它利用底层的物理串口链接收发数据，同时向上层提供若干个逻辑上独立使用的收发通道（上图中提供了四个逻辑通道，不同颜色表示）。每个逻辑通道独立创建，可以拥有软件流控制。

在实际使用中，TE端的MUX向MS端的MUX发起通道建立请求，设置通道参数等，是主动的一方；MS端的MUX等待TE端的服务请求，根据自身能力提供相应服务。也就是说，两者的角色是不对称的。

TE终端和MS终端之间的每个通道，称作一个DLC链路，它们是先后相互独立的建立起来的。其数据传输采用8BIT字符的Start-Stop的方式进行传输，双方的数据交互使用了后面定义的帧结构。

简单来说CMUX的使用流程就是：

> 1.启动CMUX服务：向模块发送AT+CMUX命令
>
> 2.建立DLC服务：建立数据链路
>
> 3.数据服务、功耗处理
>
> 4.释放DLC服务
>
> 5.关闭服务

## 6.CMUX数据结构

| Flag        | Address | Control | Length     | Information | FCS    | Flag        |
| ----------- | ------- | ------- | ---------- | ----------- | ------ | ----------- |
| 0xF9(basic) | 地址域  | 控制域  | 数据域长度 | 实际数据域  | 校验域 | 0xF9(basic) |

**地址域：**

| Bit No. | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    |
| ------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| Signal  | EA   | C/R  | DLCI | DLCI | DLCI | DLCI | DLCI | DLCI |

**控制域：**

| Frame Type                                    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 备注 |
| --------------------------------------------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| SABM (Set Asynchronous Balanced Mode)         | 1    | 1    | 1    | 1    | P/F  | 1    | 0    | 0    |      |
| UA (Unnumbered Acknowledgement)               | 1    | 1    | 0    | 0    | P/F  | 1    | 1    | 0    |      |
| DM (Disconnected Mode)                        | 1    | 1    | 1    | 1    | P/F  | 0    | 0    | 0    |      |
| DISC (Disconnect)                             | 1    | 1    | 0    | 0    | P/F  | 0    | 1    | 0    |      |
| UIH(Unnumbered Information with Header check) | 1    | 1    | 1    | 1    | P/F  | 1    | 1    | 1    |      |
| UI (Unnumbered Information)                   | 1    | 1    | 0    | 0    | P/F  | 0    | 0    | 0    | 可选 |

* SABM: SABM命令帧，异步平衡模式
* UA: UA回应帧，对SABM和DISC这两个命令帧的确认
* DM: 如果在链路断开状态，收到DISC命令，就应该发一个DM作为响应
* DISC: DISC命令用于终止通道
* UIH: UIH命令帧/响应帧，相对于 UI 帧只对地址域，控制域和长度域校验
* UI: UI命令帧/响应帧

## 7.CMUX使用

