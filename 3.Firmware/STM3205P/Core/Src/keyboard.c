/* ###################################################################
**     Filename    : display.
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
#include "keyboard.h"
#include "data_types.h"
#include "display.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
uint32_t Keyboard_GetMultiplier(accx3_t value);

//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------
Keyboard_t Keyboard;

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
void Keyboard_Init(Keyboard_t *kb_obj)
{
    Button_Init(&kb_obj->M1);
    Button_Init(&kb_obj->M2);
    Button_Init(&kb_obj->M3);
    Button_Init(&kb_obj->M4);
    Button_Init(&kb_obj->Lock);
    Button_Init(&kb_obj->OCP);
    Button_Init(&kb_obj->OVP);
    Button_Init(&kb_obj->OnOff);
    Button_Init(&kb_obj->LeftArrow);
    Button_Init(&kb_obj->RightArrow);
    Button_Init(&kb_obj->VoltageCurrent);

    kb_obj->DialValue = 0;
    kb_obj->DialDirection = 0;
    kb_obj->DialStep = 0;
    kb_obj->DialPrevState = 0;
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
void Keyboard_Read(Keyboard_t *kb_obj, uint32_t millis)
{
    //----------------------------------------------------------------
    // Reset keyboard matrix
    //----------------------------------------------------------------
    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_RESET);

    // Optional settling time
    // delay_us(10);

    //----------------------------------------------------------------
    // IN1
    //----------------------------------------------------------------
    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_SET);

    // delay_us(10);

    Button_Update(&kb_obj->M1, HAL_GPIO_ReadPin(key_out1_GPIO_Port, key_out1_Pin), millis);

    Button_Update(&kb_obj->M4, HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin), millis);

    Button_Update(&kb_obj->M2, HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin), millis);

    Button_Update(&kb_obj->M3, HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin), millis);

    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_RESET);

    //----------------------------------------------------------------
    // IN2
    //----------------------------------------------------------------
    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_SET);

    // delay_us(10);

    Button_Update(&kb_obj->Lock, HAL_GPIO_ReadPin(key_out1_GPIO_Port, key_out1_Pin), millis);

    Button_Update(&kb_obj->OnOff, HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin), millis);

    Button_Update(&kb_obj->OCP, HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin), millis);

    Button_Update(&kb_obj->OVP, HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin), millis);

    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_RESET);

    //----------------------------------------------------------------
    // IN3
    //----------------------------------------------------------------
    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_SET);

    // delay_us(10);

    Button_Update(&kb_obj->LeftArrow, HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin), millis);

    Button_Update(&kb_obj->RightArrow, HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin), millis);

    Button_Update(&kb_obj->VoltageCurrent, HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin), millis);

    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_RESET);

    //----------------------------------------------------------------
    // Rotary encoder
    //----------------------------------------------------------------

    kb_obj->DialValue = 0;

    // Read encoder channels
    uint8_t B = (HAL_GPIO_ReadPin(BKeyRight_GPIO_Port, BKeyRight_Pin) == GPIO_PIN_RESET);

    uint8_t A = (HAL_GPIO_ReadPin(BKeyLeft_GPIO_Port, BKeyLeft_Pin) == GPIO_PIN_RESET);

    // Build current state
    uint8_t currentState = (A << 1) | B;

    // Process only state changes
    if(currentState != kb_obj->DialPrevState)
    {
        switch(kb_obj->DialStep)
        {
        //--------------------------------------------------------
        // Waiting for encoder to leave idle state
        //--------------------------------------------------------
        case 0:

            if((kb_obj->DialPrevState == 0b00) && (currentState == 0b10))
            {
                kb_obj->DialDirection = 1;
                kb_obj->DialStep = 1;
            }
            else if((kb_obj->DialPrevState == 0b00) && (currentState == 0b01))
            {
                kb_obj->DialDirection = -1;
                kb_obj->DialStep = 1;
            }

            break;

        //--------------------------------------------------------
        // Second state must be 11
        //--------------------------------------------------------
        case 1:

            if(currentState == 0b11)
            {
                kb_obj->DialStep = 2;
            }
            else
            {
                kb_obj->DialStep = 0;
                kb_obj->DialDirection = 0;
            }

            break;

        //--------------------------------------------------------
        // Third state
        //--------------------------------------------------------
        case 2:

            if((kb_obj->DialDirection > 0) && (currentState == 0b01))
            {
                kb_obj->DialStep = 3;
            }
            else if((kb_obj->DialDirection < 0) && (currentState == 0b10))
            {
                kb_obj->DialStep = 3;
            }
            else
            {
                kb_obj->DialStep = 0;
                kb_obj->DialDirection = 0;
            }

            break;

        //--------------------------------------------------------
        // Final state must return to idle (00)
        //--------------------------------------------------------
        case 3:

            if(currentState == 0b00)
            {
                kb_obj->DialValue = kb_obj->DialDirection;
            }

            kb_obj->DialStep = 0;
            kb_obj->DialDirection = 0;

            break;
        }

        kb_obj->DialPrevState = currentState;
    }
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
void Keyboard_ValueAdjust(Keyboard_t *kb_obj, uint8_t dp_blink_index, accx3_t *value, int32_t limit_superior, int32_t limit_inferior)
{
    uint32_t multiplier = 0;
    uint32_t digit_1 = 0;
    uint32_t digit_2 = 0;
    uint32_t digit_3 = 0;
    uint32_t digit_4 = 0;

    multiplier = Keyboard_GetMultiplier(*value);

    digit_1 = multiplier;
    digit_2 = multiplier / 10;
    digit_3 = multiplier / 100;
    digit_4 = multiplier / 1000;

    if(*value < limit_superior && kb_obj->DialValue > 0)
    {
        if(dp_blink_index == 1)
        {
            *value += digit_1;
        }
        else if(dp_blink_index == 2)
        {
            *value += digit_2;
        }
        else if(dp_blink_index == 3)
        {
            *value += digit_3;
        }
        else if(dp_blink_index == 4)
        {
            *value += digit_4;
        }
    }
    else if(*value > limit_inferior && kb_obj->DialValue < 0)
    {
        if(dp_blink_index == 1)
        {
            *value -= digit_1;
        }
        else if(dp_blink_index == 2)
        {
            *value -= digit_2;
        }
        else if(dp_blink_index == 3)
        {
            *value -= digit_3;
        }
        else if(dp_blink_index == 4)
        {
            *value -= digit_4;
        }
    }

    kb_obj->DialValue = 0;

    if(*value > limit_superior)
    {
        *value = limit_superior;
    }
    else if(*value < limit_inferior)
    {
        *value = limit_inferior;
    }
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
uint32_t Keyboard_GetMultiplier(accx3_t value)
{
    if(value < 10000)
    {
        return 1000;
    }
    else if(value < 100000)
    {
        return 10000;
    }
    else if(value < 1000000)
    {
        return 100000;
    }
    else
    {
        return 1000000;
    }

    return 1000;
}