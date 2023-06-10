# BH1750-Sensor Driver

---

```c
目录结构：
   -EC_Project
    	|--RTT-Frame
    		|--Sensor code
    			|--bh1750_drv(Sensor)
    				|--Library
        				|--bh1750.c
        				|--bh1750.h
    				|--Example
        				|--bh1750_config.c
        				|--bh1750_cofig.c
```

文件上传遵循该目录结构，其中Library为驱动代码，Example为用户扩展API函数及测试代码

附：该文件驱动依赖宏定义：`PKG_USING_BH1750_LATEST_VERSION`，请在`rtconfig.h`文件中添加
