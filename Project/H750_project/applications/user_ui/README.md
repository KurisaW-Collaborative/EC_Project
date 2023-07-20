UI依赖：

​	软件包：LittlevGL2RTT

### 函数
```
void ui_init(void);
```
初始化lvgl 必须先调用该函数 该函数调用后如果没有其他操作会默认显示主UI

#### 主UI

```
void show_main_screen();
```
显示主UI

```
void set_electric_num(int num);
```
设置电量，以百分比形式显示（直接填入数字即可 例如99 100）

```
void set_wifi_status(int flag);
```
进行设置wifi状态，flag=0为无wifi 1为有wifi
也可以使用宏  HAVE_WIFI  或  NO_HAVE_WIFI

```
void set_city(char * city_name);
```
设置城市，将城市以字符串格式传入即可

```
void set_temperature(char* num);
```
设置温度，将温度以字符串格式传入即可

```
void set_humidity(char* pressure_num);
```
设置湿度，将湿度以字符串格式传入即可

```
void set_pressure(char* pressure_num);
```
设置气压，将气压值以字符串格式传入即可



#### 报错UI

```
void show_error_screen();
```
显示报错屏幕

```
void set_error_info(char* error_message);
```
设置报错信息  参数为想要显示的字符串（如果有汉字注意使用UTF8编码文件）

#### 警告UI

```
void show_warring_screen();
```
显示警告屏幕
```
void set_warning_info(char* warning_message);
```
设置警告信息  参数为想要显示的字符串（如果有汉字注意使用UTF8编码文件）

#### 运动状态界面UI

```
void set_longitude(char * longitude_nub);//经度
void set_latitude(char * latitude_nub);//纬度
void set_exercise_status(char * exercise_status_string);//运动状态
void set_speed(char* speed_string);//速度
void set_direction(char* direction_string);//方向
void set_travel_time(char* travel_time_string);//运行时间
void set_travel_distance(char* travel_distance_string);//运行距离
```
用法同上将想要设置的字符串传入即可

#### 设置检测系统界面UI

```
void set_deteciton_temperature(char* num);//设置温度
void set_deteciton_pressure(char* pressure_num);//设置气压
void set_deteciton_humidity(char* humidity_num);//设置湿度
void set_deteciton_illumination(char* illumination);
```
用法同上将想要设置的字符串传入即可



