/* ###################################################################
**     Filename    : HAL_74HC595.c
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

#include "HAL_74HC595.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------


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
void HAL_74HC595_Init(HAL_74HC595_t *obj,
                      GPIO_TypeDef *SD_Port, uint16_t SD_Pin,
                      GPIO_TypeDef *RCLK_Port, uint16_t RCLK_Pin,
                      GPIO_TypeDef *SRCLK_Port, uint16_t SRCLK_Pin,
                      uint16_t byte_count)
{
    obj->SD_Port = SD_Port;
    obj->SD_Pin = SD_Pin;
    obj->RCLK_Port = RCLK_Port;
    obj->RCLK_Pin = RCLK_Pin;
    obj->SRCLK_Port = SRCLK_Port;
    obj->SRCLK_Pin = SRCLK_Pin;
    obj->byte_count = byte_count;

    HAL_GPIO_WritePin(obj->SD_Port, obj->SD_Pin, 0);
    HAL_GPIO_WritePin(obj->RCLK_Port, obj->RCLK_Pin, 0);
    HAL_GPIO_WritePin(obj->SRCLK_Port, obj->SRCLK_Pin, 0);
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
void HAL_74HC595_WriteData(HAL_74HC595_t *obj, uint8_t * data)
{
    HAL_GPIO_WritePin(obj->RCLK_Port, obj->RCLK_Pin, 0); // Set RCLK low

    for (int byte_index = 0; byte_index < obj->byte_count; byte_index++)
    {
        uint8_t current_byte = data[obj->byte_count - 1 - byte_index]; // Send MSB first

        for (int bit_index = 0; bit_index < 8; bit_index++)
        {
            // Set SD pin according to the current bit
            if (current_byte & (1 << (7 - bit_index))) // Check MSB first
            {
                HAL_GPIO_WritePin(obj->SD_Port, obj->SD_Pin, 1);
            }
            else
            {
                HAL_GPIO_WritePin(obj->SD_Port, obj->SD_Pin, 0);
            }

            // Pulse SRCLK to shift in the bit
            HAL_GPIO_WritePin(obj->SRCLK_Port, obj->SRCLK_Pin, 1);
            HAL_GPIO_WritePin(obj->SRCLK_Port, obj->SRCLK_Pin, 0);
        }
    }

    HAL_GPIO_WritePin(obj->RCLK_Port, obj->RCLK_Pin, 1); // Set RCLK high to latch data
    HAL_GPIO_WritePin(obj->RCLK_Port, obj->RCLK_Pin, 0); // Set RCLK low
}
