
#include "fifo.h"

static uint16_t FifoNext( tFifo *fifo, uint16_t index )
{
	return ( index + 1 ) % fifo->Size;
}

void FifoInit( tFifo *fifo, uint16_t *buffer, uint16_t size )
{
	fifo->Begin = 0;
	fifo->End = 0;
	fifo->Data = buffer;
	fifo->Size = size;
}

void FifoPush( tFifo *fifo, uint16_t data )
{
	fifo->End = FifoNext( fifo, fifo->End );
	fifo->Data[fifo->End] = data;
}

uint16_t FifoPop( tFifo *fifo )
{
	uint16_t data = fifo->Data[FifoNext( fifo, fifo->Begin )];

	fifo->Begin = FifoNext( fifo, fifo->Begin );
	return data;
}

void FifoFlush( tFifo *fifo )
{
	fifo->Begin = 0;
	fifo->End = 0;
}

bool IsFifoEmpty( tFifo *fifo )
{
	return ( fifo->Begin == fifo->End );
}
uint8_t get_Fifo_size( tFifo *fifo )
{
	return (  fifo->End  - fifo->Begin );
}
bool IsFifoExist( tFifo *fifo ,uint16_t data)
{
	uint8_t i ;
    uint8_t len = fifo->End - fifo->Begin;
	if(len > 0)
	{
	    for(i=0;i<len;i++)
		{
			if(data == fifo->Data[FifoNext( fifo, fifo->Begin ) + len])
			{
			    return 1;
			}
		}
	}else{
	    for(i=1;i<fifo->End;i++)
		{
		    if(data == fifo->Data[i])
			{
			    return 1;
			}
		}
		for(i=FifoNext( fifo, fifo->Begin );i<fifo->Size;i++)
		{
		    if(data == fifo->Data[i])
			{
			    return 1;
			}
		}
	}
	return 0;
}
bool IsFifoFull( tFifo *fifo )
{
	return ( FifoNext( fifo, fifo->End ) == fifo->Begin );
}
