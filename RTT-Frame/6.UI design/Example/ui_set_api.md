心知天气使用教程：https://blog.csdn.net/weixin_42487906/article/details/113767644
注意 图片需要使用svg图片通过lvgl官方的转换器转为c数组

***带汉字的文件需要utf-8编码格式否则显示不了中文***
### 函数
```
void ui_init(void);
```
初始化lvgl 必须先调用该函数 该函数调用后如果没有其他操作会默认显示主UI

####主UI
```
void show_main_screen();
```
显示主UI

```
void set_electric_num(int num);
```
设置电量，以百分比形式显示（直接填入数字即可 例如99 100）

```
void set_temperature_num(int integer,int decimals);
```
设置温度，第一个参数为整数部分，第二个参数为小数部分（最好保留到小数点前一位 该函数存在缺陷没有调整 如小数部分002，会将前面的0省略 因为通常一位够用所以有时间再修复这个缺陷）

```
void set_wifi_status(int flag);
```
进行设置wifi状态，flag=0为无wifi 1为有wifi
也可以使用宏  HAVE_WIFI  或  NO_HAVE_WIFI

####报错UI
```
void show_error_screen();
```
显示报错屏幕

```
void set_error_info(char* error_message);
```
设置报错信息  参数为想要显示的字符串（如果有汉字注意使用UTF8编码文件）

####警告UI
```
void show_warring_screen();
```
显示警告屏幕
```
void set_warning_info(char* warning_message);
```
设置警告信息  参数为想要显示的字符串（如果有汉字注意使用UTF8编码文件）