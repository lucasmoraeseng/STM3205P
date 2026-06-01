/* ###################################################################
**     Filename    : led_indicator.h
**     Project     : STM3205P
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Jun 01, 2026
**     Author      : lucas
**
**     Module description.
**
** ###################################################################*/

#ifndef SRC_LED_INDICATOR_H_
#define SRC_LED_INDICATOR_H_

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------

#include "data_types.h"
#include "stdbool.h"
#include "stdint.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------
typedef struct
{
    uint8_t value;
    uint8_t blink;
    uint16_t time_on;
    uint16_t time_on_started;
    uint16_t time_off;
    uint16_t time_off_started;
    uint16_t blink_cnt;
    uint16_t blink_cycles;
} LedIndicator_t;

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
extern void LedIndicator_Init(LedIndicator_t *led);

extern void LedIndicator_WriteValue(LedIndicator_t *led, bool value);
extern void LedIndicator_Set(LedIndicator_t *led);
extern void LedIndicator_Clear(LedIndicator_t *led);
extern void LedIndicator_Blink(LedIndicator_t *led, uint32_t millis);
extern void LedIndicator_SetTime(LedIndicator_t *led, uint16_t time_on, uint16_t time_off);
extern void LedIndicator_SetCycles(LedIndicator_t *led, uint16_t cycles);
extern bool LedIndicator_Update(LedIndicator_t *led, uint32_t millis);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------

#endif /* SRC_LED_INDICATOR_H_ */