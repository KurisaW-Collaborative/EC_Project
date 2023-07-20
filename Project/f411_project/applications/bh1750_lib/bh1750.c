/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-05     Yifang       the first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>

#include "stm32f4xx.h"
#include "bh1750.h"

BH1750_Data BH1750_Init(uint8_t mode, uint16_t address, I2C_HandleTypeDef* handle)
{
    BH1750_Data dreturn;
    dreturn.s_mode_ = mode;
    dreturn.s_address_ = address << 1;
    dreturn.handle_ = handle;

    HAL_StatusTypeDef s_ret_ = HAL_I2C_Master_Transmit(dreturn.handle_, dreturn.s_address_, &dreturn.s_mode_, 1, HAL_MAX_DELAY);
    if(s_ret_ == HAL_OK){ dreturn.s_status_ = ALL_OK;}

    return dreturn;
}

float BH1750_Read(BH1750_Data* d)
{
    // read and return readout value as float
    // TODO: dodać jakieś ify, do sprawdzania stanu, i BLOKOWANIU odczytu jeśli coś nie działa (na podstawie s_status_)
    if(d->s_status_ == ALL_OK)
    {
    uint8_t readout_buffer[2];
    HAL_Delay(130);
    HAL_I2C_Master_Transmit(d->handle_, d->s_address_, &d->s_mode_, 1, HAL_MAX_DELAY);
    HAL_StatusTypeDef s_ret_ = HAL_I2C_Master_Receive(d->handle_, d->s_address_, readout_buffer, 2, HAL_MAX_DELAY);

    if(s_ret_ == HAL_OK){ d->s_status_ = ALL_OK;}

    uint16_t holder = ((uint16_t)readout_buffer[0]<<8 | readout_buffer[1]);
    float freturn = holder/1.2;

    return freturn;
    }
}
