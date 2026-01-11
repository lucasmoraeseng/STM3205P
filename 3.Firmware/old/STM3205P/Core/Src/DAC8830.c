/* ###################################################################
**     Filename    : DAC8830.c
**     Project     : STM3205P
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Oct 14, 2025
**     Author      : lucas
**
**     Implementação do driver básico para DAC8830 usando HAL SPI.
**
** ###################################################################*/

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------
#include "DAC8830.h"
#include "string.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------
#ifndef DAC8830_DEFAULT_TIMEOUT_MS
#define DAC8830_DEFAULT_TIMEOUT_MS  10u
#endif

//--------------------------------------------------------------------
// Function prototype (private)
//--------------------------------------------------------------------
static void DAC8830_CS_Low(DAC8830_t *dev);
static void DAC8830_CS_High(DAC8830_t *dev);
static uint16_t DAC8830_ClampCode(int32_t code);

//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Code
//--------------------------------------------------------------------

/* ###################################################################
 * Function: DAC8830_Init
 * Description:
 *     Inicializa a estrutura do driver associando periféricos e
 *     parâmetros básicos (vref e timeout). Não reconfigura o SPI:
 *     espera-se que o MX já o tenha configurado.
 *
 * Parameters:
 *     dev     - Ponteiro para DAC8830_t (estrutura alocada pelo usuário).
 *     hspi    - Ponteiro para SPI handle configurado.
 *     cs_port - GPIO port do CS.
 *     cs_pin  - GPIO pin do CS.
 *     vref    - Tensão de referência (V) usada na conversão.
 *
 * Returns:
 *     void
 *
 * ###################################################################*/
void DAC8830_Init(DAC8830_t *dev, SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_port, uint16_t cs_pin, float vref)
{
    if (dev == NULL) return;

    dev->hspi = hspi;
    dev->cs_port = cs_port;
    dev->cs_pin = cs_pin;
    dev->vref = (vref > 0.0f) ? vref : 1.0f;
    dev->timeout_ms = DAC8830_DEFAULT_TIMEOUT_MS;
    dev->initialized = true;

    /* Ensure CS high (inactive) */
    DAC8830_CS_High(dev);
}

/* ###################################################################
 * Function: DAC8830_SetTimeout
 * Description:
 *     Ajusta timeout para operações SPI do driver.
 *
 * ###################################################################*/
void DAC8830_SetTimeout(DAC8830_t *dev, uint32_t timeoutMs)
{
    if (dev == NULL) return;
    dev->timeout_ms = timeoutMs ? timeoutMs : DAC8830_DEFAULT_TIMEOUT_MS;
}

/* ###################################################################
 * Function: DAC8830_WriteRaw
 * Description:
 *     Envia 16 bits para a DAC8830 via SPI. Controle manual do CS
 *     antes e depois da transmissão.
 *
 * Returns:
 *     true  - transmissao OK
 *     false - erro (ponteiro inválido ou HAL SPI falhou)
 *
 * ###################################################################*/
bool DAC8830_WriteRaw(DAC8830_t *dev, uint16_t value)
{
    if (dev == NULL || !dev->initialized || dev->hspi == NULL) return false;

    uint8_t tx[2];
    tx[0] = (uint8_t)((value >> 8) & 0xFF);
    tx[1] = (uint8_t)(value & 0xFF);

    DAC8830_CS_Low(dev);
    HAL_StatusTypeDef st = HAL_SPI_Transmit(dev->hspi, tx, 2, dev->timeout_ms);
    DAC8830_CS_High(dev);

    return (st == HAL_OK);
}

/* ###################################################################
 * Function: DAC8830_SetVoltage
 * Description:
 *     Converte a tensão desejada para código de 16 bits considerando
 *     vref configurada em DAC8830_Init e envia para a DAC8830.
 *     A conversão usa escala linear: code = round((Vout / Vref) * 65535).
 *
 * Returns:
 *     true  - transmissão OK
 *     false - erro (ponteiro inválido, tensão fora de alcance ou SPI falhou)
 *
 * ###################################################################*/
bool DAC8830_SetVoltage(DAC8830_t *dev, float voltage)
{
    if (dev == NULL || !dev->initialized) return false;

    /* Clamp voltage to 0..vref */
    if (voltage < 0.0f) voltage = 0.0f;
    if (voltage > dev->vref) voltage = dev->vref;

    /* Scale to 16-bit unsigned */
    float ratio = voltage / dev->vref;
    uint32_t code = (uint32_t)(ratio * 65535.0f + 0.5f);

    return DAC8830_WriteRaw(dev, (uint16_t)DAC8830_ClampCode((int32_t)code));
}

/* ###################################################################
 * Function: DAC8830_CS_Low / DAC8830_CS_High
 * Description:
 *     Funções auxiliares para controlar o pino CS.
 *
 * ###################################################################*/
static void DAC8830_CS_Low(DAC8830_t *dev)
{
    if (dev && dev->cs_port) {
        HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
    }
}

static void DAC8830_CS_High(DAC8830_t *dev)
{
    if (dev && dev->cs_port) {
        HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
    }
}

/* ###################################################################
 * Function: DAC8830_ClampCode
 * Description:
 *     Garante que o código enviado esteja dentro de 0..0xFFFF.
 *
 * ###################################################################*/
static uint16_t DAC8830_ClampCode(int32_t code)
{
    if (code < 0) return 0u;
    if (code > 0xFFFF) return 0xFFFFu;
    return (uint16_t)code;
}
