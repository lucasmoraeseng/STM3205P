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
#include "display.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------
keyboard_t Keyboard;
keyboard_t KeyboardPrev;

uint8_t DialPrevState = 0;
uint8_t DialStep = 0;
int8_t DialDirection = 0;

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
void Keyboard_Read()
{
    //----------------------------------------------------------------
    // Reset keyboard states
    //----------------------------------------------------------------
    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_RESET);

    HAL_Delay(1);

    //----------------------------------------------------------------
    // IN1
    //----------------------------------------------------------------
    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_SET);

    // delay_us(10);

    Keyboard.Keys.Bits.M1 =
        HAL_GPIO_ReadPin(key_out1_GPIO_Port, key_out1_Pin);

    Keyboard.Keys.Bits.M4 =
        HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin);

    Keyboard.Keys.Bits.M2 =
        HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin);

    Keyboard.Keys.Bits.M3 =
        HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin);

    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_RESET);

    //----------------------------------------------------------------
    // IN2
    //----------------------------------------------------------------
    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_SET);

    // HAL_Delay(1);
    // delay_us(10);

    Keyboard.Keys.Bits.Lock =
        HAL_GPIO_ReadPin(key_out1_GPIO_Port, key_out1_Pin);

    Keyboard.Keys.Bits.OnOff =
        HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin);

    Keyboard.Keys.Bits.OCP =
        HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin);

    Keyboard.Keys.Bits.OVP =
        HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin);

    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_RESET);

    //----------------------------------------------------------------
    // IN3
    //----------------------------------------------------------------
    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_SET);

    // HAL_Delay(1);
    // delay_us(10);

    Keyboard.Keys.Bits.LeftArrow =
        HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin);

    Keyboard.Keys.Bits.RightArrow =
        HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin);

    Keyboard.Keys.Bits.VoltageCurrent =
        HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin);

    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_RESET);

    //----------------------------------------------------------------
    // Rotary encoder read
    //----------------------------------------------------------------

    //----------------------------------------------------------------
    // Rotary encoder read
    //----------------------------------------------------------------

    Keyboard.DialValue = 0;

    // Read encoder pins
    uint8_t B =
        (HAL_GPIO_ReadPin(BKeyRight_GPIO_Port, BKeyRight_Pin) == GPIO_PIN_RESET);

    uint8_t A =
        (HAL_GPIO_ReadPin(BKeyLeft_GPIO_Port, BKeyLeft_Pin) == GPIO_PIN_RESET);

    // Build current state
    uint8_t currentState = (A << 1) | B;

    // Ignore repeated states
    if(currentState != DialPrevState)
    {
        switch(DialStep)
        {
        //--------------------------------------------------------
        // Waiting for start
        //--------------------------------------------------------
        case 0:

            if((DialPrevState == 0b00) && (currentState == 0b10))
            {
                DialDirection = 1;
                DialStep = 1;
            }
            else if((DialPrevState == 0b00) && (currentState == 0b01))
            {
                DialDirection = -1;
                DialStep = 1;
            }

            break;

        //--------------------------------------------------------
        // Second state must be 11
        //--------------------------------------------------------
        case 1:

            if(currentState == 0b11)
            {
                DialStep = 2;
            }
            else
            {
                DialStep = 0;
                DialDirection = 0;
            }

            break;

        //--------------------------------------------------------
        // Third state
        //--------------------------------------------------------
        case 2:

            if((DialDirection == 1) && (currentState == 0b01))
            {
                DialStep = 3;
            }
            else if((DialDirection == -1) && (currentState == 0b10))
            {
                DialStep = 3;
            }
            else
            {
                DialStep = 0;
                DialDirection = 0;
            }

            break;

        //--------------------------------------------------------
        // Final state must return to 00
        //--------------------------------------------------------
        case 3:

            if(currentState == 0b00)
            {
                Keyboard.DialValue = DialDirection;
            }

            DialStep = 0;
            DialDirection = 0;

            break;
        }

        DialPrevState = currentState;
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
void Keyboard_VoltageAdjust()
{
    uint32_t multiplier = 0;
    uint32_t digit_1 = 0;
    uint32_t digit_2 = 0;
    uint32_t digit_3 = 0;
    uint32_t digit_4 = 0;

    if(actualData.Voltage < 10000)
    {
        multiplier = 1000;
    }
    else if(actualData.Voltage < 100000)
    {
        multiplier = 10000;
    }
    else if(actualData.Voltage < 1000000)
    {
        multiplier = 100000;
    }
    else
    {
        multiplier = 1000000;
    }

    digit_1 = multiplier;
    digit_2 = multiplier / 10;
    digit_3 = multiplier / 100;
    digit_4 = multiplier / 1000;

    if(actualData.Voltage < VOLTAGE_LIMIT_SUPERIOR && Keyboard.DialValue > 0)
    {
        if(display.blink_index == 1)
        {
            actualData.Voltage += digit_1;
        }
        else if(display.blink_index == 2)
        {
            actualData.Voltage += digit_2;
        }
        else if(display.blink_index == 3)
        {
            actualData.Voltage += digit_3;
        }
        else if(display.blink_index == 4)
        {
            actualData.Voltage += digit_4;
        }
    }
    else if(actualData.Voltage > VOLTAGE_LIMIT_INFERIOR && Keyboard.DialValue < 0)
    {
        if(display.blink_index == 1)
        {
            actualData.Voltage -= digit_1;
        }
        else if(display.blink_index == 2)
        {
            actualData.Voltage -= digit_2;
        }
        else if(display.blink_index == 3)
        {
            actualData.Voltage -= digit_3;
        }
        else if(display.blink_index == 4)
        {
            actualData.Voltage -= digit_4;
        }
    }

    Keyboard.DialValue = 0;

    if(actualData.Voltage > VOLTAGE_LIMIT_SUPERIOR)
    {
        actualData.Voltage = VOLTAGE_LIMIT_SUPERIOR;
    }
    else if(actualData.Voltage < VOLTAGE_LIMIT_INFERIOR)
    {
        actualData.Voltage = VOLTAGE_LIMIT_INFERIOR;
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
void Keyboard_CurrentAdjust()
{
    uint32_t multiplier = 0;
    uint32_t digit_1 = 0;
    uint32_t digit_2 = 0;
    uint32_t digit_3 = 0;
    uint32_t digit_4 = 0;

    if(actualData.Current < 10000)
    {
        multiplier = 1000;
    }
    else if(actualData.Current < 100000)
    {
        multiplier = 10000;
    }
    else if(actualData.Current < 1000000)
    {
        multiplier = 100000;
    }
    else
    {
        multiplier = 1000000;
    }

    digit_1 = multiplier;
    digit_2 = multiplier / 10;
    digit_3 = multiplier / 100;
    digit_4 = multiplier / 1000;

    if(actualData.Current < CURRENT_LIMIT_SUPERIOR && Keyboard.DialValue > 0)
    {
        if(display.blink_index == 1)
        {
            actualData.Current += digit_1;
        }
        else if(display.blink_index == 2)
        {
            actualData.Current += digit_2;
        }
        else if(display.blink_index == 3)
        {
            actualData.Current += digit_3;
        }
        else if(display.blink_index == 4)
        {
            actualData.Current += digit_4;
        }
    }
    else if(actualData.Current > CURRENT_LIMIT_INFERIOR && Keyboard.DialValue < 0)
    {
        if(display.blink_index == 1)
        {
            actualData.Current -= digit_1;
        }
        else if(display.blink_index == 2)
        {
            actualData.Current -= digit_2;
        }
        else if(display.blink_index == 3)
        {
            actualData.Current -= digit_3;
        }
        else if(display.blink_index == 4)
        {
            actualData.Current -= digit_4;
        }
    }

    Keyboard.DialValue = 0;

    if(actualData.Current > CURRENT_LIMIT_SUPERIOR)
    {
        actualData.Current = CURRENT_LIMIT_SUPERIOR;
    }
    else if(actualData.Current < CURRENT_LIMIT_INFERIOR)
    {
        actualData.Current = CURRENT_LIMIT_INFERIOR;
    }
}
