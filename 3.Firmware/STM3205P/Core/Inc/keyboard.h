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

#include "display.h"
#include "main.h"
#include "stdbool.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include <string.h>

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------
#define VOLTAGE_LIMIT_SUPERIOR 32000 // 32.000V
#define VOLTAGE_LIMIT_INFERIOR 0     // 0.000V

#define CURRENT_LIMIT_SUPERIOR 5000 // 5.000A
#define CURRENT_LIMIT_INFERIOR 0    // 0.000A

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
typedef union
{
    struct
    {
        uint16_t M1 : 1;
        uint16_t M2 : 1;
        uint16_t M3 : 1;
        uint16_t M4 : 1;

        uint16_t Lock : 1;
        uint16_t OCP : 1;
        uint16_t OVP : 1;
        uint16_t OnOff : 1;

        uint16_t LeftArrow : 1;
        uint16_t RightArrow : 1;
        uint16_t VoltageCurrent : 1;

        uint16_t Reserved : 5;
    } Bits;

    uint16_t Value;

} keyboard_keys_t;

typedef struct
{
    keyboard_keys_t Keys;

    int8_t DialValue;

} keyboard_t;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
extern void Keyboard_Read();

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------

extern keyboard_t Keyboard;
extern keyboard_t KeyboardPrev;

extern uint8_t DialPrevState = 0;
extern uint8_t DialStep = 0;
extern int8_t DialDirection = 0;

#endif /* SRC_KEYBOARD_H_ */
