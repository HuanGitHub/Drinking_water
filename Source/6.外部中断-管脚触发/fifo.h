#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdbool.h>
//#include "mytypedef.h"
#include "stm8l10x.h"


/*!
 * FIFO
 */
typedef struct sFifo
{
	uint16_t Begin;
	uint16_t End;
	uint16_t *Data;
    uint16_t Size;
}tFifo;

void FifoInit( tFifo *fifo, uint16_t *buffer, uint16_t size );

void FifoPush( tFifo *fifo, uint16_t data );

uint16_t FifoPop( tFifo *fifo );

void FifoFlush( tFifo *fifo );

bool IsFifoEmpty( tFifo *fifo );

bool IsFifoFull( tFifo *fifo );

uint8_t get_Fifo_size( tFifo *fifo );

#endif // __FIFO_H__
