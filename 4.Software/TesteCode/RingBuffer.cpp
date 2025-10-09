/* ###################################################################
**     Filename    : RingBuffer.cpp
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
 * Function: RB_Init
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Initialize a ring buffer structure.
 *
 * Parameters:
 *  rb       - pointer to the RingBuffer_t instance to initialize
 *  buffer   - pointer to the backing memory buffer (byte array)
 *  size     - size in bytes of the backing buffer
 *
 * Returns:
 *  void
 *
 * Notes:
 *  The provided buffer pointer must point to at least 'size' bytes.
###################################################################*/
void RB_Init(RingBuffer_t *rb, void *buffer, size_t size)
{
    rb->buffer = buffer;
    rb->maxSize = size;
    rb->head = 0;
    rb->tail = 0;
    rb->full = false;
}

/* ###################################################################
 * Function: RB_Reset
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Reset ring buffer indices and full flag.
 *
 * Parameters:
 *  rb - pointer to the RingBuffer_t instance to reset
 *
 * Returns:
 *  void
###################################################################*/
void RB_Reset(RingBuffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->full = false;
}

/* ###################################################################
 * Function: RB_Put
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Write dataSize bytes into the ring buffer.
 *
 * Parameters:
 *  rb       - pointer to the RingBuffer_t
 *  data     - pointer to source data to copy into the buffer
 *  dataSize - number of bytes to write
 *
 * Returns:
 *  true  - on success
 *  false - if dataSize is larger than buffer capacity
 *
 * Notes:
 *  If the buffer is full, this implementation advances the tail
 *  to overwrite the oldest data (overwrite mode).
###################################################################*/
bool RB_Put(RingBuffer_t *rb, void *data, size_t dataSize)
{
    if(dataSize > rb->maxSize) 
    {
        // Data size is larger than buffer size
        return false;
    }

    memcpy((uint8_t*)rb->buffer + rb->head, data, dataSize);

    if(rb->full) 
    {
        rb->tail = (rb->tail + dataSize) % rb->maxSize; // Overwrite oldest data
    }

    rb->head = (rb->head + dataSize) % rb->maxSize;
    rb->full = (rb->head == rb->tail);

    return true;
}

/* ###################################################################
 * Function: RB_Get
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Read dataSize bytes from the ring buffer into the provided output.
 *
 * Parameters:
 *  rb       - pointer to the RingBuffer_t
 *  data     - pointer to destination buffer to receive data
 *  dataSize - number of bytes to read
 *
 * Returns:
 *  true  - on success
 *  false - if the buffer is empty
 *
 * Notes:
 *  This implementation does not validate that 'dataSize' bytes are
 *  available; caller must ensure sufficient data is present or adapt
 *  the function accordingly.
###################################################################*/
bool RB_Get(RingBuffer_t *rb, void *data, size_t dataSize)
{
    if(rb->head == rb->tail && !rb->full) 
    {
        // Buffer is empty
        return false;
    }

    memcpy(data, (uint8_t*)rb->buffer + rb->tail, dataSize);
    rb->full = false;
    rb->tail = (rb->tail + dataSize) % rb->maxSize;

    return true;
}

/* ###################################################################
 * Function: RB_IsFull
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Check if the ring buffer is full.
 *
 * Parameters:
 *  rb - pointer to the RingBuffer_t
 *
 * Returns:
 *  true if full, false otherwise
###################################################################*/
bool RB_IsFull(RingBuffer_t *rb)
{
    return rb->full;
}

/* ###################################################################
 * Function: RB_IsEmpty
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Check if the ring buffer is empty.
 *
 * Parameters:
 *  rb - pointer to the RingBuffer_t
 *
 * Returns:
 *  true if empty, false otherwise
###################################################################*/
bool RB_IsEmpty(RingBuffer_t *rb)
{
    return (!rb->full && (rb->head == rb->tail));
}

/* ###################################################################
 * Function: RB_Capacity
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Return the capacity of the ring buffer in bytes.
 *
 * Parameters:
 *  rb - pointer to the RingBuffer_t
 *
 * Returns:
 *  capacity in bytes
###################################################################*/
size_t RB_Capacity(RingBuffer_t *rb)
{
    return rb->maxSize;
}

/* ###################################################################
 * Function: RB_Size
 * Author: Moraes, L.
 * Date: Oct 6, 2025
 * Revision: 1.0
 * --------------------
 * Return the current number of bytes stored in the buffer.
 *
 * Parameters:
 *  rb - pointer to the RingBuffer_t
 *
 * Returns:
 *  number of bytes currently stored
###################################################################*/
size_t RB_Size(RingBuffer_t *rb)
{
    size_t size = rb->maxSize;

    if(!rb->full) 
    {
        if(rb->head >= rb->tail) 
        {
            size = rb->head - rb->tail;
        } 
        else 
        {
            size = rb->maxSize + rb->head - rb->tail;
        }
    }

    return size;
}


