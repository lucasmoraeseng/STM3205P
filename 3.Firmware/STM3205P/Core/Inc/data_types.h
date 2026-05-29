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

#ifndef SRC_DATA_TYPES_H_
#define SRC_DATA_TYPES_H_

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
#define accx3_t int32_t // num x 1000 so 1.234 is represented as 1234

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
typedef struct
{
    float Voltage;
    float Current;
    uint8_t OVP;
    uint8_t OCP;
} settings_float_t;

typedef struct
{
    accx3_t Voltage;
    accx3_t Current;
    uint8_t OVP;
    uint8_t OCP;
} settings_accx3_t;

typedef struct
{
    uint32_t Signature;
    settings_accx3_t memory1;
    settings_accx3_t memory2;
    settings_accx3_t memory3;
    settings_accx3_t memory4;
    settings_accx3_t memory5;
} data_storage_t;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------

#endif /* SRC_DATA_TYPES_H_ */
