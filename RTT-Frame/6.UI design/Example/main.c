/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

#include "ali_user_api/user_api.h"
#include "ui.h"

#define LED_PIN GET_PIN(I, 8)

extern void wlan_autoconnect_init(void);


int main(void)
{
    rt_err_t result;
        /* 初始化事件对象 */
        result = rt_event_init(&wifi_event, "wifi_event", RT_IPC_FLAG_PRIO);
        if (result != RT_EOK)
        {
            rt_kprintf("init event failed.\n");
            return -1;
        }
    rt_uint32_t count = 1;
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    /* init Wi-Fi auto connect feature */
    wlan_autoconnect_init();
    /* enable auto reconnect on WLAN device */
    rt_wlan_config_autoreconnect(RT_TRUE);

    ui_init();

  //  set_warning_info("错误");
   // set_error_info("警告");
    while(count++)
    {
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);


        //rt_thread_mdelay(5000);
       // show_error_screen();
        //rt_thread_mdelay(5000);
        //show_warning_screen();
    }
    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);
