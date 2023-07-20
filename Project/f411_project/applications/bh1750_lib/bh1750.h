/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-14     Yifang       the first version
 */
#ifndef APPLICATIONS_BH1750_LIB_BH1750_H_
#define APPLICATIONS_BH1750_LIB_BH1750_H_

#include <rthw.h>
#include <rtthread.h>

enum BH1750_Mode
{
    CONT_HI_RES  = 0x10,        //Continuously H-Resolution Mode
    CONT_HI_RES_2 = 0x11,       //Continuously H-Resolution Mode2
    CONT_LO_RES = 0x13,         //Continuously L-Resolution Mode
    OT_HI_RES = 0x20,           //One Time H-Resolution Mode
    OT_HI_RES_2 = 0x21,         //One Time H-Resolution Mode2
    OT_LO_RES = 0x23            //One Time L-Resolution Mode
};

enum BH1750_Address{
    // address of the device

    ADDR_0V = 0x23,     //set if co
    ADDR_N0V = 0x5c
};

// CORE FUNCTIONS AND UTILITIES

typedef enum BH1750_Status
{
    // S_XXXX -> sensor (transmission) related flags
    // I_XXXX -> initialisation related flags
    // TODO: zaimplementować xDDDD

    S_ERROR = -1,
    S_OK = 1,
    I_ERROR = 2,
    I_OK =  -2,
    ALL_OK = 0
}BH1750_Status;

typedef struct BH1750_Data
{
    // sensor's state and data
    uint8_t s_mode_;
    uint16_t s_address_;
    BH1750_Status s_status_;
    I2C_HandleTypeDef* handle_;

}BH1750_Data;


// prototypes
BH1750_Data BH1750_Init(uint8_t mode, uint16_t address, I2C_HandleTypeDef* handle);
float BH1750_Read(BH1750_Data* d);

#endif /* APPLICATIONS_BH1750_LIB_BH1750_H_ */
