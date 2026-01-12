/* ###################################################################
**     Filename    : HAL_74HC595.h
**     Project     : STM3205P
**     Processor   : 
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Oct 6, 2025, 5:07:02 PM
**     Abstract    :
**     Author	   : lucas
**
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/


#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------
#include "stm32f1xx_hal.h"


//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------




//--------------------------------------------------------------------
// Typedef enum
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
typedef struct
{
    GPIO_TypeDef *SD_Port;
    uint16_t SD_Pin;
    GPIO_TypeDef *RCLK_Port;
    uint16_t RCLK_Pin;
    GPIO_TypeDef *SRCLK_Port;
    uint16_t SRCLK_Pin;
    uint16_t byte_count;
}HAL_74HC595_t;


//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
extern void HAL_74HC595_Init(HAL_74HC595_t *obj,
                      GPIO_TypeDef *SD_Port, uint16_t SD_Pin,
                      GPIO_TypeDef *RCLK_Port, uint16_t RCLK_Pin,
                      GPIO_TypeDef *SRCLK_Port, uint16_t SRCLK_Pin,
                      uint16_t byte_count);
extern void HAL_74HC595_WriteData(HAL_74HC595_t *obj, uint8_t * data);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------


#endif /* SRC_DISPLAY_H_ */
