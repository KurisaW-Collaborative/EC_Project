/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-08     Yifang       the first version
 */
#include <rtthread.h>
#include <stdio.h>
#include <math.h>
#include "filter.h"

// 初始化低通滤波器
void LowPassFilter_Init(LowPassFilter* filter, float alpha, float initial_output)
{
    filter->alpha = alpha;
    filter->prev_output = initial_output;
}

// 应用低通滤波器
float LowPassFilter_Apply(LowPassFilter* filter, float input)
{
    float output = (1 - filter->alpha) * filter->prev_output + filter->alpha * input;
    filter->prev_output = output;
    return output;
}

double calculateMean(double data[], int n) {
    double sum = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        sum += data[i];
    }

    return sum / n;
}

double calculateStandardDeviation(double data[], int n) {
    double mean = calculateMean(data, n);
    double sum = 0.0;
    int i;

    for (i = 0; i < n; i++) {
        sum += pow(data[i] - mean, 2);
    }

    return sqrt(sum / n);
}

double calculateCoefficientOfVariation(double data[], int n) {
    double mean = calculateMean(data, n);
    double standardDeviation = calculateStandardDeviation(data, n);

    return (standardDeviation / mean) * 100.0;
}

float LowPassFilter_Sample(double data[], int size)
{
    // 创建一个低通滤波器
    LowPassFilter filter;
    float input, output;

    // 初始化低通滤波器
    LowPassFilter_Init(&filter, 0.1, 0.0);

    // 应用低通滤波器并打印输出结果
    int i;
    for (i = 0; i < size; i++) {
        input = data[i];
        output = LowPassFilter_Apply(&filter, input);
        rt_kprintf("Input: %.2f, Output: %.2f\n", input, output);
    }

    return output;
}
//MSH_CMD_EXPORT(LowPassFilter_Sample,LowPassFilter_Sample);

// coefficient of variation:离散系数
double cov_filter(double data[], int size)
{
    double coefficientOfVariation = calculateCoefficientOfVariation(data, size);

//    rt_kprintf("Coefficient of Variation: %.2f%%\n", coefficientOfVariation);

    return coefficientOfVariation;
}
//MSH_CMD_EXPORT(cov_filter,cov_filter);
