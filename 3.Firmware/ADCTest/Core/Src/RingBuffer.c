/* ###################################################################
**     Filename    : RingBuffer.c
**     Project     : STM3205P
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : Oct 9, 2025, 18:21:54
**     Author      : lucas
**
**     Implementação de um buffer circular (ring buffer) simples.
**
** ###################################################################*/


//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------

#include "RingBuffer.h"

//--------------------------------------------------------------------
// Definitions
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Function prototype
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------


//--------------------------------------------------------------------
// Code
//--------------------------------------------------------------------

/* ###################################################################
 * Function: RingBuffer_Init
 * Description:
 *     Inicializa a estrutura do ring buffer associando o array de
 *     armazenamento e ajustando índices e flags.
 *
 * Parameters:
 *     rb     - Ponteiro para RingBuffer_t a ser inicializado.
 *     buffer - Ponteiro para memória de armazenamento (array).
 *     size   - Número de elementos do array.
 *
 * Returns:
 *     void
 *
 * ###################################################################*/
void RingBuffer_Init(RingBuffer_t *rb, RBDataType* buffer, uint16_t size)
{
    rb->buffer = buffer;
    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
    rb->full = false;
}

/* ###################################################################
 * Function: RingBuffer_Reset
 * Description:
 *     Reseta índices e flag de cheio. Não altera o conteúdo do array.
 *
 * Parameters:
 *     rb - Ponteiro para RingBuffer_t.
 *
 * Returns:
 *     void
 *
 * ###################################################################*/
void RingBuffer_Reset(RingBuffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->full = false;
}

/* ###################################################################
 * Function: RingBuffer_Put
 * Description:
 *     Insere um valor no buffer. Se o buffer estiver cheio, sobrescreve
 *     o elemento mais antigo e avança a cauda.
 *
 * Parameters:
 *     rb   - Ponteiro para RingBuffer_t.
 *     data - Valor a ser inserido.
 *
 * Returns:
 *     true  - se ocorreu sobrescrita de dado antigo;
 *     false - caso contrário.
 *
 * ###################################################################*/
bool RingBuffer_Put(RingBuffer_t *rb, RBDataType data)
{
    bool overwritten = false;

    rb->buffer[rb->head] = data;

    if(rb->full)
    {
        rb->tail = (rb->tail + 1) % rb->size; // Overwrite, move tail forward
        overwritten = true; // Indicate that an overwrite occurred
    }

    rb->head = (rb->head + 1) % rb->size;

    rb->full = (rb->head == rb->tail);

    return overwritten;
}

/* ###################################################################
 * Function: RingBuffer_Get
 * Description:
 *     Lê e remove o elemento mais antigo do buffer (na posição tail).
 *
 * Parameters:
 *     rb   - Ponteiro para RingBuffer_t.
 *     data - Ponteiro onde será escrita a amostra lida.
 *
 * Returns:
 *     true  - se um elemento foi lido;
 *     false - se o buffer estava vazio.
 *
 * ###################################################################*/
bool RingBuffer_Get(RingBuffer_t *rb, RBDataType *data)
{
    bool ret = false;

    if(!RingBuffer_IsEmpty(rb))
    {
        *data = rb->buffer[rb->tail];
        rb->full = false;
        rb->tail = (rb->tail + 1) % rb->size;
        ret = true;
    }

    return ret;
}

/* ###################################################################
 * Function: RingBuffer_IsEmpty
 * Description:
 *     Indica se o buffer está vazio.
 *
 * Parameters:
 *     rb - Ponteiro para RingBuffer_t.
 *
 * Returns:
 *     true se vazio; false caso contrário.
 *
 * ###################################################################*/
bool RingBuffer_IsEmpty(RingBuffer_t *rb)
{
    return (!rb->full && (rb->head == rb->tail));
}

/* ###################################################################
 * Function: RingBuffer_IsFull
 * Description:
 *     Indica se o buffer está cheio.
 *
 * Parameters:
 *     rb - Ponteiro para RingBuffer_t.
 *
 * Returns:
 *     true se cheio; false caso contrário.
 *
 * ###################################################################*/
bool RingBuffer_IsFull(RingBuffer_t *rb)
{
    return rb->full;
}

/* ###################################################################
 * Function: RingBuffer_Capacity
 * Description:
 *     Retorna a capacidade total do buffer (número de elementos alocados).
 *
 * Parameters:
 *     rb - Ponteiro para RingBuffer_t.
 *
 * Returns:
 *     Capacidade do buffer.
 *
 * ###################################################################*/
uint16_t RingBuffer_Capacity(RingBuffer_t *rb)
{
    return rb->size;
}

/* ###################################################################
 * Function: RingBuffer_Size
 * Description:
 *     Retorna o número de elementos atualmente armazenados no buffer.
 *
 * Parameters:
 *     rb - Ponteiro para RingBuffer_t.
 *
 * Returns:
 *     Quantidade de elementos presentes.
 *
 * ###################################################################*/
uint16_t RingBuffer_Size(RingBuffer_t *rb)
{
    uint16_t size = rb->size;

    if(!rb->full)
    {
        if(rb->head >= rb->tail)
        {
            size = rb->head - rb->tail;
        }
        else
        {
            size = rb->size + rb->head - rb->tail;
        }
    }

    return size;
}

/* ###################################################################
 * Function: RingBuffer_Average
 * Description:
 *     Calcula a média aritmética dos elementos atualmente armazenados
 *     no buffer. Retorna 0.0 se o buffer estiver vazio.
 *
 * Parameters:
 *     rb - Ponteiro para RingBuffer_t.
 *
 * Returns:
 *     Média dos valores armazenados (float).
 *
 * ###################################################################*/
float RingBuffer_Average(RingBuffer_t *rb)
{
    float avg = 0.0f;
    uint16_t count = RingBuffer_Size(rb);

    if(count == 0)
    {
        return 0.0f; // Avoid division by zero
    }

    for(uint16_t i = 0; i < count; i++)
    {
        uint16_t index = (rb->tail + i) % rb->size;
        avg += rb->buffer[index];
    }

    avg /= count;

    return avg;
}


