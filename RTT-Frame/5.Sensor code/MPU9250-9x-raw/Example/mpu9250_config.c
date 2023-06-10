/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Yifang       the first version
 */
#include <rtthread.h>
#include <stdint.h>
#include "mpu9250.h"
#include "mpu9250_config.h"

static uint8_t ak8963_WhoAmI = 0;
static uint8_t mpu9250_WhoAmI = 0;
static MPU9250 mpu;

SPI_HandleTypeDef hspi1;

/* Init function */
static int mpu9250_drv_init(int argc, char *argv[])
{
    MX_SPI1_Init();

    MPU9250_Init(&mpu);

    while(1)
    {
        ak8963_WhoAmI = mpu_r_ak8963_WhoAmI(&mpu);
        mpu9250_WhoAmI = mpu_r_WhoAmI(&mpu);
        MPU9250_ReadAccel(&mpu);
        MPU9250_ReadGyro(&mpu);
        MPU9250_ReadMag(&mpu);
        rt_kprintf("AK8963: 0x%x\nMPU9250: 0x%x\n", ak8963_WhoAmI,
                mpu9250_WhoAmI);
        rt_kprintf("AX:%d \tAY:%d\t AZ:%d\n", mpu.mpu_data.Accel_row[0],
                mpu.mpu_data.Accel_row[1], mpu.mpu_data.Accel_row[2]);
        rt_kprintf("AX:%.3f \tAY:%.3f\t AZ:%.3f\n", mpu.mpu_data.Accel[0],
                mpu.mpu_data.Accel[1], mpu.mpu_data.Accel[2]);
        rt_kprintf("GX:%d \tGY:%d\t GZ:%d\n", mpu.mpu_data.Gyro_row[0],
                mpu.mpu_data.Gyro_row[1], mpu.mpu_data.Gyro_row[2]);
        rt_kprintf("GX:%.3f \tGY:%.3f\t GZ:%.3f\n", mpu.mpu_data.Gyro[0],
                mpu.mpu_data.Gyro[1], mpu.mpu_data.Gyro[2]);
        rt_kprintf("MX:%d \tMY:%d\t MZ:%d\n", mpu.mpu_data.Magn_row[0],
                mpu.mpu_data.Magn_row[1], mpu.mpu_data.Magn_row[2]);
        rt_kprintf("MX:%.3f \tMY:%.3f\t MZ:%.3f\n", mpu.mpu_data.Magn[0],
                mpu.mpu_data.Magn[1], mpu.mpu_data.Magn[2]);
        rt_kprintf("*************************\n");

        rt_thread_mdelay(50);
    }
}
MSH_CMD_EXPORT(mpu9250_drv_init, mpu9250 sensor init function);

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}
