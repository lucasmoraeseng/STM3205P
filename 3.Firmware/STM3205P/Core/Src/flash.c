/* ###################################################################
**     Filename    : flash.h
**     Project     : STM3205P
**     Processor   :
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Oct 6, 2025, 5:07:13 PM
**     Abstract    :
**     Author	   : lucas
**
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------
#include "flash.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------
data_storage_t flashData;

const data_storage_t DefaultFlashData =
    {
        .Signature = FLASH_SIGNATURE,

        .memory1 = {5.0f, 1.0f},
        .memory2 = {3.3f, 2.0f},
        .memory3 = {12.0f, 3.0f},
        .memory4 = {24.0f, 4.0f},
        .memory5 = {32.0f, 5.0f}};

//--------------------------------------------------------------------
// Code
//--------------------------------------------------------------------

/* ###################################################################
 * Function:
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Initialize struct of current sensor, calculating it's parameters
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
HAL_StatusTypeDef Flash_WriteSettings(data_storage_t *data)
{
    HAL_StatusTypeDef status;

    uint32_t address = FLASH_USER_START_ADDR;

    HAL_FLASH_Unlock();

    // Erase page
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t pageError;

    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInit.PageAddress = FLASH_USER_START_ADDR;
    eraseInit.NbPages = 1;

    status = HAL_FLASHEx_Erase(&eraseInit, &pageError);

    if(status != HAL_OK)
    {
        HAL_FLASH_Lock();
        return status;
    }

    // Write data half-word by half-word
    uint16_t *ptr = (uint16_t *)data;

    for(uint32_t i = 0; i < (sizeof(data_storage_t) / 2); i++)
    {
        status = HAL_FLASH_Program(
            FLASH_TYPEPROGRAM_HALFWORD,
            address,
            ptr[i]);

        if(status != HAL_OK)
        {
            HAL_FLASH_Lock();
            return status;
        }

        address += 2;
    }

    HAL_FLASH_Lock();

    return HAL_OK;
}

/* ###################################################################
 * Function:
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Initialize struct of current sensor, calculating it's parameters
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void Flash_ReadSettings(data_storage_t *data)
{
    memcpy(
        data,
        (void *)FLASH_USER_START_ADDR,
        sizeof(data_storage_t));

    // Check if flash contains valid data
    if(data->Signature != FLASH_SIGNATURE)
    {
        // Load default values
        memcpy(
            data,
            &DefaultFlashData,
            sizeof(data_storage_t));

        // Optional:
        // Save defaults into flash
        Flash_WriteSettings(data);
    }
}
