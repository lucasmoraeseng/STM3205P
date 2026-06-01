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

#include "data_types.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------
#define FLASH_USER_START_ADDR 0x08007C00
#define FLASH_SIGNATURE 0xDEADBEEF

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------

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
