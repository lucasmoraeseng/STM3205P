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
HAL_74HC595_t display_obj;
settings_accx3_t actualData;
Display_t display;

uint32_t frameCounter = 0;

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
void Display_Init(Display_t *obj)
{
    HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_RESET);

    HAL_74HC595_Init(&obj->hAL_74HC595,
                     SD2_GPIO_Port, SD2_Pin,
                     STCP2_GPIO_Port, STCP2_Pin,
                     SHCP2_GPIO_Port, SHCP2_Pin,
                     2);

    uint8_t data[2] = {0x00, 0x00};

    HAL_74HC595_WriteData(&obj->hAL_74HC595, data);
    obj->beep_cnt = 0;
    obj->beep = 0;

    LedIndicator_Init(&obj->ledOVP);
    LedIndicator_Init(&obj->ledOCP);
    LedIndicator_Init(&obj->ledCC);
    LedIndicator_Init(&obj->ledCV);
    LedIndicator_Init(&obj->ledOUT);
    LedIndicator_Init(&obj->ledM1);
    LedIndicator_Init(&obj->ledM2);
    LedIndicator_Init(&obj->ledM3);
    LedIndicator_Init(&obj->ledM4);
    LedIndicator_Init(&obj->ledM5);
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
void Display_WriteBus(uint16_t data)
{
    // Ensure the latch pin is LOW before starting the transmission
    HAL_GPIO_WritePin(STCP2_GPIO_Port, STCP2_Pin, GPIO_PIN_RESET);

    // Send 16 bits (MSB first)
    for(int8_t i = 15; i >= 0; i--)
    {
        // Set the data pin according to the current bit
        if(data & (1 << i))
            HAL_GPIO_WritePin(SD2_GPIO_Port, SD2_Pin, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(SD2_GPIO_Port, SD2_Pin, GPIO_PIN_RESET);

        // Optional delay to control clock speed
        // Delay_us(1);

        // Generate clock pulse (shift register clock)
        HAL_GPIO_WritePin(SHCP2_GPIO_Port, SHCP2_Pin, GPIO_PIN_SET);
        // Delay_us(1); // Optional: adjust pulse width
        HAL_GPIO_WritePin(SHCP2_GPIO_Port, SHCP2_Pin, GPIO_PIN_RESET);
    }

    // Latch pulse to transfer the shifted bits to the output register
    HAL_GPIO_WritePin(STCP2_GPIO_Port, STCP2_Pin, GPIO_PIN_SET);
    // Delay_us(1);
    HAL_GPIO_WritePin(STCP2_GPIO_Port, STCP2_Pin, GPIO_PIN_RESET);
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
void Display_EnableDisplay(uint8_t dp)
{
    if(dp == 1)
    {
        HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_SET);
    }

    if(dp == 2)
    {
        HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_SET);
    }

    if(dp == 3)
    {
        HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_SET);
    }

    if(dp == 4)
    {
        HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_SET);
    }

    if(dp == 5)
    {
        HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_SET);
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
void Display_DisableDisplay(uint8_t dp)
{
    if(dp == 1)
    {
        HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_RESET);
    }

    if(dp == 2)
    {
        HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_RESET);
    }

    if(dp == 3)
    {
        HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_RESET);
    }

    if(dp == 4)
    {
        HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_RESET);
    }

    if(dp == 5)
    {
        HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_RESET);
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
void Display_DisableAll()
{
    HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_RESET);
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
// void display_DisplayNext(Display_t *obj)
// {
//     if(obj->disp_cnt == 0)
//         obj->disp_cnt = 1;

//     display_DisableAll();
//     display_WriteBus(obj->display_data[obj->disp_cnt - 1]);
//     display_EnableDisplay(obj->disp_cnt);

//     obj->disp_cnt++;

//     if(obj->disp_cnt > 5)
//         obj->disp_cnt = 1;
// }

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
void Display_PrepareDataFloat(Display_t *obj, float voltage, float current)
{
    Digits4_t v_digits;
    Digits4_t c_digits;
    // uint8_t v_dot[4] = {0, 0, 0, 0};
    // uint8_t c_dot[4] = {0, 0, 0, 0};

    Display_Float2Digits(voltage, &v_digits);
    Display_Float2Digits(current, &c_digits);

    obj->display1 = v_digits;
    obj->display2 = c_digits;
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
void Display_PrepareDataACCX3(Display_t *obj, settings_accx3_t data)
{
    Digits4_t v_digits;
    Digits4_t c_digits;
    // uint8_t v_dot[4] = {0, 0, 0, 0};
    // uint8_t c_dot[4] = {0, 0, 0, 0};

    Display_ACCX32Digits(data.Voltage, &v_digits);
    Display_ACCX32Digits(data.Current, &c_digits);

    obj->display1 = v_digits;
    obj->display2 = c_digits;
    LedIndicator_WriteValue(&obj->ledOVP, data.OVP);
    LedIndicator_WriteValue(&obj->ledOCP, data.OCP);
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
// void Display_SetCharOnMemory(Display_t *obj, uint8_t bus_high, uint8_t bus_low, uint8_t display)
// {
//     uint16_t data = (bus_high << 8) | bus_low;
//     if(display == 1)
//     {
//         obj->display_data[1] = data;
//     }

//     if(display == 2)
//     {
//         display_data[0] = data;
//     }

//     if(display == 3)
//     {
//         display_data[3] = data;
//     }

//     if(display == 4)
//     {
//         display_data[4] = data;
//     }
// }

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
// void Display_SetNumberOnMemory(uint8_t bus_high, uint8_t dot_high, uint8_t bus_low, uint8_t dot_low, uint8_t display)
// {
//     uint16_t dataH = display_GetNumberData(bus_high, 1);
//     uint16_t dataL = display_GetNumberData(bus_low, 2);

//     if(dot_high)
//     {
//         dataH |= 0x04;
//     }

//     if(dot_low)
//     {
//         dataL |= 0x04;
//     }

//     uint16_t data = (dataH << 8) | dataL;

//     if(display == 1)
//     {
//         display_data[1] = data;
//     }

//     if(display == 2)
//     {
//         display_data[2] = data;
//     }

//     if(display == 3)
//     {
//         display_data[3] = data;
//     }

//     if(display == 4)
//     {
//         display_data[4] = data;
//     }
// }

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
uint8_t Display_GetNumberData(uint8_t number, uint8_t dp)
{
    switch(number)
    {
    case 0:
        if(dp == 1)
            return disp1_0;
        if(dp == 2)
            return disp2_0;
        break;
    case 1:
        if(dp == 1)
            return disp1_1;
        if(dp == 2)
            return disp2_1;
        break;
    case 2:
        if(dp == 1)
            return disp1_2;
        if(dp == 2)
            return disp2_2;
        break;
    case 3:
        if(dp == 1)
            return disp1_3;
        if(dp == 2)
            return disp2_3;
        break;
    case 4:
        if(dp == 1)
            return disp1_4;
        if(dp == 2)
            return disp2_4;
        break;
    case 5:
        if(dp == 1)
            return disp1_5;
        if(dp == 2)
            return disp2_5;
        break;
    case 6:
        if(dp == 1)
            return disp1_6;
        if(dp == 2)
            return disp2_6;
        break;
    case 7:
        if(dp == 1)
            return disp1_7;
        if(dp == 2)
            return disp2_7;
        break;
    case 8:
        if(dp == 1)
            return disp1_8;
        if(dp == 2)
            return disp2_8;
        break;
    case 9:
        if(dp == 1)
            return disp1_9;
        if(dp == 2)
            return disp2_9;
        break;
    }

    return 0x00;
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
void Display_Float2Digits(float value, Digits4_t *digits)
{
    uint16_t value_int = 0;
    uint16_t temp_value = 0;

    if(value < 10)
    {
        value_int = (uint16_t)(roundf(value * 1000));
    }
    else if(value < 100)
    {
        value_int = (uint16_t)(roundf(value * 100));
    }
    else if(value < 1000)
    {
        value_int = (uint16_t)(roundf(value * 10));
    }
    else
    {
        value_int = (uint16_t)(roundf(value * 1));
    }

    digits->d1 = (value_int / 1000) % 10;
    temp_value = digits->d1 * 1000;
    digits->d2 = ((value_int - temp_value) / 100) % 10;
    temp_value += digits->d2 * 100;
    digits->d3 = ((value_int - temp_value) / 10) % 10;
    temp_value += digits->d3 * 10;
    digits->d4 = (value_int - temp_value) % 10;

    digits->d1_dot = 0;
    digits->d2_dot = 0;
    digits->d3_dot = 0;
    digits->d4_dot = 0;

    if(value < 10)
    {
        digits->d1_dot = 1;
    }
    else if(value < 100)
    {
        digits->d2_dot = 1;
    }
    else if(value < 1000)
    {
        digits->d3_dot = 1;
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
void Display_ACCX32Digits(accx3_t value, Digits4_t *digits)
{
    uint32_t value_int;
    uint32_t temp_value = 0;

    // Convert ACCX3 to display value
    if(value < 10000) // 0.000 ~ 9.999
    {
        value_int = value;
    }
    else if(value < 100000) // 10.00 ~ 99.99
    {
        value_int = value / 10;
    }
    else if(value < 1000000) // 100.0 ~ 999.9
    {
        value_int = value / 100;
    }
    else // >= 1000
    {
        value_int = value / 1000;
    }

    digits->d1 = (value_int / 1000) % 10;
    temp_value = digits->d1 * 1000;

    digits->d2 = ((value_int - temp_value) / 100) % 10;
    temp_value += digits->d2 * 100;

    digits->d3 = ((value_int - temp_value) / 10) % 10;
    temp_value += digits->d3 * 10;

    digits->d4 = (value_int - temp_value) % 10;

    digits->d1_dot = 0;
    digits->d2_dot = 0;
    digits->d3_dot = 0;
    digits->d4_dot = 0;

    if(value < 10000)
    {
        // X.XXX
        digits->d1_dot = 1;
    }
    else if(value < 100000)
    {
        // XX.XX
        digits->d2_dot = 1;
    }
    else if(value < 1000000)
    {
        // XXX.X
        digits->d3_dot = 1;
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
void Display_Update(Display_t *obj)
{
    uint8_t data[2] = {0x00, 0x00};

    HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_RESET);

    if(obj->disp_cnt == 0)
    {
        data[0] = Display_GetNumberData(obj->display2.d2, 2) | (obj->display2.d2_dot ? disp_dot : 0x00);
        data[1] = Display_GetNumberData(obj->display1.d2, 1) | (obj->display1.d2_dot ? disp_dot : 0x00);

        if(obj->blink_index == 2)
        {
            if(obj->blink_display == 1)
                data[0] = obj->blink_state ? 0x00 : data[0];
            else if(obj->blink_display == 2)
                data[1] = obj->blink_state ? 0x00 : data[1];
        }

        HAL_74HC595_WriteData(&obj->hAL_74HC595, data);
        HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_SET);
    }
    else if(obj->disp_cnt == 1)
    {
        data[0] = Display_GetNumberData(obj->display2.d1, 2) | (obj->display2.d1_dot ? disp_dot : 0x00);
        data[1] = Display_GetNumberData(obj->display1.d1, 1) | (obj->display1.d1_dot ? disp_dot : 0x00);

        if(obj->blink_index == 1)
        {
            if(obj->blink_display == 1)
                data[0] = obj->blink_state ? 0x00 : data[0];
            else if(obj->blink_display == 2)
                data[1] = obj->blink_state ? 0x00 : data[1];
        }

        HAL_74HC595_WriteData(&obj->hAL_74HC595, data);
        HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_SET);
    }
    else if(obj->disp_cnt == 2)
    {
        data[0] = 0;
        data[1] = 0;

        // data[0] |= ((obj->ledOUT & 0x01) << 0);
        // data[0] |= ((obj->ledM5 & 0x01) << 1);
        // data[0] |= ((obj->ledM4 & 0x01) << 2);
        // data[0] |= ((obj->ledCV & 0x01) << 4);
        // data[0] |= ((obj->ledM2 & 0x01) << 7);

        // data[1] |= ((obj->ledCC & 0x01) << 0);
        // data[1] |= ((obj->ledM3 & 0x01) << 1);
        // data[1] |= ((obj->ledOCP & 0x01) << 3);
        // data[1] |= ((obj->ledOVP & 0x01) << 5);
        // data[1] |= ((obj->ledM1 & 0x01) << 7);

        data[0] |= (LedIndicator_Update(&obj->ledOUT, obj->frame_cnt) << 0);
        data[0] |= (LedIndicator_Update(&obj->ledM5, obj->frame_cnt) << 1);
        data[0] |= (LedIndicator_Update(&obj->ledM4, obj->frame_cnt) << 2);
        data[0] |= (LedIndicator_Update(&obj->ledCV, obj->frame_cnt) << 4);
        data[0] |= (LedIndicator_Update(&obj->ledM2, obj->frame_cnt) << 7);

        data[1] |= (LedIndicator_Update(&obj->ledCC, obj->frame_cnt) << 0);
        data[1] |= (LedIndicator_Update(&obj->ledM3, obj->frame_cnt) << 1);
        data[1] |= (LedIndicator_Update(&obj->ledOCP, obj->frame_cnt) << 3);
        data[1] |= (LedIndicator_Update(&obj->ledOVP, obj->frame_cnt) << 5);
        data[1] |= (LedIndicator_Update(&obj->ledM1, obj->frame_cnt) << 7);

        HAL_74HC595_WriteData(&obj->hAL_74HC595, data);
        HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_SET);
    }
    else if(obj->disp_cnt == 3)
    {
        data[0] = Display_GetNumberData(obj->display2.d3, 2) | (obj->display2.d3_dot ? disp_dot : 0x00);
        data[1] = Display_GetNumberData(obj->display1.d3, 1) | (obj->display1.d3_dot ? disp_dot : 0x00);

        if(obj->blink_index == 3)
        {
            if(obj->blink_display == 1)
                data[0] = obj->blink_state ? 0x00 : data[0];
            else if(obj->blink_display == 2)
                data[1] = obj->blink_state ? 0x00 : data[1];
        }

        HAL_74HC595_WriteData(&obj->hAL_74HC595, data);
        HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_SET);
    }
    else if(obj->disp_cnt == 4)
    {
        data[0] = Display_GetNumberData(obj->display2.d4, 2) | (obj->display2.d4_dot ? disp_dot : 0x00);
        data[1] = Display_GetNumberData(obj->display1.d4, 1) | (obj->display1.d4_dot ? disp_dot : 0x00);

        if(obj->blink_index == 4)
        {
            if(obj->blink_display == 1)
                data[0] = obj->blink_state ? 0x00 : data[0];
            else if(obj->blink_display == 2)
                data[1] = obj->blink_state ? 0x00 : data[1];
        }

        HAL_74HC595_WriteData(&obj->hAL_74HC595, data);
        HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_SET);
    }

    obj->disp_cnt++;
    if(obj->disp_cnt > 4)
    {
        obj->disp_cnt = 0;
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
void Display_ClearMemoryLeds(Display_t *obj)
{
    LedIndicator_Clear(&obj->ledOVP);
    LedIndicator_Clear(&obj->ledOCP);
    LedIndicator_Clear(&obj->ledM1);
    LedIndicator_Clear(&obj->ledM2);
    LedIndicator_Clear(&obj->ledM3);
    LedIndicator_Clear(&obj->ledM4);
    LedIndicator_Clear(&obj->ledM5);
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
void Buzzer_Play(Display_t *obj, BuzzerTone_t note, uint32_t duration_ms)
{
    obj->beep = true;
    obj->beep_cnt = 0;
    obj->beep_duration = duration_ms;

    obj->beep_phase = 0;
    obj->beep_increment = note;
}
