/* ###################################################################
**     Filename    : led_indicator.c
**     Project     : ProjectName
**     Processor   : Processor
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Jun 01, 2026
**     Abstract    :
**     Author      : Lucas Moraes
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
#include "led_indicator.h"

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
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: Jun 01, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void LedIndicator_Init(LedIndicator_t *led)
{
    led->value = 0;
    led->blink = 0;
    led->time_on_started = 0;
    led->time_on = 100;
    led->time_off_started = 0;
    led->time_off = 100;
    led->blink_cnt = 0;
    led->blink_cycles = 10;
}

/* ###################################################################
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: Jun 01, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void LedIndicator_WriteValue(LedIndicator_t *led, bool value)
{
    led->value = value;
}

/* ###################################################################
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: Jun 01, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void LedIndicator_Set(LedIndicator_t *led)
{
    led->value = true;
}

/* ###################################################################
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: Jun 01, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void LedIndicator_Clear(LedIndicator_t *led)
{
    led->value = false;
}

/* ###################################################################
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: Jun 01, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void LedIndicator_Blink(LedIndicator_t *led, uint32_t millis)
{
    led->blink = true;
    led->blink_cnt = 0;
    led->time_off_started = millis + led->time_on;
    led->time_on_started = millis;
}

/* ###################################################################
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: Jun 01, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void LedIndicator_SetTime(LedIndicator_t *led, uint16_t time_on, uint16_t time_off)
{
    led->time_on = time_on;
    led->time_off = time_off;
}

/* ###################################################################
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: Jun 01, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
void LedIndicator_SetCycles(LedIndicator_t *led, uint16_t cycles)
{
    led->blink_cycles = cycles;
}

/* ###################################################################
 * Function: FunctionName
 * Author: Moraes, L.
 * Date: Jun 01, 2026
 * Revision: 1.0
 * --------------------
 * Function description
 *
 *  arg1: input arg1
 *
 *  arg2: input arg2
 *
 *  returns: void
 *
 *
###################################################################*/
bool LedIndicator_Update(LedIndicator_t *led, uint32_t millis)
{
    bool result = led->value;

    if(led->blink)
    {
        if(led->blink_cnt >= led->blink_cycles)
        {
            led->blink = 0;
            led->blink_cnt = 0;
            result = false;
        }
        else
        {
            if((millis - led->time_on_started) < led->time_on)
            {
                result = true;
            }
            else if((millis - led->time_off_started) < led->time_off)
            {
                result = false;
            }
            else
            {
                led->blink_cnt++;

                if(led->blink_cnt < led->blink_cycles)
                {
                    led->time_on_started = millis;
                    led->time_off_started = millis + led->time_on;
                    result = true;
                }
            }
        }
    }

    return result;
}