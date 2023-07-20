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
#include "tcp_accept.h"

// Define the structure to store TCP connections
#define MAX_TCP_CONNECTIONS 5
struct tcp_connection
{
    int conn_id;
    int connected;
};
static struct tcp_connection tcp_connections[MAX_TCP_CONNECTIONS];

// Function to initialize the TCP connections
static void init_tcp_connections(void)
{
    for (int i = 0; i < MAX_TCP_CONNECTIONS; i++)
    {
        tcp_connections[i].conn_id = -1;
        tcp_connections[i].connected = 0;
    }
}

// Function to find an available TCP connection slot
static int find_available_connection(void)
{
    for (int i = 0; i < MAX_TCP_CONNECTIONS; i++)
    {
        if (!tcp_connections[i].connected)
        {
            return i;
        }
    }
    return -1; // No available slots
}

// Custom rt_device_tcp_accept function
int rt_device_tcp_accept(rt_device_t dev, struct sockaddr *addr, socklen_t *addrlen)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->type == RT_Device_Class_Char);

    int conn_id = find_available_connection();
    if (conn_id < 0)
    {
//        rt_kprintf("No available TCP connection slot!\n");
        return -RT_EFULL;
    }

    int new_conn = -1;
    for (int i = 0; i < MAX_TCP_CONNECTIONS; i++)
    {
        if (!tcp_connections[i].connected)
        {
            new_conn = i;
            break;
        }
    }

    if (new_conn > 0)
    {
        tcp_connections[new_conn].connected = 1;
        tcp_connections[new_conn].conn_id = new_conn;
        return new_conn; // Return the connection ID
    }
    else
    {
        return -RT_ERROR;
    }
}
