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

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

//--------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h> /* for size_t */

//--------------------------------------------------------------------
// Typedef structs
//--------------------------------------------------------------------
typedef struct {
    void *buffer;      // Pointer to the buffer array
    size_t head;       // Index of the head (next write position)
    size_t tail;       // Index of the tail (next read position)
    size_t maxSize;    // Maximum size of the buffer (capacity in bytes)
    bool full;         // Flag to indicate if the buffer is full
} RingBuffer_t;

//--------------------------------------------------------------------
// Function prototypes (external)
//--------------------------------------------------------------------
extern void   RB_Init(RingBuffer_t *rb, void *buffer, size_t size);
extern void   RB_Reset(RingBuffer_t *rb);
extern bool   RB_Put(RingBuffer_t *rb, void *data, size_t dataSize);
extern bool   RB_Get(RingBuffer_t *rb, void *data, size_t dataSize);
extern bool   RB_IsFull(RingBuffer_t *rb);
extern bool   RB_IsEmpty(RingBuffer_t *rb);
extern size_t RB_Capacity(RingBuffer_t *rb);
extern size_t RB_Size(RingBuffer_t *rb);

//--------------------------------------------------------------------
// General Variables
//--------------------------------------------------------------------

#endif /* RING_BUFFER_H_ */
