/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-17     Yifang       the first version
 */
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-17     Yifang       the first version
 */
#include <rtthread.h>
#include "stm32g4xx.h"

#define ESP8266_UART_NAME "uart1"

static rt_device_t esp8266_uart_dev;

HAL_StatusTypeDef sendATCommand_Client(const char *command, const char *expectedResponse, uint32_t timeout);

void ESP8266_Client_Init(void)
{
    esp8266_uart_dev = rt_device_find(ESP8266_UART_NAME);
    if (esp8266_uart_dev == RT_NULL)
    {
        rt_kprintf("ESP8266 UART device not found!\n");
        return;
    }

    rt_device_open(esp8266_uart_dev, RT_DEVICE_FLAG_RDWR);
}

rt_err_t ESP8266_ConnectToServer(const char *ip, uint16_t port)
{
    char command[64];
    rt_snprintf(command, sizeof(command), "AT+CIPSTART=0,\"TCP\",\"%s\",%u\r\n", ip, port);

    // Send AT command to establish the TCP connection
    if (sendATCommand_Client(command, "CONNECT", 5000) != HAL_OK)
    {
        rt_kprintf("ESP8266 failed to connect to server!\n");
        return RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t ESP8266_SendData(const char *data)
{
    char command[64];
    rt_snprintf(command, sizeof(command), "AT+CIPSEND=0,%u\r\n", rt_strlen(data));

    // Send AT command to start data transmission
    if (sendATCommand_Client(command, ">", 3000) != HAL_OK)
    {
        rt_kprintf("ESP8266 failed to send data (data transmission not started)!\n");
        return RT_ERROR;
    }

    // Send the actual data
    rt_device_write(esp8266_uart_dev, 0, data, rt_strlen(data));

    // Wait for "SEND OK" response
    if (sendATCommand_Client("", "SEND OK", 5000) != HAL_OK)
    {
        rt_kprintf("ESP8266 failed to send data!\n");
        return RT_ERROR;
    }

    return RT_EOK;
}

HAL_StatusTypeDef sendATCommand_Client(const char *command, const char *expectedResponse, uint32_t timeout)
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
        rt_kprintf("No response received for command: %s\n", command);
        return HAL_TIMEOUT;
    }
}

void client_entry(void)
{
    rt_err_t err = -RT_ERROR;

    if (sendATCommand_Client("AT+CWMODE=1\r\n", "OK", 3000) != HAL_OK)
    {
        rt_kprintf("Failed to set Station mode!\n");
        return;
    }
    else
    {
        rt_kprintf("Set WiFi mode to Station mode!\n");
    }

//    if (sendATCommand_Client("AT+RST\r\n", "OK", 3000) != HAL_OK)
//    {
//        rt_kprintf("Failed to set Station mode!\n");
//        return;
//    }
//    else
//    {
//        rt_kprintf("Set at model restart!\n");
//    }

    rt_thread_mdelay(3000);

    // 此处修改为F4的ESP模块AP模式下的热点信息
    if (sendATCommand_Client("AT+CWJAP=\"ESP8266\",\"jetbotwyq\"\r\n", "OK", 10000) != HAL_OK)
    {
        rt_kprintf("Failed to connect to the WiFi network!\n");
        return;
    }
    else
    {
        rt_kprintf("Connect to the WiFi network!\n");
    }

    if (sendATCommand_Client("AT+CIPMUX=0\r\n", "OK", 3000) != HAL_OK)
    {
        rt_kprintf("Failed to Open single connection!\n");
        return;
    }
    else
    {
        rt_kprintf("Open single connection!\n");
    }

    // 此处改为F4的ESP模块AP模式下的IP，并对端口8086进行监听
    if (sendATCommand_Client("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080\r\n", "CONNECT", 5000) != HAL_OK)
    {
        rt_kprintf("Failed to connect to the TCP server!\n");
        return;
    }
    else
    {
        rt_kprintf("Connect to the TCP server!\n");
    }

    if (sendATCommand_Client("AT+CIPMODE=0\r\n", "OK", 3000) != HAL_OK)
    {
        rt_kprintf("Failed to set CIPMODE!\n");
        return;
    }
    else
    {
        rt_kprintf("Set CIPMODE to 0 (normal mode)!\n");
    }


    if (sendATCommand_Client("AT+CIPSEND=7\r\n", ">", 3000) != HAL_OK)
    {
        rt_kprintf("Failed to enter data sending mode!\n");
        return;
    }
    else
    {
        rt_kprintf("Enter data sending mode!\n");
    }

    const char *weather_msg = "posture";

    if (sendATCommand_Client("posture", "SEND OK", 5000) != HAL_OK)
    {
        rt_device_write(esp8266_uart_dev, 0, weather_msg, rt_strlen(weather_msg));
        rt_kprintf("Failed to send posture_msg!\n");

        return;
    }
    else
    {
        rt_kprintf("Exit data sending mode!\n");
    }

    rt_kprintf("Data sent successfully!\n");
}

void esp8266_client_thread_init(void)
{
    ESP8266_Client_Init();
    rt_thread_t client_thread = rt_thread_create("client", client_entry, RT_NULL, 2048, 20, 10);
    if (client_thread != RT_NULL)
    {
        rt_thread_startup(client_thread);
    }
}
//INIT_APP_EXPORT(esp8266_client_thread_init);
MSH_CMD_EXPORT(esp8266_client_thread_init,esp8266_client_thread_init);
