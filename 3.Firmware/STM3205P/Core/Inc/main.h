/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BKeyLeft_Pin GPIO_PIN_13
#define BKeyLeft_GPIO_Port GPIOC
#define key_out4_Pin GPIO_PIN_14
#define key_out4_GPIO_Port GPIOC
#define key_out2_Pin GPIO_PIN_15
#define key_out2_GPIO_Port GPIOC
#define key_in3_Pin GPIO_PIN_0
#define key_in3_GPIO_Port GPIOA
#define AD1F_Pin GPIO_PIN_1
#define AD1F_GPIO_Port GPIOA
#define AD2F_Pin GPIO_PIN_2
#define AD2F_GPIO_Port GPIOA
#define TEMP_MONITOR_Pin GPIO_PIN_3
#define TEMP_MONITOR_GPIO_Port GPIOA
#define DAC_CS1_Pin GPIO_PIN_4
#define DAC_CS1_GPIO_Port GPIOA
#define DAC_SCLK_Pin GPIO_PIN_5
#define DAC_SCLK_GPIO_Port GPIOA
#define DAC_CS0_Pin GPIO_PIN_6
#define DAC_CS0_GPIO_Port GPIOA
#define DAC_SPI_Pin GPIO_PIN_7
#define DAC_SPI_GPIO_Port GPIOA
#define OCP_Pin GPIO_PIN_0
#define OCP_GPIO_Port GPIOB
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
#define FAN_Pin GPIO_PIN_11
#define FAN_GPIO_Port GPIOA
#define BY_Pin GPIO_PIN_12
#define BY_GPIO_Port GPIOA
#define REL1_Pin GPIO_PIN_15
#define REL1_GPIO_Port GPIOA
#define REL3_Pin GPIO_PIN_3
#define REL3_GPIO_Port GPIOB
#define REL2_Pin GPIO_PIN_4
#define REL2_GPIO_Port GPIOB
#define key_in1_Pin GPIO_PIN_5
#define key_in1_GPIO_Port GPIOB
#define key_in2_Pin GPIO_PIN_6
#define key_in2_GPIO_Port GPIOB
#define key_out1_Pin GPIO_PIN_7
#define key_out1_GPIO_Port GPIOB
#define key_out3_Pin GPIO_PIN_8
#define key_out3_GPIO_Port GPIOB
#define BKeyRight_Pin GPIO_PIN_9
#define BKeyRight_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
