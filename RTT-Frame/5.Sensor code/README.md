# 传感器驱动代码

---

如传感器驱动中使用到RT-Thread软件包，请复制驱动代码到Sensor组下的xxx.c及xxx.h，之后再删除相关软件包文件，避免后续用户使用时因 Git 版本对该文件出现不可用情况

```c
目录结构：
   -EC_Project
    	|--RTT-Frame
    		|--Sensor code
    			|--xxx_drv(Sensor)
    				|--Library
        				|--xxx.c
        				|--xxx.h
    				|--Example
        				|--xxx_config.c
        				|--xxx_cofig.c
```

文件上传遵循该目录结构，其中Library为驱动代码，Example为用户扩展API函数及测试代码