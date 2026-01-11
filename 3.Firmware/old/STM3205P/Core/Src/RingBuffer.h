/* ###################################################################
**     Filename    : RingBuffer.h
**     Project     : STM3205P
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Oct 9, 2025, 18:22:05
**     Author      : lucas
**
**     Descrição   : Interface pública para um buffer circular (ring buffer)
**                   genérico para RBDataType (uint16_t por padrão).
**
** ###################################################################*/

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------
#include "stdint.h"
#include "stdbool.h"


//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------
#define RBDataType uint16_t

//--------------------------------------------------------------------
// Typedef enum
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
typedef struct
{
    RBDataType *buffer;    // pointer to buffer memory
    uint16_t size;         // size of the buffer (number of elements)
    uint16_t head;         // head index (write position)
    uint16_t tail;         // tail index (read position)
    bool full;             // buffer full flag
}RingBuffer_t;


//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------

/**
 * @brief Inicializa o ring buffer.
 * @param rb    Ponteiro para a estrutura do ring buffer.
 * @param buffer Ponteiro para a memória de armazenamento (array de RBDataType).
 * @param size  Número de elementos do buffer.
 */
void RingBuffer_Init(RingBuffer_t *rb, RBDataType* buffer, uint16_t size);

/**
 * @brief Reseta índices e estado do buffer (não altera os dados armazenados).
 * @param rb Ponteiro para a estrutura do ring buffer.
 */
void RingBuffer_Reset(RingBuffer_t *rb);

/**
 * @brief Insere um elemento no buffer.
 * @param rb   Ponteiro para a estrutura do ring buffer.
 * @param data Dado a ser inserido.
 * @return true se ocorreu sobrescrita de dado antigo; false caso contrário.
 */
bool RingBuffer_Put(RingBuffer_t *rb, RBDataType data);

/**
 * @brief Lê (remove) um elemento do buffer.
 * @param rb   Ponteiro para a estrutura do ring buffer.
 * @param data Ponteiro onde será armazenado o elemento lido.
 * @return true se um elemento foi lido; false se o buffer estava vazio.
 */
bool RingBuffer_Get(RingBuffer_t *rb, RBDataType *data);

/**
 * @brief Informa se o buffer está vazio.
 * @param rb Ponteiro para a estrutura do ring buffer.
 * @return true se vazio; false caso contrário.
 */
bool RingBuffer_IsEmpty(RingBuffer_t *rb);

/**
 * @brief Informa se o buffer está cheio.
 * @param rb Ponteiro para a estrutura do ring buffer.
 * @return true se cheio; false caso contrário.
 */
bool RingBuffer_IsFull(RingBuffer_t *rb);

/**
 * @brief Retorna a capacidade (número total de elementos) do buffer.
 * @param rb Ponteiro para a estrutura do ring buffer.
 * @return Capacidade do buffer.
 */
uint16_t RingBuffer_Capacity(RingBuffer_t *rb);

/**
 * @brief Retorna o número atual de elementos armazenados no buffer.
 * @param rb Ponteiro para a estrutura do ring buffer.
 * @return Quantidade de elementos presentes no buffer.
 */
uint16_t RingBuffer_Size(RingBuffer_t *rb);

/**
 * @brief Calcula a média aritmética dos elementos atualmente armazenados.
 * @param rb Ponteiro para a estrutura do ring buffer.
 * @return Média dos valores; 0.0f se o buffer estiver vazio.
 */
float RingBuffer_Average(RingBuffer_t *rb);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------


#endif /* RINGBUFFER_H_ */
