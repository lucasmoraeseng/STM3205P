/* ###################################################################
**     Filename    : button.h
**     Project     : STM3205P
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : May 30, 2026
**     Author      : lucas
**
**     Module description.
**
** ###################################################################*/

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------

#include "stdbool.h"
#include "stdint.h"

#include "data_types.h"
#include "display.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
typedef struct
{
    uint8_t CurrentState;
    uint8_t PreviousState;

    uint8_t KeyDown;
    uint8_t KeyUp;

    uint8_t Pressed;

    uint32_t PressingTime;

} Button_t;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
extern void Button_Init(Button_t *btn_obj);
extern void Button_Update(Button_t *btn_obj, uint8_t state);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------

#endif /* SRC_BUTTON_H_ */