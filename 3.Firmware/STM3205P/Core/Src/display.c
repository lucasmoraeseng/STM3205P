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
void display_Init(Display_t *obj,GPIO_TypeDef *SD_Port, uint16_t SD_Pin,
                      GPIO_TypeDef *RCLK_Port, uint16_t RCLK_Pin,
                      GPIO_TypeDef *SRCLK_Port, uint16_t SRCLK_Pin)
{
    HAL_74HC595_Init(&obj->hAL_74HC595,
                      SD_Port, SD_Pin,
                      RCLK_Port, RCLK_Pin,
                      SRCLK_Port, SRCLK_Pin,
                      2);

}


// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_WriteBus(uint16_t data)
// {
//     // Ensure the latch pin is LOW before starting the transmission
//     HAL_GPIO_WritePin(STCP2_GPIO_Port, STCP2_Pin, GPIO_PIN_RESET);

//     // Send 16 bits (MSB first)
//     for (int8_t i = 15; i >= 0; i--)
//     {
//         // Set the data pin according to the current bit
//         if (data & (1 << i))
//             HAL_GPIO_WritePin(SD2_GPIO_Port, SD2_Pin, GPIO_PIN_SET);
//         else
//             HAL_GPIO_WritePin(SD2_GPIO_Port, SD2_Pin, GPIO_PIN_RESET);

//         // Optional delay to control clock speed
//         // Delay_us(1);

//         // Generate clock pulse (shift register clock)
//         HAL_GPIO_WritePin(SHCP2_GPIO_Port, SHCP2_Pin, GPIO_PIN_SET);
//         // Delay_us(1); // Optional: adjust pulse width
//         HAL_GPIO_WritePin(SHCP2_GPIO_Port, SHCP2_Pin, GPIO_PIN_RESET);
//     }

//     // Latch pulse to transfer the shifted bits to the output register
//     HAL_GPIO_WritePin(STCP2_GPIO_Port, STCP2_Pin, GPIO_PIN_SET);
//     // Delay_us(1);
//     HAL_GPIO_WritePin(STCP2_GPIO_Port, STCP2_Pin, GPIO_PIN_RESET);
// }

// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_EnableDisplay(uint8_t display)
// {
// 	if(display == 1)
// 	{
//         HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_SET);
// 	}

// 	if(display == 2)
// 	{
//         HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_SET);
// 	}

// 	if(display == 3)
// 	{
//         HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_SET);
// 	}

// 	if(display == 4)
// 	{
//         HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_SET);
// 	}

// 	if(display == 5)
// 	{
//         HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_SET);
// 	}
// }

// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_DisableDisplay(uint8_t display)
// {
// 	if(display == 1)
// 	{
//         HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_RESET);
// 	}

// 	if(display == 2)
// 	{
//         HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_RESET);
// 	}

// 	if(display == 3)
// 	{
//         HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_RESET);
// 	}

// 	if(display == 4)
// 	{
//         HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_RESET);
// 	}

// 	if(display == 5)
// 	{
//         HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_RESET);
// 	}
// }

// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_DisableAll()
// {
// 	HAL_GPIO_WritePin(display1_GPIO_Port, display1_Pin, GPIO_PIN_RESET);
// 	HAL_GPIO_WritePin(display2_GPIO_Port, display2_Pin, GPIO_PIN_RESET);
// 	HAL_GPIO_WritePin(display3_GPIO_Port, display3_Pin, GPIO_PIN_RESET);
// 	HAL_GPIO_WritePin(display4_GPIO_Port, display4_Pin, GPIO_PIN_RESET);
// 	HAL_GPIO_WritePin(display5_GPIO_Port, display5_Pin, GPIO_PIN_RESET);
// }


// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_DisplayNext()
// {
// 	if(disp_cnt ==0)
// 		disp_cnt = 1;

// 	display_DisableAll();
// 	display_WriteBus(display_data[disp_cnt-1]);
// 	display_EnableDisplay(disp_cnt);

// 	disp_cnt ++;

// 	if(disp_cnt>5)
// 		disp_cnt = 1;
// }

// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_PrepareData(float voltage, float current)
// {	
// 	Digits4_t v_digits;
// 	Digits4_t c_digits;
// 	uint8_t v_dot[4] = {0,0,0,0};
// 	uint8_t c_dot[4] = {0,0,0,0};

// 	display_Float2Digits(voltage, &v_digits);
// 	display_Float2Digits(current, &c_digits);

// 	if(v_digits.dot_position)
// 	{
// 		v_dot[v_digits.dot_position - 1] = 1;
// 	}

// 	if(c_digits.dot_position)
// 	{
// 		c_dot[c_digits.dot_position - 1] = 1;
// 	}


// 	display_SetNumberOnMemory(v_digits.d1, v_dot[0], c_digits.d1, c_dot[0], 1);
// 	display_SetNumberOnMemory(v_digits.d2, v_dot[1], c_digits.d2, c_dot[1], 2);
// 	display_SetNumberOnMemory(v_digits.d3, v_dot[2], c_digits.d3, c_dot[2], 3);
// 	display_SetNumberOnMemory(v_digits.d4, v_dot[3], c_digits.d4, c_dot[3], 4);
    
// }

// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_SetCharOnMemory(uint8_t bus_high, uint8_t bus_low, uint8_t display)
// {
// 	uint16_t data = (bus_high << 8 ) | bus_low;
// 	if(display == 1)
// 	{
// 		display_data[1] = data;
// 	}

// 	if(display == 2)
// 	{
// 		display_data[0] = data;
// 	}

// 	if(display == 3)
// 	{
// 		display_data[3] = data;
// 	}

// 	if(display == 4)
// 	{
// 		display_data[4] = data;
// 	}
// }

// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_SetNumberOnMemory(uint8_t bus_high, uint8_t dot_high, uint8_t bus_low, uint8_t dot_low, uint8_t display)
// {
// 	uint16_t dataH = display_GetNumberData(bus_high, 1);
// 	uint16_t dataL = display_GetNumberData(bus_low, 2);

// 	if(dot_high)
// 	{
// 		dataH |= 0x04;
// 	}

// 	if(dot_low)
// 	{
// 		dataL |= 0x04;
// 	}

// 	uint16_t data = (dataH << 8 ) | dataL;

// 	if(display == 1)
// 	{
// 		display_data[1] = data;
// 	}

// 	if(display == 2)
// 	{
// 		display_data[0] = data;
// 	}

// 	if(display == 3)
// 	{
// 		display_data[3] = data;
// 	}

// 	if(display == 4)
// 	{
// 		display_data[4] = data;
// 	}
// }
// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// uint8_t display_GetNumberData(uint8_t number, uint8_t display)
// {
// 	switch(number)
// 	{
// 		case 0:
// 			if(display == 1) return disp1_0;
// 			if(display == 2) return disp2_0;
// 			break;
// 		case 1:
// 			if(display == 1) return disp1_1;	
// 			if(display == 2) return disp2_1;
// 			break;
// 		case 2:
// 			if(display == 1) return disp1_2;
// 			if(display == 2) return disp2_2;
// 			break;
// 		case 3:
// 			if(display == 1) return disp1_3;	
// 			if(display == 2) return disp2_3;
// 			break;
// 		case 4:
// 			if(display == 1) return disp1_4;
// 			if(display == 2) return disp2_4;
// 			break;
// 		case 5:
// 			if(display == 1) return disp1_5;	
// 			if(display == 2) return disp2_5;
// 			break;
// 		case 6:
// 			if(display == 1) return disp1_6;
// 			if(display == 2) return disp2_6;
// 			break;
// 		case 7:
// 			if(display == 1) return disp1_7;	
// 			if(display == 2) return disp2_7;
// 			break;
// 		case 8:
// 			if(display == 1) return disp1_8;
// 			if(display == 2) return disp2_8;
// 			break;
// 		case 9:
// 			if(display == 1) return disp1_9;	
// 			if(display == 2) return disp2_9;
// 			break;
// 	}

// 	return 0x00;
// }



// /* ###################################################################
//  * Function:
//  * Author: Moraes, L.
//  * Date: Oct 6, 2025
//  * Revision: 1.0
//  * --------------------
//  * Initialize struct of current sensor, calculating it's parameters
//  *
//  *  arg1: input arg1
//  *
//  *  arg2: input arg2
//  *
//  *  returns: void
//  *
//  *
// ###################################################################*/
// void display_Float2Digits(float value, Digits4_t *digits)
// {
// 	uint16_t value_int = 0;
// 	uint16_t temp_value = 0;

// 	if(value < 10)
// 	{
// 		value_int = (uint16_t)(roundf(value * 1000));
// 	}
// 	else if(value < 100)
// 	{
// 		value_int = (uint16_t)(roundf(value * 100));
// 	}
// 	else if(value < 1000)
// 	{
// 		value_int = (uint16_t)(roundf(value * 10));
// 	}
// 	else
// 	{
// 		value_int = (uint16_t)(roundf(value * 1));
// 	}

// 	digits->d1 = (value_int / 1000) % 10;
// 	temp_value = digits->d1 * 1000;
// 	digits->d2 = ((value_int - temp_value) / 100) % 10;
// 	temp_value += digits->d2 * 100;
// 	digits->d3 = ((value_int - temp_value) / 10) % 10;
// 	temp_value += digits->d3 * 10;
// 	digits->d4 = (value_int - temp_value) % 10;

// 	if(value < 10)
// 	{
// 		digits->dot_position = 1;
// 	}
// 	else if(value < 100)
// 	{
// 		digits->dot_position = 2;
// 	}
// 	else if(value < 1000)
// 	{
// 		digits->dot_position = 3;
// 	}
// 	else
// 	{
// 		digits->dot_position = 0;
// 	}
// }



