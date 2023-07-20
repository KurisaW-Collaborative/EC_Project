/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-16     Yifang       the first version
 */
#ifndef APPLICATIONS_AT_SERVER_USER_H_
#define APPLICATIONS_AT_SERVER_USER_H_

#include "stm32f4xx.h"

#define TCP_RX_BUFFER_SIZE 128
char tcp_rx_buffer[TCP_RX_BUFFER_SIZE];

rt_device_t esp8266_uart_dev;

void ESP8266_Init(void);
rt_err_t ESP8266_SetupAP(void);
rt_err_t ESP8266_StartServer(void);
HAL_StatusTypeDef sendATCommand_Server(const char *command, const char *expectedResponse, uint32_t timeout);
void handle_tcp_server(void *param);

void esp8266_server_thread_init(void);

#endif /* APPLICATIONS_AT_SERVER_USER_H_ */
