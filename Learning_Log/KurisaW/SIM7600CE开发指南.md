## 开发板信息

![image-20230623093900480](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306230939807.png)

![image-20230623093922796](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306230939991.png)



UNV-SIM7600CE开发板含有三组天线接口，分别是4G天线接口（丝印标注main ant），3G天线接口（丝印标注aux ant），GPS有源天线接口（丝印标注GNS ant）。

## RT-Thread SIM76xx设备初始化失败解决办法

参考：[求助：SIM7600ce设备初始化失败](https://club.rt-thread.org/ask/question/4cdcb056b4b4dc1b.html)

总结解决办法就是：

1.确保网络信号质量。之前信号强度在16和21的时候没有注册网络成功，可能不同厂商的4G模块强度要求不一，尽量找一个信号好的地方。

2.确保能在windows上使用AT命令能够有效反馈。这部分是前提，需要在windows上使用USB连接电脑然后通过端口结合串口工具能正确收发AT指令（注意事项：在设备管理器需要找到对应的4G端口，有些4G模块会集成GPS，同时需要正确的安装驱动，这块商家会提供的）

3.4G模块一般会有个初始化过程，需要等待其注册网络后再进行AT指令的操作，一般看板载的提示灯会有所说明

![image-20230624102833097](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306241028479.png)

## 常用的AT指令集

* 查询注册情况：

![image-20230625120255573](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306251202990.png)

* 查询网络情况

![image-20230625120443947](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306251204001.png)

* 获取基站号

![image-20230625121538469](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306251215526.png)

* 修改串口波特率

![image-20230625121644324](https://cdn.jsdelivr.net/gh/kurisaW/picbed/img2023/202306251216372.png)

* 基站定位

## TCP透传模式流程

### 1.信号查询

```c
AT+CSQ
```

* AT：指示这是一条AT指令。
* +CSQ：指示这是关于信号质量的参数。
* AT+CSQ指令用于查询设备当前的信号质量。设备将返回一个响应，提供信号强度和误码率等信息。通常，信号强度以RSSI（Received Signal Strength Indication）表示，误码率以BER（Bit Error Rate）表示。

```c
AT+CREG?
```

* AT：指示这是一条AT指令。
* +CREG: 指示这是关于网络注册的参数。
* ?: 用于查询参数的当前值。
* AT+CREG?指令用于查询设备当前的网络注册状态。设备将返回一个响应，提供关于注册状态的信息，例如已注册、未注册、正在搜索等。

```c
AT+CPSI?
```

* AT：指示这是一条AT指令。
* +CPSI：指示这是关于当前服务的参数。
* ?: 用于查询参数的当前值。
* AT+CPSI?指令用于查询设备当前连接的无线服务信息。设备将返回一个响应，提供有关当前服务的详细信息，如运营商名称、网络类型（GSM、LTE等）、频段等。

```c
AT+CGREG?
```

* AT：指示这是一条AT指令。
* +CGREG: 指示这是关于GPRS网络注册的参数。
* ?: 用于查询参数的当前值。
* AT+CGREG?指令用于查询设备当前的GPRS网络注册状态。设备将返回一个响应，提供关于注册状态的信息，如已注册、未注册、正在搜索等。

### 2.设置APN

```c
AT+CGSOCKCONT=1,"IP","CMNET"
```

* AT：指示这是一条AT指令。
* +CGSOCKCONT：指示这是关于套接字上下文的参数。
* =1：指定套接字上下文的索引为1，表示配置第一个套接字上下文。
* "IP"：指定套接字上下文的PDP类型为IP，表示使用IP数据传输。
* "CMNET"：指定套接字上下文的APN（接入点名称）为CMNET，表示连接到CMNET网络。
  AT+CGSOCKCONT=1,"IP","CMNET"指令的含义是配置第一个套接字上下文，使用IP数据传输，并连接到CMNET网络。

```c
AT+CSOCKSETPN=1
```

* AT：指示这是一条AT指令。
* +CSOCKSETPN：指示这是关于套接字设置的参数。
* =1：指定要设置的套接字索引为1，表示设置第一个套接字的参数。
* AT+CSOCKSETPN=1指令的含义是设置第一个套接字的参数。

```c
AT+CIPMODE=0
```

* AT：指示这是一条AT指令。
* +CIPMODE：指示这是关于IP传输模式的参数。
* =0：指定IP传输模式为0，表示禁用透明传输模式。
* AT+CIPMODE=0指令的含义是禁用设备的透明传输模式，使其不能将数据直接透明传输。

```c
AT+NETOPEN
```

* AT：指示这是一条AT指令。
* +NETOPEN：指示这是关于网络打开的参数。
* AT+NETOPEN指令的含义是打开设备的网络连接，使其能够开始进行网络通信。

```c
AT+IPADDR
```

* AT：指示这是一条AT指令。
* +IPADDR：指示这是关于IP地址的参数。
* AT+IPADDR指令的含义是查询设备的IP地址，设备将返回一个响应，提供当前的IP地址信息。

### 3. TCP Client

AT+CIPOPEN=0,"TCP","116.236.221.75",8011

AT+CIPSEND=0,5
