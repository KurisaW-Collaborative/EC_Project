/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "data_upload/data_upload.h"

/* defined the LED0 pin: PA5 */
#define LED0_PIN               GET_PIN(A, 5)

int main(void)
{
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    // sensor init
    rt_kprintf("\n");
    bmp280_drv_init();
    bh1750_drv_init();
    aht10_drv_init();

    // AT config init
#ifndef PKG_USING_AT_DEVICE
//    esp8266_server_thread_init();
//    esp8266_client_thread_init();
#else
    esp8266_device_register();
#endif

    /* start thread schedule */

    // Abnormal data monitoring task
    GP2Y_thread_start();
    rt_kprintf("Air quality monitoring mission has been enabled!\n");
    // user open it
//    LM386_thread_start();
//    rt_kprintf("City noise monitoring task has been enabled!\n");

    // voice ctrl task
    voice_thread_start();
    rt_kprintf("The voice command recognition task has been enabled!\n");

    // nmea analysis task, connect ready to use
//    gps_thread_start();

    // data upload task
//    int result = onenet_mqtt_init();
//    if(result != 0)
//    {
//        rt_kprintf("onenet_mqtt_init failed!\n");
//    }
//    onenet_set_cmd_rsp_cb(onenet_cmd_rsp_cb);
//    rt_kprintf("Upload task has been enabled!\n");

//    onenet_upload_thread_start();
//    rt_kprintf("Upload task has been enabled!\n");

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
