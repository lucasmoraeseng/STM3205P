/* ###################################################################
**     Filename    : flash.h
**     Project     : STM3205P
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Oct 14, 2025
**     Author      : lucas
**
**     Interface para controle da flash via HAL (MX).
**
** ###################################################################*/

#ifndef SRC_FLASH_H_
#define SRC_FLASH_H_

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------

#include "stdbool.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include <string.h>

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------
#define FLASH_USER_START_ADDR 0x08007C00
#define FLASH_SIGNATURE 0xDEADB33F

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
typedef struct
{
    float Voltage;
    float Current;
    uint8_t OVP;
    uint8_t OCP;
} settings_t;

typedef struct
{
    uint32_t Signature;
    settings_t memory1;
    settings_t memory2;
    settings_t memory3;
    settings_t memory4;
    settings_t memory5;
} data_storage_t;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
extern HAL_StatusTypeDef Flash_WriteSettings(data_storage_t *data);
extern void Flash_ReadSettings(data_storage_t *data);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------
extern data_storage_t flashData;

#endif /* SRC_FLASH_H_ */
