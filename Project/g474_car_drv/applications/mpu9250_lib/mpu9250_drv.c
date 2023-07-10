/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-22     Yifang       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "mpu9250_drv.h"

#include <math.h>

extern I2C_HandleTypeDef hi2c3;

#define DEG2RAD     0.017453293f    /*��ת����*/
#define RAD2DEG     57.29578f       /*����ת��*/

struct MPU9250_t mpu9250;

float Kp = 2.0f;        /*��������*/
float Ki = 0.2f;        /*��������*/
float exInt = 0.0f;
float eyInt = 0.0f;
float ezInt = 0.0f;     /*��������ۼ�*/

static float q0 = 1.0f; /*��Ԫ��*/
static float q1 = 0.0f;
static float q2 = 0.0f;
static float q3 = 0.0f;

int yaw,pitch,roll;

volatile uint32_t last_update, now_update;

void MPU9250_Init(void)
{
    unsigned char pdata;
    //����豸�Ƿ�׼����
    HAL_I2C_IsDeviceReady(&hi2c3, MPU9250_ADDRESS, 10, HAL_MAX_DELAY);
    //��������Ƿ�׼����
    HAL_I2C_GetState(&hi2c3);

    pdata=0x80; //��λMPU
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_PWR_MGMT1_REG, 1, &pdata, 1, HAL_MAX_DELAY);
    HAL_I2C_IsDeviceReady(&hi2c3, MPU9250_ADDRESS, 10, HAL_MAX_DELAY);

    HAL_Delay(500);  //��λ����Ҫ�ȴ�һ��ʱ�䣬�ȴ�оƬ��λ���

    pdata=0x01; //����MPU
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_PWR_MGMT1_REG, 1, &pdata, 1, HAL_MAX_DELAY);

    pdata=3<<3; //��������Ϊ2000
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_GYRO_CFG_REG, 1, &pdata, 1, HAL_MAX_DELAY);

    pdata=01;   //���ü��ٶȴ��������̡�4g
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_ACCEL_CFG_REG, 1, &pdata, 1, HAL_MAX_DELAY);

    pdata=0; //�����ǲ�����Ƶ����
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_SAMPLE_RATE_REG, 1, &pdata, 1, HAL_MAX_DELAY);

    pdata=0;    //�ر������ж�
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_INT_EN_REG, 1, &pdata, 1, HAL_MAX_DELAY);

    pdata=0;    //�ر�FIFO
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_FIFO_EN_REG, 1, &pdata, 1, HAL_MAX_DELAY);

    pdata=0X02; //������·ģʽ��ֱ�Ӷ�ȡAK8963����������
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_INTBP_CFG_REG, 1, &pdata, 1, HAL_MAX_DELAY);
    HAL_Delay(10);  //��Ҫһ����ʱ�ô����ƹ���

    pdata = 4;  //����MPU9250�����ֵ�ͨ�˲���
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_CFG_REG, 1, &pdata, 1, HAL_MAX_DELAY);

    pdata=0;    //ʹ�������Ǻͼ��ٶȹ���
    HAL_I2C_Mem_Write(&hi2c3, MPU9250_ADDRESS, MPU_PWR_MGMT2_REG, 1, &pdata, 1, HAL_MAX_DELAY);

    pdata = 0x01;
    HAL_I2C_Mem_Write(&hi2c3, AK8963_ADDRESS, AK8963_CNTL1, 1, &pdata, 1, HAL_MAX_DELAY);
    HAL_Delay(10);
}

void GetImuData(void)
{
    uint8_t imu_data[14]={0};
    uint8_t mag_data[6] = {0};
    uint8_t pdata;
    short accx,accy,accz;
    short gyrox,gyroy,gyroz;
    short magx,magy,magz;

    float gyro_sensitivity = 16.384f;
    int acc_sensitivity = 8192;

    static short mag_count = 0;

    HAL_I2C_Mem_Read(&hi2c3, MPU9250_ADDRESS, MPU_ACCEL_XOUTH_REG, 1, imu_data, 14, HAL_MAX_DELAY); //��ȡ�����Ǻͼ��ٶȼƵ�����
    accx = (imu_data[0]<<8)|imu_data[1];
    accy = (imu_data[2]<<8)|imu_data[3];
    accz = (imu_data[4]<<8)|imu_data[5];
    gyrox = (imu_data[8]<<8)|imu_data[9];
    gyroy = (imu_data[10]<<8)|imu_data[11];
    gyroz = (imu_data[12]<<8)|imu_data[13];

    mpu9250.gyro.x = (float)(gyrox-GYROX_BIAS)/gyro_sensitivity;
    mpu9250.gyro.y = (float)(gyroy-GYROY_BIAS)/gyro_sensitivity;
    mpu9250.gyro.z = (float)(gyroz-GYROZ_BIAS)/gyro_sensitivity;

    mpu9250.acc.x = (float)(accx-ACCX_BIAS)/acc_sensitivity;
    mpu9250.acc.y = (float)(accy-ACCY_BIAS)/acc_sensitivity;
    mpu9250.acc.z = (float)(accz-ACCZ_BIAS)/acc_sensitivity;

    mag_count++;
    if(mag_count == 10) //�����Ʋ��ܶ�ȡ̫Ƶ��
    {
        HAL_I2C_Mem_Read(&hi2c3, AK8963_ADDRESS, AK8963_HXL, 1, mag_data, 6, HAL_MAX_DELAY);    //��ȡ����������
        magx = (mag_data[0]<<8)|mag_data[1];
        magy = (mag_data[2]<<8)|mag_data[3];
        magz = (mag_data[4]<<8)|mag_data[5];
        mpu9250.mag.x = (float)magy/1000.0f;        //�����Ƶ����귽λ��ͬ
        mpu9250.mag.y = (float)magx/1000.0f;
        mpu9250.mag.z = -(float)magz/1000.0f;
        pdata = 1;
        HAL_I2C_Mem_Write(&hi2c3, AK8963_ADDRESS, AK8963_CNTL1, 1, &pdata, 1, HAL_MAX_DELAY);   //Ϊ��һ�ζ�ȡ������������׼��
        mag_count = 0;

//        rt_kprintf("$%.2f %.2f %.2f;", mpu9250.acc.x, mpu9250.acc.y, mpu9250.acc.z);
//        rt_kprintf("$%.2f %.2f %.2f;", mpu9250.gyro.x, mpu9250.gyro.y, mpu9250.gyro.z);
//        rt_kprintf("$%.2f %.2f %.2f;", mpu9250.mag.x, mpu9250.mag.y, mpu9250.mag.z);
    }
}

void imuUpdate(struct Axisf acc, struct Axisf gyro, struct Axisf mag)
{
    float q0q0 = q0 * q0;
    float q1q1 = q1 * q1;
    float q2q2 = q2 * q2;
    float q3q3 = q3 * q3;

    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    float q0q3 = q0 * q3;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q3 = q2 * q3;

    float normalise;
    float ex, ey, ez;
    float halfT;
    float hx, hy, hz, bx, bz;
    float vx, vy, vz, wx, wy, wz;

    now_update = HAL_GetTick(); //��λms
    halfT = ((float)(now_update - last_update) / 2000.0f);
    last_update = now_update;

    gyro.x *= DEG2RAD;  /*��ת����*/
    gyro.y *= DEG2RAD;
    gyro.z *= DEG2RAD;

    /* �Լ��ٶȼ����ݽ��й�һ������ */
    if(acc.x != 0 || acc.y != 0 || acc.z != 0)
    {
        normalise = sqrt(acc.x * acc.x + acc.y * acc.y + acc.z * acc.z);
        acc.x /= normalise;
        acc.y /= normalise;
        acc.z /= normalise;
    }

    /* �Դ��������ݽ��й�һ������ */
    if(mag.x != 0 || mag.y != 0 || mag.z != 0)
    {
        normalise = sqrt(mag.x * mag.x + mag.y * mag.y + mag.z * mag.z);
        mag.x /= normalise;
        mag.y /= normalise;
        mag.z /= normalise;
    }

    /* ���������ͶӰ�����������ϵĸ������� */
    hx = 2.0f*mag.x*(0.5f - q2q2 - q3q3) + 2.0f*mag.y*(q1q2 - q0q3) + 2.0f*mag.z*(q1q3 + q0q2);
    hy = 2.0f*mag.x*(q1q2 + q0q3) + 2.0f*mag.y*(0.5f - q1q1 - q3q3) + 2.0f*mag.z*(q2q3 - q0q1);
    hz = 2.0f*mag.x*(q1q3 - q0q2) + 2.0f*mag.y*(q2q3 + q0q1) + 2.0f*mag.z*(0.5f - q1q1 - q2q2);
    bx = sqrt((hx*hx) + (hy*hy));
    bz = hz;

    /* ������ٶȼ�ͶӰ�����������ϵĸ������� */
    vx = 2.0f*(q1q3 - q0q2);
    vy = 2.0f*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;

    /* �������Ĵ������·��� */
    wx = 2.0f*bx*(0.5f - q2q2 - q3q3) + 2.0f*bz*(q1q3 - q0q2);
    wy = 2.0f*bx*(q1q2 - q0q3) + 2.0f*bz*(q0q1 + q2q3);
    wz = 2.0f*bx*(q0q2 + q1q3) + 2.0f*bz*(0.5f - q1q1 - q2q2);

    /* �������ۼƣ������������������� */
    ex = (acc.y*vz - acc.z*vy) + (mag.y*wz - mag.z*wy);
    ey = (acc.z*vx - acc.x*vz) + (mag.z*wx - mag.x*wz);
    ez = (acc.x*vy - acc.y*vx) + (mag.x*wy - mag.y*wx);

    /* �����˲� PI */
    exInt += ex * Ki * halfT;
    eyInt += ey * Ki * halfT;
    ezInt += ez * Ki * halfT;
    gyro.x += Kp*ex + exInt;
    gyro.y += Kp*ey + eyInt;
    gyro.z += Kp*ez + ezInt;

    /* ʹ��һ���������������Ԫ�� */
    q0 += (-q1 * gyro.x - q2 * gyro.y - q3 * gyro.z) * halfT;
    q1 += ( q0 * gyro.x + q2 * gyro.z - q3 * gyro.y) * halfT;
    q2 += ( q0 * gyro.y - q1 * gyro.z + q3 * gyro.x) * halfT;
    q3 += ( q0 * gyro.z + q1 * gyro.y - q2 * gyro.x) * halfT;

    /* ����Ԫ�����й�һ������ */
    normalise = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 /= normalise;
    q1 /= normalise;
    q2 /= normalise;
    q3 /= normalise;

    /* ����Ԫ�����ŷ���� */
    mpu9250.attitude.x = -asinf(-2*q1*q3 + 2*q0*q2) * RAD2DEG;  //pitch
    mpu9250.attitude.y = atan2f(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1) * RAD2DEG;   //roll
    mpu9250.attitude.z = atan2f(2*q1*q2 + 2*q0*q3, -2*q2*q2 - 2*q3*q3 + 1) * RAD2DEG;   //yaw

    yaw = mpu9250.attitude.z;       //����J-Scope��ȡ
    pitch = mpu9250.attitude.x;
    roll = mpu9250.attitude.y;

#ifdef MPU_READ_DATA
    rt_kprintf("$%d %d %d;",yaw,pitch,roll);
    rt_thread_mdelay(10);
#endif
}
