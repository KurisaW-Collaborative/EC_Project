/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-16     Yifang       the first version
 */
#ifndef APPLICATIONS_TCP_ACCEPT_H_
#define APPLICATIONS_TCP_ACCEPT_H_

#include "sal_socket.h"

int rt_device_tcp_accept(rt_device_t dev, struct sockaddr *addr, socklen_t *addrlen);

#endif /* APPLICATIONS_TCP_ACCEPT_H_ */
