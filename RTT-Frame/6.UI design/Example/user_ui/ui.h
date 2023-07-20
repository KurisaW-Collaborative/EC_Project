/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-13     閿熸枻鎷烽敓鎺ョ鎷风毊       the first version
 */
#ifndef APPLICATIONS_USER_UI_UI_H_
#define APPLICATIONS_USER_UI_UI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "littlevgl2rtt.h"
#include "drv_spi_ili9488.h"
#include "lvgl.h"
#include "rtdef.h"
//#include <webclient.h>
//#include "ntp.h"
#include <cJSON.h>
#include <time.h>


#include "data_communication/data_communication.h"

#define EVENT_FLAG3 (1 << 3)


#define BAD_ENVIRONMENT_START 0x1
#define BAD_ENVIRONMENT_END 0x2
#define ABNORMAL_ATTITUDE_START 0x3
#define ABNORMAL_ATTITUDE_END 0x4
#define FIRE_HAZARD_START 0x5
#define FIRE_HAZARD_END 0x6
#define LOW_BATTERY_START 0x7
#define LOW_BATTERY_END 0x8

extern struct rt_event wifi_event;//閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹ui閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熼樁鍒猴拷  閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸彮顏庢嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸帴纰夋嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鎺ョ尨鎷烽敓鏂ゆ嫹閿熸枻鎷蜂綅閿熸枻鎷� 閿熸枻鎷烽敓鏂ゆ嫹ui閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷峰綍閿熸枻鎷烽敓鏂ゆ嫹閿熺醇VENT_FLAG3

lv_disp_t *dispp;

struct now_show_ui{
    lv_obj_t* screen;
    lv_obj_t *github;
    lv_obj_t *time_sketchy;
    lv_obj_t *time_minute;
}now_show_ui;//閿熸枻鎷烽敓鏂ゆ嫹鎵ч敓鍙鎷烽敓绲琲閿熸枻鎷峰悓閿熸枻鎷疯refresh_thread_entry鍒烽敓鏂ゆ嫹閿熸枻鎷风ず閿熸枻鎷风洰閿熸枻鎷�

enum wifi_status{
  NO_HAVE_WIFI = 0,
  HAVE_WIFI ,
};

//閿熸枻鎷峰閿熸枻鎷峰叏閿熸枻鎷稶I閿熸枻鎷烽敓鏂ゆ嫹
void ui_init(void);

//閿熸枻鎷风ず閿熸枻鎷峰悓UI閿熸枻鎷烽敓鏂ゆ嫹
void show_error_ui();
void show_warning_ui();
void show_main_ui();
void show_start_ui();
void show_kinestate_ui();
void show_deteciton_ui();

/********閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷稶I start********/
void set_electric_num(int num);
void set_wifi_status(int flag);
void set_time(int hour,int points,int seconds,int wday);

void set_city(char * city_name);
void set_temperature(char* num);
void set_humidity(char* pressure_num);
void set_pressure(char* pressure_num);
/********閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷稶I end********/

/********閿熸枻鎷烽敓鐭揪鎷烽敓鏂ゆ嫹閫旈敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹UI start********/
void set_error_info(char* error_message);
void set_warning_info(char* warning_message);
/********閿熸枻鎷烽敓鐭揪鎷烽敓鏂ゆ嫹閫旈敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹UI end********/

/********閿熸枻鎷烽敓鏂ゆ嫹閿熷壙璁规嫹鐘舵�侀敓鏂ゆ嫹閿熸枻鎷稶I start********/
void set_longitude(char * longitude_nub);
void set_latitude(char * latitude_nub);
void set_exercise_status(char * exercise_status_string);
void set_speed(char* speed_string);
void set_direction(char* direction_string);
void set_travel_time(char* travel_time_string);
void set_travel_distance(char* travel_distance_string);
/********閿熸枻鎷烽敓鏂ゆ嫹閿熷壙璁规嫹鐘舵�侀敓鏂ゆ嫹閿熸枻鎷稶I end********/

/********閿熸枻鎷烽敓鐭》鎷烽敓杈冧綆绛规嫹閿熸枻鎷烽敓绲孖 start********/
void set_deteciton_temperature(char* num);
void set_deteciton_pressure(char* pressure_num);
void set_deteciton_humidity(char* humidity_num);
void set_deteciton_illumination(char* illumination);
/********閿熸枻鎷烽敓鐭》鎷烽敓杈冧綆绛规嫹閿熸枻鎷烽敓绲孖 start********/

/********閿熸枻鎷烽敓鐭》鎷烽敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹鏂愶綇鎷烽敓鏂ゆ嫹閿熺祵I start********/
void show_deteciton_abnormal_ui();
void set_deteciton_abnormal_temperature(char* num);//鍚岄敓鏂ゆ嫹閿熺煫鍑ゆ嫹 鐘舵�佸�间负0涓洪敓灞婂父鐘舵�侀敓鏂ゆ嫹閿熸枻鎷烽敓鏂ゆ嫹宀滀紮鎷烽敓缂搭偓鎷烽敓锟� 鐘舵�佸�间负1浣嶉敓鏂ゆ嫹閿熸枻鎷风姸鎬�
void set_deteciton_abnormal_pressure(char* pressure_num);
void set_deteciton_abnormal_humidity(char* humidity_num);
void set_deteciton_abnormal_illumination(char* illumination_stringint);
/********閿熸枻鎷烽敓鐭》鎷烽敓杈冧綆绛规嫹閿熸枻鎷烽敓绲孖 start********/

//鐟欙箑褰俇I
void ui_tigger_start();
void ui_tigger_end();

void close_lvgl_show();


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* APPLICATIONS_USER_UI_UI_H_ */
