/* ###################################################################
**     Filename    : display.
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
#include <math.h>
#include <stdint.h>

#include "HAL_74HC595.h"
#include "data_types.h"
#include "led_indicator.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------
#define STCP2_Pin GPIO_PIN_1
#define STCP2_GPIO_Port GPIOB
#define SHCP2_Pin GPIO_PIN_10
#define SHCP2_GPIO_Port GPIOB
#define SD2_Pin GPIO_PIN_11
#define SD2_GPIO_Port GPIOB
#define display1_Pin GPIO_PIN_12
#define display1_GPIO_Port GPIOB
#define display2_Pin GPIO_PIN_13
#define display2_GPIO_Port GPIOB
#define display3_Pin GPIO_PIN_14
#define display3_GPIO_Port GPIOB
#define display4_Pin GPIO_PIN_15
#define display4_GPIO_Port GPIOB
#define display5_Pin GPIO_PIN_8
#define display5_GPIO_Port GPIOA

// Display 1
#define disp1_0 0xFA
#define disp1_1 0x22
#define disp1_2 0xB9
#define disp1_3 0xAB
#define disp1_4 0x63
#define disp1_5 0xCB
#define disp1_6 0xDB
#define disp1_7 0xA2
#define disp1_8 0xFB
#define disp1_9 0xEB
#define disp1_A 0xF3
#define disp1_B 0x5B
#define disp1_C 0xD8
#define disp1_D 0x3B
#define disp1_E 0xD9
#define disp1_F 0xD1
#define disp1_H 0x73
#define disp1_L 0x58
#define disp1_P 0xF1
#define disp1_U 0x7A
#define disp1_n 0x13
#define disp1_o 0x1B
#define disp1_r 0x11
#define disp1_t 0x59
#define disp1_y 0x6B
#define disp1_dash 0x01
#define disp1_underscore 0x08
#define disp1_equal 0x09
#define disp1_degree 0xE1
#define disp1_clear 0x00

// Display 2
#define disp2_0 0xFA
#define disp2_1 0x82
#define disp2_2 0xB9
#define disp2_3 0xAB
#define disp2_4 0xC3
#define disp2_5 0x6B
#define disp2_6 0x7B
#define disp2_7 0xA2
#define disp2_8 0xFB
#define disp2_9 0xEB
#define disp2_A 0xF3
#define disp2_B 0x5B
#define disp2_C 0x78
#define disp2_D 0x9B
#define disp2_E 0x79
#define disp2_F 0x71
#define disp2_H 0xD3
#define disp2_L 0x58
#define disp2_P 0xF1
#define disp2_U 0xDA
#define disp2_n 0x13
#define disp2_o 0x1B
#define disp2_r 0x11
#define disp2_t 0x59
#define disp2_y 0xCB
#define disp2_dash 0x1
#define disp2_underscore 0x8
#define disp2_equal 0x9
#define disp2_degree 0xE1
#define disp2_clear 0x0

#define disp_dot 0x04

//--------------------------------------------------------------------
// Typedef enum
//--------------------------------------------------------------------
typedef enum
{
    BUZZER_TONE_OFF = 0,

    // Octave 3
    BUZZER_TONE_C3 = 214,  // 130.81 Hz
    BUZZER_TONE_CS3 = 227, // 138.59 Hz
    BUZZER_TONE_D3 = 240,  // 146.83 Hz
    BUZZER_TONE_DS3 = 255, // 155.56 Hz
    BUZZER_TONE_E3 = 270,  // 164.81 Hz
    BUZZER_TONE_F3 = 286,  // 174.61 Hz
    BUZZER_TONE_FS3 = 303, // 185.00 Hz
    BUZZER_TONE_G3 = 321,  // 196.00 Hz
    BUZZER_TONE_GS3 = 340, // 207.65 Hz
    BUZZER_TONE_A3 = 360,  // 220.00 Hz
    BUZZER_TONE_AS3 = 381, // 233.08 Hz
    BUZZER_TONE_B3 = 404,  // 246.94 Hz

    // Octave 4
    BUZZER_TONE_C4 = 429,  // 261.63 Hz
    BUZZER_TONE_CS4 = 454, // 277.18 Hz
    BUZZER_TONE_D4 = 481,  // 293.66 Hz
    BUZZER_TONE_DS4 = 510, // 311.13 Hz
    BUZZER_TONE_E4 = 540,  // 329.63 Hz
    BUZZER_TONE_F4 = 572,  // 349.23 Hz
    BUZZER_TONE_FS4 = 606, // 369.99 Hz
    BUZZER_TONE_G4 = 642,  // 392.00 Hz
    BUZZER_TONE_GS4 = 680, // 415.30 Hz
    BUZZER_TONE_A4 = 721,  // 440.00 Hz
    BUZZER_TONE_AS4 = 763, // 466.16 Hz
    BUZZER_TONE_B4 = 809,  // 493.88 Hz

    // Octave 5
    BUZZER_TONE_C5 = 858,   // 523.25 Hz
    BUZZER_TONE_CS5 = 909,  // 554.37 Hz
    BUZZER_TONE_D5 = 962,   // 587.33 Hz
    BUZZER_TONE_DS5 = 1020, // 622.25 Hz
    BUZZER_TONE_E5 = 1080,  // 659.25 Hz
    BUZZER_TONE_F5 = 1144,  // 698.46 Hz
    BUZZER_TONE_FS5 = 1212, // 739.99 Hz
    BUZZER_TONE_G5 = 1285,  // 783.99 Hz
    BUZZER_TONE_GS5 = 1360, // 830.61 Hz
    BUZZER_TONE_A5 = 1442,  // 880.00 Hz
    BUZZER_TONE_AS5 = 1527, // 932.33 Hz
    BUZZER_TONE_B5 = 1618,  // 987.77 Hz

    // Octave 6
    BUZZER_TONE_C6 = 1715, // 1046.50 Hz
    BUZZER_TONE_D6 = 1925, // 1174.66 Hz
    BUZZER_TONE_E6 = 2160, // 1318.51 Hz
    BUZZER_TONE_F6 = 2288, // 1396.91 Hz
    BUZZER_TONE_G6 = 2570, // 1567.98 Hz
    BUZZER_TONE_A6 = 2884, // 1760.00 Hz
    BUZZER_TONE_B6 = 3237  // 1975.53 Hz

} BuzzerTone_t;

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
// Structure to hold separated digits
typedef struct
{
    uint8_t d1;     // Thousands / tens / int part
    uint8_t d1_dot; // Dot for d1
    uint8_t d2;     // Hundreds / units
    uint8_t d2_dot; // Dot for d2
    uint8_t d3;     // Tens / tenths
    uint8_t d3_dot; // Dot for d3
    uint8_t d4;     // Units / hundredths
    uint8_t d4_dot; // Dot for d4
} Digits4_t;

typedef struct
{
    Digits4_t display1;
    Digits4_t display2;
    HAL_74HC595_t hAL_74HC595;
    uint8_t disp_cnt;
    uint8_t blink_display; // 0 - none; 1 - display1; 2 - display2
    uint8_t blink_state;   // 0 - off; 1 - on
    uint8_t blink_index;
    LedIndicator_t ledOVP;
    LedIndicator_t ledOCP;
    LedIndicator_t ledCC;
    LedIndicator_t ledCV;
    LedIndicator_t ledOUT;
    LedIndicator_t ledM1;
    LedIndicator_t ledM2;
    LedIndicator_t ledM3;
    LedIndicator_t ledM4;
    LedIndicator_t ledM5;
    uint16_t frame_cnt;
    uint8_t beep;
    uint32_t beep_cnt;
    uint32_t beep_duration;
    uint32_t beep_phase;
    uint32_t beep_increment;
} Display_t;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------
extern void Display_Init(Display_t *obj);
extern void Display_WriteBus(uint16_t data);
extern void Display_EnableDisplay(uint8_t dp);
extern void Display_DisableDisplay(uint8_t dp);
extern void Display_DisableAll();
// extern void display_DisplayNext();
extern void Display_PrepareDataFloat(Display_t *obj, float voltage, float current);
extern void Display_PrepareDataACCX3(Display_t *obj, settings_accx3_t data);
// extern void display_SetCharOnMemory(uint8_t bus_high, uint8_t bus_low, uint8_t display);
// extern void display_SetNumberOnMemory(uint8_t bus_high, uint8_t dot_high, uint8_t bus_low, uint8_t dot_low, uint8_t display);
extern uint8_t Display_GetNumberData(uint8_t number, uint8_t dp);
extern void Display_Float2Digits(float value, Digits4_t *digits);
extern void Display_ACCX32Digits(accx3_t value, Digits4_t *digits);
extern void Display_Update(Display_t *obj);
extern void Display_ClearMemoryLeds(Display_t *obj);

extern void Buzzer_Play(Display_t *obj, BuzzerTone_t note, uint32_t duration_ms);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------
extern HAL_74HC595_t display_obj;
extern settings_accx3_t actualData;
extern settings_accx3_t measuredData;

extern Display_t display;
extern uint32_t frameCounter;

#endif /* SRC_DISPLAY_H_ */
