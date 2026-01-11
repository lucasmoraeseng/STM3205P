/* ###################################################################
**     Filename    : DAC8830.h
**     Project     : STM3205P
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Oct 14, 2025
**     Author      : lucas
**
**     Interface para controle da DAC8830 via SPI usando HAL (MX).
**
** ###################################################################*/

#ifndef SRC_DAC8830_H_
#define SRC_DAC8830_H_

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------
#include "stm32f1xx_hal.h"
#include "main.h"
#include "stdint.h"
#include "stdbool.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------
#ifndef DAC8830_DEFAULT_TIMEOUT_MS
#define DAC8830_DEFAULT_TIMEOUT_MS  10u
#endif

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
typedef struct {
    SPI_HandleTypeDef *hspi;    // SPI handle (MX generated)
    GPIO_TypeDef *cs_port;      // CS GPIO port
    uint16_t cs_pin;            // CS GPIO pin
    float vref;                 // Reference voltage used for conversion
    uint32_t timeout_ms;        // HAL timeout for SPI transactions
    bool initialized;           // Device initialized flag
} DAC8830_t;

//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------

/**
 * @brief Inicializa estrutura do driver da DAC8830.
 * @param dev      Ponteiro para estrutura DAC8830_t (usuário aloca).
 * @param hspi     Ponteiro para SPI handle (por exemplo &hspi1).
 * @param cs_port  GPIO port do CS (por exemplo GPIOA).
 * @param cs_pin   GPIO pin do CS (por exemplo GPIO_PIN_4).
 * @param vref     Tensão de referência usada na conversão voltagem->código.
 *
 * Nota: função não altera configurações do SPI — presuma que o MX
 *       já configurou o periférico adequadamente.
 */
void DAC8830_Init(DAC8830_t *dev, SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_port, uint16_t cs_pin, float vref);

/**
 * @brief Envia um código bruto de 16 bits para a DAC8830.
 * @param dev   Ponteiro para estrutura DAC8830_t inicializada.
 * @param value Código de 16 bits (MSB primeiro).
 * @return true em caso de sucesso, false em caso de erro.
 */
bool DAC8830_WriteRaw(DAC8830_t *dev, uint16_t value);

/**
 * @brief Converte uma tensão desejada para código e envia para a DAC8830.
 * @param dev     Ponteiro para estrutura DAC8830_t inicializada.
 * @param voltage Tensão desejada na saída (V).
 * @return true em caso de sucesso, false em caso de erro ou se voltage fora do alcance.
 */
bool DAC8830_SetVoltage(DAC8830_t *dev, float voltage);

/**
 * @brief Ajusta o timeout usado nas operações SPI (ms).
 * @param dev       Ponteiro para estrutura DAC8830_t.
 * @param timeoutMs Timeout em milissegundos.
 */
void DAC8830_SetTimeout(DAC8830_t *dev, uint32_t timeoutMs);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------

#endif /* SRC_DAC8830_H_ */
