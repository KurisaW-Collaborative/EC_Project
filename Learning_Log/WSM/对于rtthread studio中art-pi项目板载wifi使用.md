## 想要使用板载wifi可以用两种方式

1.直接创建示例程序,在示例程序上进行接下来的编写（推荐，因为这种方式把自动连接wifi也已经配置好了）

2.手动设置开启

接下来逐一进行说明

### 1.创建示例程序

在创建项目时如下设置

![image-20230509170729375](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305092208141.png)

### 2.手动开启

![image-20230509184339491](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305092208518.png)

开启后直接进行编译即可

需要注意的是可能会出现如下错误（原因因本人水平有限，无法详细说明）

![img](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305092209362.png)

解决方法：

![image-20230509185343281](https://raw.githubusercontent.com/guapi61/PigGo_imag0/main/img0/202305091853334.png)

在这里关闭使用C基础库即可（图片可能未成功上传，在RT-Thread-settings中 内核->kservice服务优化中）

（如果有人知道关闭这个是否会影响某些功能的使用或者知道错误出现的原因和其他解决方法欢迎留言告知）