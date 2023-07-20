/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-16     Yifang       the first version
 */
#include <rtthread.h>
#include "at_server_user.h"
#include "tcp_accept.h"

#define ESP8266_UART_NAME "uart6"

void ESP8266_Init(void)
{
    esp8266_uart_dev = rt_device_find(ESP8266_UART_NAME);
    if (esp8266_uart_dev == RT_NULL)
    {
        rt_kprintf("ESP8266 UART device not found!\n");
        return;
    }

    rt_device_open(esp8266_uart_dev, RT_DEVICE_FLAG_RDWR);
}

rt_err_t ESP8266_SetupAP(void) {
    // 发送AT指令设置为AP模式，并配置WiFi名称和密码
    if (sendATCommand("AT+CWMODE=2\r\n", "OK", 3000) != HAL_OK)
    {
        rt_kprintf("ESP8266 set AP mode failed!\n");
        return;
    }

    if (sendATCommand("AT+RST\r\n", "OK", 3000) != HAL_OK)
    {
        rt_kprintf("Failed to set Station mode!\n");
        return;
    }

    rt_thread_mdelay(5000);

    char command[128];
    sprintf(command, "AT+CWSAP=\"ESP8266\",\"jetbotwyq\",1,3\r\n");
    if (sendATCommand(command, "OK", 3000) != HAL_OK)
    {
        rt_kprintf("ESP8266 setup AP parameters failed!\n");
        return;
    }

    // 延时等待设置完成
    rt_thread_mdelay(1000);

    return RT_EOK;
}

rt_err_t ESP8266_StartServer(void)
{
    // 启动TCP Server，并设置端口号为8080
    if (sendATCommand("AT+CIPMUX=1\r\n", "OK", 3000) != HAL_OK)
    {
        rt_kprintf("ESP8266 set CIPMUX failed!\n");
        return;
    }

    rt_thread_mdelay(1000);

    char command[64];
    sprintf(command, "AT+CIPSERVER=1,8080\r\n");
    if (sendATCommand(command, "OK", 3000) != HAL_OK)
    {
        rt_kprintf("ESP8266 start server failed!\n");
        return;
    }

    if (sendATCommand("AT+CIFSR\r\n", "OK", 3000) != HAL_OK)
    {
        rt_kprintf("ESP8266 take server IP failed!\n");
        return;
    }

    // 设置超时时间为1200s
    if (sendATCommand("AT+CIPSTO=1200\r\n", "OK", 3000) != HAL_OK)
    {
        rt_kprintf("Failed to set the timeout period. !\n");
        return;
    }

    // 延时等待设置完成
    rt_thread_mdelay(1000);

    rt_thread_t tcp_server_thread = rt_thread_create("tcp_server", handle_tcp_server, esp8266_uart_dev, 4096, 20, 10);
    if (tcp_server_thread != RT_NULL)
    {
        rt_thread_startup(tcp_server_thread);
        rt_kprintf("TCP server thread started!\n");
    }
    else
    {
        rt_kprintf("Failed to create TCP server thread!\n");
        return RT_ERROR;
    }

    return RT_EOK;
}

HAL_StatusTypeDef sendATCommand(const char *command, const char *expectedResponse, uint32_t timeout)
{
    HAL_StatusTypeDef status;
    char buffer[256];
    uint32_t tickstart = rt_tick_get();
    uint32_t buffer_idx = 0;
    int response_received = 0;

    memset(buffer, 0, sizeof(buffer));

    // Send AT command
    rt_device_write(esp8266_uart_dev, 0, command, strlen(command));

    // Wait for response
    do
    {
        if (rt_device_read(esp8266_uart_dev, 0, buffer + buffer_idx, 1) == 1)
        {
            buffer_idx++;
        }

        // Check if the expected response is received
        if (strstr(buffer, expectedResponse) != RT_NULL)
        {
            response_received = 1;
            break;
        }

    } while ((rt_tick_get() - tickstart) < timeout);

    if (response_received)
    {
        // Print the received response
        rt_kprintf("Received response for command: %s\nResponse: %s\n", command, buffer);
        return HAL_OK;
    }
    else
    {
        // Response not received within the timeout
//        rt_kprintf("No response received for command: %s\n", command);
        return HAL_TIMEOUT;
    }
}


/***********************************************/

void handle_tcp_data(int conn, const char *data, int data_len)
{
    // Process received data here (you can add your custom handling logic)
    rt_kprintf("Received TCP data (Connection %d %d): %s\n", conn, data_len, data);
}

// TCP server
// TCP server
void handle_tcp_server(void *param)
{
    rt_device_t dev = (rt_device_t)param;
    uint8_t buffer[256];
    int conn_id = -1;

    while (1)
    {
        if (sendATCommand("", "+IPD,0,7:posture", 3000) == HAL_OK)
        {
            rt_kprintf("received the posture data!\n");
        }
//        else if(sendATCommand("", "+IPD,0,24:posture from the client!", 3000) == HAL_OK)
//        {
//            rt_kprintf("received the data!\n");
//        }
        else
        {
//            rt_kprintf("error to receive the data!\n");
        }
    }
}

/***********************************************/

void at_server_entry(void)
{
    rt_err_t err = -RT_ERROR;
    err = ESP8266_SetupAP();
    if(err == RT_EOK)
    {
        err = -RT_ERROR;
        err = ESP8266_StartServer();
        if(err == RT_EOK)
        {
            rt_kprintf("ESP8266_StartServer successful!\n");
        }
        else
        {
            rt_kprintf("ESP8266_StartServer failed!\n");
        }
    }
    else
    {
        rt_kprintf("ESP8266_SetupAP failed!\n");
    }
}

static void esp8266_init(void)
{
    rt_thread_t atserver_thread= rt_thread_create("esp8266_init", at_server_entry, RT_NULL, 8196, 21, 1000);
    rt_thread_startup(atserver_thread);
    ESP8266_Init();
}
INIT_APP_EXPORT(esp8266_init);
//MSH_CMD_EXPORT(esp8266_init,esp8266_init);

