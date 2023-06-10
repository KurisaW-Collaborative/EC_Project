# BMP280-Sensor Driver

---

```c
目录结构：
   -EC_Project
    	|--RTT-Frame
    		|--Sensor code
    			|--bmp280_drv(Sensor)
    				|--Library
        				|--bmp280.c
        				|--bmp280.h
    				|--Example
        				|--bmp280_config.c
        				|--bmp280_cofig.c
```

文件上传遵循该目录结构，其中Library为驱动代码，Example为用户扩展API函数及测试代码

附：此驱动如果使用RT-Thread进行开发，需要依赖于*rt_vsnprintf_full* 软件包
