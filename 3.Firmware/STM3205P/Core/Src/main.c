/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
// ADC 1   -> Output Voltage Measure
// ADC 2   -> Output Current Measure
// TIM 1   -> PWM to fan control
// TIM 2   -> Periodic interrupt for display update 1ms
// TIM 3   -> Periodic interrupt for ADC Measure
// USART 1 -> Serial communication
// SPI 1   -> Communication with DAC8830

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DAC8830.h"
#include "RingBuffer.h"
#include "display.h"
#include "flash.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
Display_t display;
ADC_ChannelConfTypeDef cfgVoltageADC;
ADC_ChannelConfTypeDef cfgCurrentADC;
ADC_ChannelConfTypeDef cfgTemperatureADC;

keyboard_t Keyboard;

uint16_t frameCounter = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)
    {
    }
    else if(htim->Instance == TIM2)
    {
        display.frame_cnt++;
        if(display.frame_cnt % 512 == 0)
        {
            display.blink_state = !display.blink_state;
        }

        display_update(&display);
    }
    else if(htim->Instance == TIM3)
    {
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

    if(hadc->Instance == ADC1)
    {
        uint16_t value1 = HAL_ADC_GetValue(&hadc1);
        // RingBuffer_Put(&RBVoltage,(RBDataType) value1);
    }
    else if(hadc->Instance == ADC2)
    {
        uint16_t value2 = HAL_ADC_GetValue(&hadc2);
        // RingBuffer_Put(&RBCurrent,(RBDataType) value2);
    }
}

void PanelRead()
{
    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_RESET);

    HAL_Delay(1);

    // In1 - High
    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_SET);

    HAL_Delay(1);

    if(HAL_GPIO_ReadPin(key_out1_GPIO_Port, key_out1_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.M1 = 1;
    }
    else
    {
        Keyboard.Keys.Bits.M1 = 0;
    }

    if(HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.M4 = 1;
    }
    else
    {
        Keyboard.Keys.Bits.M4 = 0;
    }

    if(HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.M2 = 1;
    }
    else
    {
        Keyboard.Keys.Bits.M2 = 0;
    }

    if(HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.M3 = 1;
    }
    else
    {
        Keyboard.Keys.Bits.M3 = 0;
    }

    HAL_GPIO_WritePin(key_in1_GPIO_Port, key_in1_Pin, GPIO_PIN_RESET);

    // In2 - High
    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_SET);

    HAL_Delay(1);

    if(HAL_GPIO_ReadPin(key_out1_GPIO_Port, key_out1_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.Lock = 1;
    }
    else
    {
        Keyboard.Keys.Bits.Lock = 0;
    }

    if(HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.OnOff = 1;
    }
    else
    {
        Keyboard.Keys.Bits.OnOff = 0;
    }

    if(HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.OCP = 1;
    }
    else
    {
        Keyboard.Keys.Bits.OCP = 0;
    }

    if(HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.OVP = 1;
    }
    else
    {
        Keyboard.Keys.Bits.OVP = 0;
    }

    HAL_GPIO_WritePin(key_in2_GPIO_Port, key_in2_Pin, GPIO_PIN_RESET);

    // In3 - High
    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_SET);

    HAL_Delay(1);
    // if(HAL_GPIO_ReadPin(key_out1_GPIO_Port,key_out1_Pin) == GPIO_PIN_SET)
    // {
    //     Keyboard.Keys.Bits.LOCK = 1;
    // }
    // else
    // {
    //     Keyboard.Keys.Bits.LOCK = 0;
    // }

    if(HAL_GPIO_ReadPin(key_out2_GPIO_Port, key_out2_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.LeftArrow = 1;
    }
    else
    {
        Keyboard.Keys.Bits.LeftArrow = 0;
    }

    if(HAL_GPIO_ReadPin(key_out3_GPIO_Port, key_out3_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.RightArrow = 1;
    }
    else
    {
        Keyboard.Keys.Bits.RightArrow = 0;
    }

    if(HAL_GPIO_ReadPin(key_out4_GPIO_Port, key_out4_Pin) == GPIO_PIN_SET)
    {
        Keyboard.Keys.Bits.VoltageCurrent = 1;
    }
    else
    {
        Keyboard.Keys.Bits.VoltageCurrent = 0;
    }

    HAL_GPIO_WritePin(key_in3_GPIO_Port, key_in3_Pin, GPIO_PIN_RESET);
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

    /* USER CODE BEGIN 1 */

    cfgVoltageADC.Channel = ADC_CHANNEL_1;
    cfgVoltageADC.Rank = ADC_REGULAR_RANK_1;
    cfgVoltageADC.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

    cfgCurrentADC.Channel = ADC_CHANNEL_2;
    cfgCurrentADC.Rank = ADC_REGULAR_RANK_1;
    cfgCurrentADC.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

    cfgTemperatureADC.Channel = ADC_CHANNEL_3;
    cfgTemperatureADC.Rank = ADC_REGULAR_RANK_1;
    cfgTemperatureADC.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    Flash_ReadSettings(&flashData);

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */
    display_Init(&display);
    display_PrepareData(&display, flashData.memory1.Voltage, flashData.memory1.Current);

    // display.blink_display = 2;
    // display.blink_index = 1;

    // display_PrepareData(0.0f, 0.0f);

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_ADC2_Init();
    MX_TIM1_Init();
    MX_USART1_UART_Init();
    MX_TIM2_Init();
    MX_SPI1_Init();
    /* USER CODE BEGIN 2 */

    HAL_ADC_ConfigChannel(&hadc1, &cfgVoltageADC);
    HAL_ADC_ConfigChannel(&hadc2, &cfgCurrentADC);

    HAL_TIM_Base_Start_IT(&htim2); // Timer with interruption
    HAL_ADC_Start_IT(&hadc1);      // Start ADC1 with interruption
    HAL_ADC_Start_IT(&hadc2);      // Start ADC2 with interruption

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while(1)
    {
        PanelRead();

        display.ledM1 = Keyboard.Keys.Bits.M1;
        display.ledM2 = Keyboard.Keys.Bits.M2;
        display.ledM3 = Keyboard.Keys.Bits.M3;
        display.ledM4 = Keyboard.Keys.Bits.M4;
        display.ledM5 = Keyboard.Keys.Bits.LeftArrow;

        display.ledOUT = Keyboard.Keys.Bits.OnOff;
        display.ledCC = Keyboard.Keys.Bits.Lock;
        display.ledOCP = Keyboard.Keys.Bits.OCP;
        display.ledOVP = Keyboard.Keys.Bits.OVP;
        display.ledCV = Keyboard.Keys.Bits.RightArrow;

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void)
{

    /* USER CODE BEGIN ADC1_Init 0 */

    /* USER CODE END ADC1_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC1_Init 1 */

    /* USER CODE END ADC1_Init 1 */

    /** Common config
     */
    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    if(HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if(HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC1_Init 2 */

    /* USER CODE END ADC1_Init 2 */
}

/**
 * @brief ADC2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC2_Init(void)
{

    /* USER CODE BEGIN ADC2_Init 0 */

    /* USER CODE END ADC2_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC2_Init 1 */

    /* USER CODE END ADC2_Init 1 */

    /** Common config
     */
    hadc2.Instance = ADC2;
    hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc2.Init.ContinuousConvMode = DISABLE;
    hadc2.Init.DiscontinuousConvMode = DISABLE;
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc2.Init.NbrOfConversion = 1;
    if(HAL_ADC_Init(&hadc2) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if(HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC2_Init 2 */

    /* USER CODE END ADC2_Init 2 */
}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void)
{

    /* USER CODE BEGIN SPI1_Init 0 */

    /* USER CODE END SPI1_Init 0 */

    /* USER CODE BEGIN SPI1_Init 1 */

    /* USER CODE END SPI1_Init 1 */
    /* SPI1 parameter configuration*/
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_1LINE;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    if(HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN SPI1_Init 2 */

    /* USER CODE END SPI1_Init 2 */
}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void)
{

    /* USER CODE BEGIN TIM1_Init 0 */

    /* USER CODE END TIM1_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    /* USER CODE BEGIN TIM1_Init 1 */

    /* USER CODE END TIM1_Init 1 */
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 65535;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if(HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if(HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if(HAL_TIM_PWM_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if(HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if(HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        Error_Handler();
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if(HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM1_Init 2 */

    /* USER CODE END TIM1_Init 2 */
    HAL_TIM_MspPostInit(&htim1);
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 35999;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if(HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if(HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if(HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */

    /* USER CODE END TIM2_Init 2 */
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if(HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */

    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, key_in3_Pin | DAC_CS1_Pin | DAC_CS0_Pin | display5_Pin | BY_Pin | REL1_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, STCP2_Pin | SHCP2_Pin | SD2_Pin | display1_Pin | display2_Pin | display3_Pin | display4_Pin | REL3_Pin | REL2_Pin | key_in1_Pin | key_in2_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : BKeyLeft_Pin */
    GPIO_InitStruct.Pin = BKeyLeft_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(BKeyLeft_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : key_out4_Pin key_out2_Pin */
    GPIO_InitStruct.Pin = key_out4_Pin | key_out2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : key_in3_Pin display5_Pin */
    GPIO_InitStruct.Pin = key_in3_Pin | display5_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : DAC_CS1_Pin DAC_CS0_Pin BY_Pin REL1_Pin */
    GPIO_InitStruct.Pin = DAC_CS1_Pin | DAC_CS0_Pin | BY_Pin | REL1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : OCP_Pin key_out1_Pin key_out3_Pin */
    GPIO_InitStruct.Pin = OCP_Pin | key_out1_Pin | key_out3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : STCP2_Pin SHCP2_Pin SD2_Pin display1_Pin
                             display2_Pin display3_Pin display4_Pin key_in1_Pin
                             key_in2_Pin */
    GPIO_InitStruct.Pin = STCP2_Pin | SHCP2_Pin | SD2_Pin | display1_Pin | display2_Pin | display3_Pin | display4_Pin | key_in1_Pin | key_in2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pins : REL3_Pin REL2_Pin */
    GPIO_InitStruct.Pin = REL3_Pin | REL2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : BKeyRight_Pin */
    GPIO_InitStruct.Pin = BKeyRight_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(BKeyRight_GPIO_Port, &GPIO_InitStruct);

    /* USER CODE BEGIN MX_GPIO_Init_2 */

    /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while(1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
