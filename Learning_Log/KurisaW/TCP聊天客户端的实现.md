# TCP聊天客户端的实现

---

## 基础知识

#### 1.TCP与UDP的区别

TCP(Transmission Control Protocol 传输控制协议)：是一种面向连接、可靠的、基于字节流的传输层通信协议，由IETF的RFC 793定义。

UDP(User Datagram Protocol 用户数据报协议)：是OSI(Open System Interconnection 开放式系统互联)：参考模型中的一种无连接的传输层协议，提供面向事务的简单不可靠传送服务。

OSI七层模型和TCP/IP四层模型详解请看[此处](https://kurisaw.github.io/p/%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8Bosi%E4%B8%83%E5%B1%82%E6%A8%A1%E5%9E%8Btcpip%E5%9B%9B%E5%B1%82%E6%A8%A1%E5%9E%8B/)

区别：

* TCP提供的是面向连接、可靠的数据流传输；UDP提供的是非面向连接、不可靠的数据流传输。
* TCP提供可靠的服务，通过TCP连接传送的数据：无差错、不丢失、不重复、按序到达；UDP尽最大努力交付，但不保证可靠性。
* TCP面向字节流；UDP面向报文。
* TCP仅支持点对点连接；UDP支持一对一、一对多、多对多的交互通信。
* TCP最低开销20字节（首部开销）；UDP首部开销8字节，开销小。
* TCP的逻辑同i性能信道是全双工的可靠信道；UDP的逻辑通信信道是不可靠信道。

#### 2.TCP编程 服务端配置过程

* `socket():`创建一个socket
* `setsockopt():`设置socket属性
* `bind():`绑定IP地址、端口等信息到socket类上
* `listen():`开启监听
* `accept():`接收来自客户端的连接
* 收发数据：`send()、recv()、read()、write()`
* 关闭网络连接
* 关闭监听

#### 3.TCP编程 客户端配置过程

* `socket():`创建一个socket
* `setsockopt():`设置socket属性，可选
* `bind():`绑定IP地址、端口等信息到socket上
* `recvfrom():`循环接收数据
* 关闭网络连接

#### 4.UDP编程 客户端配置过程

* `socket():`创建一个socket
* `setsockopt():`设置socket属性，可选
* `bind():`绑定IP地址、端口等信息到socket上
* 设置对方的IP地址和端口等属性
* `sendto():`发送数据
* 关闭网络连接

## API函数

#### 1.创建一个socket

为通信创建一个端点并返回一个文件描述符

```c
int socket(int domain, int type, int protocol);
```

* domain：确定协议簇
* type：数据类型
* protocol：协议

```c
AF_INET		#  IPv4 协议族
AF_INET6	#  IPv6 协议族
```

```c
/* Socket protocol types (1:TCP/2:UDP/3:RAW) */
#define SOCK_STREAM     1
#define SOCK_DGRAM      2
#define SOCK_RAW        3
```

```c
```



#### 2.给套接字分配一个地址

当使用socket()创造一个套接字时，只是给定了协议簇，并没有分配地址。在套接字能够接收来自其他主机的连接时，必须bind()给它绑定一个地址。

```c
int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
```

* sockfd：代表socket的文件描述符
* my_addr：指向sockaddr结构体的指针，代表要绑定的地址
* addrlen：是sockaddr结构体的大小

#### 3.监听连接

当有一个套接字和一个地址联系之后，listen()监听到来的连接。只适用于面向连接的模式。

```c
int listen(int sockfd, int backlog);
```

* sockfd：代表socket的文件描述符
* backlog：一个整数，表示一次能够等待的最大连接数目。

#### 4.接收连接

当应用程序监听来自其他他主机的面向数据流的连接时，通过事件通知它，必须用accept()函数初始化连接。该函数为每个来凝结创建新的套接字并从监听队列中移除这个连接。

```c
int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
```

* sockfd：监听的套接字描述符
* serv_addr：指向sockaddr结构体的指针，服务器地址信息
* addrlen：sockaddr结构体的大小

## LWIP结构体

#### 1.struct sockaddr_in

```c
#if NETDEV_IPV4
/* members are in network byte order */
struct sockaddr_in
{
    uint8_t        sin_len;
    sa_family_t    sin_family;
    in_port_t      sin_port;
    struct in_addr sin_addr;
#define SIN_ZERO_LEN 8
    char            sin_zero[SIN_ZERO_LEN];
};
#endif /* NETDEV_IPV4 */

#if NETDEV_IPV6
struct sockaddr_in6
{
  uint8_t         sin6_len;      /* length of this structure    */
  sa_family_t     sin6_family;   /* AF_INET6                    */
  in_port_t       sin6_port;     /* Transport layer port #      */
  uint32_t        sin6_flowinfo; /* IPv6 flow information       */
  struct in6_addr sin6_addr;     /* IPv6 address                */
  uint32_t        sin6_scope_id; /* Set of interfaces for scope */
};
#endif /* NETDEV_IPV6 */
```

