/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Yifang       the first version
 */
#include "bmp280_config.h"
#include <stdio.h>

I2C_HandleTypeDef hi2c2;

static BMP280_HandleTypedef bmp280;
static float pressure, temperature, humidity;

/* Init function */
static int bmp280_drv_init(int argc, char *argv[])
{
    MX_I2C2_Init();

    bmp280_init_default_params(&bmp280.params);
    bmp280.addr = BMP280_I2C_ADDRESS_0;
    bmp280.i2c = &hi2c2;

    while (!bmp280_init(&bmp280, &bmp280.params))
    {
        printf("BMP280 initialization failed\n");
        HAL_Delay(2000);
    }
    printf("bmp280.id is 0x%x\n",bmp280.id);
    bool bme280p = bmp280.id == BME280_CHIP_ID;
    printf("BMP280: found %d\n",bme280p);

    while(1)
    {
        rt_thread_mdelay(100);
        while (!bmp280_read_float(&bmp280, &temperature, &pressure, &humidity))
        {
            printf("Temperature/pressure reading failed\n");
            HAL_Delay(2000);
        }

        printf("Pressure: %.2f Pa, Temperature: %.2f C", pressure, temperature);
        if (bme280p)
        {
            printf(", Humidity: %.2f\n", humidity);
        }

        else
        {
            printf("\n");
        }
        HAL_Delay(2000);
    }

    return 0;
}
MSH_CMD_EXPORT(bmp280_drv_init, bmp280 sensor init function);

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}
