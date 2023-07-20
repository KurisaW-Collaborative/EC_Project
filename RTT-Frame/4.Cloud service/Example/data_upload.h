/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     Yifang       the first version
 */
#ifndef APPLICATIONS_DATA_UPLOAD_H_

#define APPLICATIONS_DATA_UPLOAD_H_

#include "bh1750_config.h"
#include "../bmp280_lib/bmp280_read.h"

#include "aht10_lib/aht10_read.h"

struct AHT10_DATA   aht10_upload_struct;

extern rt_mutex_t user_gps_mutex;
extern char gps_upload_data[128];

// 定义云端命令下发标志
#define ACQUISITION_START "Acquisition task start"
#define ACQUISITION_END "Acquisition task end"

void weather_task_startup(void);
void weather_task_suspend(void);

void onenet_upload(void);

void onenet_cmd_rsp_cb(uint8_t *recv_data, size_t recv_size,uint8_t **resp_data,size_t *resp_size);

#endif /* APPLICATIONS_DATA_UPLOAD_H_ */
