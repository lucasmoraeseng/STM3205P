/* ###################################################################
**     Filename    : keyboard.h
**     Project     : STM3205P
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Oct 14, 2025
**     Author      : lucas
**
**     Interface para controle da flash via HAL (MX).
**
** ###################################################################*/

#ifndef SRC_KEYBOARD_H_
#define SRC_KEYBOARD_H_

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------

#include "stdbool.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include <string.h>

#include "button.h"
#include "data_types.h"
#include "display.h"
#include "main.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------

typedef struct
{
    Button_t M1;
    Button_t M2;
    Button_t M3;
    Button_t M4;

    Button_t Lock;
    Button_t OCP;
    Button_t OVP;
    Button_t OnOff;

    Button_t LeftArrow;
    Button_t RightArrow;
    Button_t VoltageCurrent;

    int8_t DialValue;
    int8_t DialDirection;
    uint8_t DialStep;
    uint8_t DialPrevState;

} Keyboard_t;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
extern void Keyboard_Init(Keyboard_t *kb_obj);
extern void Keyboard_Read(Keyboard_t *kb_obj);
extern void Keyboard_ValueAdjust(Keyboard_t *kb_obj, uint8_t dp_blink_index, accx3_t *value, int32_t limit_superior, int32_t limit_inferior);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------

extern Keyboard_t Keyboard;

#endif /* SRC_KEYBOARD_H_ */
