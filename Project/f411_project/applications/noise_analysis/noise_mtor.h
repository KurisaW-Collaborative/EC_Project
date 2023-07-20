/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-08     Yifang       the first version
 */
#ifndef APPLICATIONS_NOISE_MTOR_H_
#define APPLICATIONS_NOISE_MTOR_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define LM386_PIN        GET_PIN(B,14)
#define LM386_ADC_PIN    GET_PIN(A,4)

double lm386_get_data(void);
void LM386_thread(void);

#endif /* APPLICATIONS_NOISE_MTOR_H_ */
