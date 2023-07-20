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


// �����ͨ�˲����ṹ��
typedef struct {
    float alpha;  // �˲�����˥��ϵ��
    float prev_output;  // ��һ�����ֵ
} LowPassFilter;

#define SAMPLE_RATE 48000    // ������
#define CUTOFF_FREQ 1000     // ��ֹƵ��

float LowPassFilter_Sample(double data[], int size);
double cov_filter(double data[], int size);

#endif /* APPLICATIONS_FILTER_H_ */
