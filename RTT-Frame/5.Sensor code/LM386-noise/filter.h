/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-08     Yifang       the first version
 */
#ifndef APPLICATIONS_FILTER_H_
#define APPLICATIONS_FILTER_H_


// 定义低通滤波器结构体
typedef struct {
    float alpha;  // 滤波器的衰减系数
    float prev_output;  // 上一个输出值
} LowPassFilter;

#define SAMPLE_RATE 48000    // 采样率
#define CUTOFF_FREQ 1000     // 截止频率

float LowPassFilter_Sample(double data[], int size);
double cov_filter(double data[], int size);

#endif /* APPLICATIONS_FILTER_H_ */
