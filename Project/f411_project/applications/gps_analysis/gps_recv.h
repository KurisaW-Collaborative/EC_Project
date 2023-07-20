/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     Yifang       the first version
 */
#ifndef APPLICATIONS_GPS_RECV_H_
#define APPLICATIONS_GPS_RECV_H_

typedef struct _gpsINFO
{
    double  lat;        /**< Latitude in NDEG - +/-[degree][min].[sec/60] */
    double  lon;        /**< Longitude in NDEG - +/-[degree][min].[sec/60] */
}gpsINFO;

//参数为nmea库想要解析的串口名称
int nmea_thread_init(void);

void gs_data_take(char *inputdata, char *outputdata);

#endif /* APPLICATIONS_GPS_RECV_H_ */
