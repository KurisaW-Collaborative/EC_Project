/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-22     Yifang       the first version
 */
#ifndef APPLICATIONS_MPU9250_LIB_MPU9250_DRV_H_
#define APPLICATIONS_MPU9250_LIB_MPU9250_DRV_H_

#include "board.h"

//�ڶ�ȡʱ��ע����Ҫ�˹�����ַ����1λ��I2C��дΪ����룬��8λҪ���д��־λ��
#define MPU9250_ADDRESS 0xD0   //AD0��GNDʱ��ַΪ0x68����VCCʱ��ַΪ0x69
#define MPU_PWR_MGMT1_REG       0X6B    //��Դ����Ĵ���1
#define MPU_GYRO_CFG_REG        0X1B    //���������üĴ���
#define MPU_ACCEL_CFG_REG       0X1C    //���ٶȼ����üĴ���
#define MPU_SAMPLE_RATE_REG     0X19    //�����ǲ���Ƶ�ʷ�Ƶ��
#define MPU_INT_EN_REG          0X38    //�ж�ʹ�ܼĴ���
#define MPU_USER_CTRL_REG       0X6A    //�û����ƼĴ���
#define MPU_FIFO_EN_REG         0X23    //FIFOʹ�ܼĴ���
#define MPU_INTBP_CFG_REG       0X37    //�ж�/��·���üĴ���
#define MPU_DEVICE_ID_REG       0X75    //����ID�Ĵ���
#define MPU_PWR_MGMT2_REG       0X6C    //��Դ����Ĵ���2
#define MPU_CFG_REG             0X1A    //���üĴ��� ��ͨ�˲������üĴ���

#define MPU_TEMP_OUTH_REG       0X41    //�¶�ֵ��8λ�Ĵ���
#define MPU_TEMP_OUTL_REG       0X42    //�¶�ֵ��8λ�Ĵ���

#define MPU_ACCEL_XOUTH_REG     0X3B    //���ٶ�ֵ��X���8λ�Ĵ���
#define MPU_ACCEL_XOUTL_REG     0X3C    //���ٶ�ֵ��X���8λ�Ĵ���
#define MPU_ACCEL_YOUTH_REG     0X3D    //���ٶ�ֵ��Y���8λ�Ĵ���
#define MPU_ACCEL_YOUTL_REG     0X3E    //���ٶ�ֵ��Y���8λ�Ĵ���
#define MPU_ACCEL_ZOUTH_REG     0X3F    //���ٶ�ֵ��Z���8λ�Ĵ���
#define MPU_ACCEL_ZOUTL_REG     0X40    //���ٶ�ֵ��Z���8λ�Ĵ���

#define MPU_GYRO_XOUTH_REG      0X43    //������ֵ��X���8λ�Ĵ���
#define MPU_GYRO_XOUTL_REG      0X44    //������ֵ��X���8λ�Ĵ���
#define MPU_GYRO_YOUTH_REG      0X45    //������ֵ��Y���8λ�Ĵ���
#define MPU_GYRO_YOUTL_REG      0X46    //������ֵ��Y���8λ�Ĵ���
#define MPU_GYRO_ZOUTH_REG      0X47    //������ֵ��Z���8λ�Ĵ���
#define MPU_GYRO_ZOUTL_REG      0X48    //������ֵ��Z���8λ�Ĵ���

#define AK8963_ADDRESS 0x18     //�����Ƶ�ַ0x0C
#define AK8963_CNTL1        0x0A  //�����ƶ�ȡ�Ĵ���
#define AK8963_HXL          0x03    //������X���8λ�Ĵ���
#define AK8963_HXH          0x04    //������X���8λ�Ĵ���
#define AK8963_HYL          0x05    //������Y���8λ�Ĵ���
#define AK8963_HYH          0x06    //������Y���8λ�Ĵ���
#define AK8963_HZL          0x07    //������Z���8λ�Ĵ���
#define AK8963_HZH          0x08    //������Z���8λ�Ĵ���

#define GYROX_BIAS -2.62451148f //��ֹʱ�����Ƕ����������Ǿ��
#define GYROY_BIAS 0.305175781
#define GYROZ_BIAS -0.91552784

#define ACCX_BIAS 0.0f  //��ֹʱ���ٶȼƶ��������ٶȼƾ���˴�δ��ȡ��
#define ACCY_BIAS 0.0f
#define ACCZ_BIAS 0.0f

struct Axisf
{
    float x;
    float y;
    float z;
};

struct MPU9250_t
{
    struct Axisf gyro;
    struct Axisf acc;
    struct Axisf mag;
    struct Axisf attitude;
};


void MPU9250_Init(void);
void GetImuData(void);
void imuUpdate(struct Axisf acc, struct Axisf gyro, struct Axisf mag);
float Kalman_Filter(float angle_m, float gyro_m);

#endif /* APPLICATIONS_MPU9250_LIB_MPU9250_DRV_H_ */
