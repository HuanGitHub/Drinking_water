#ifndef __SYSTEM_CONTROL_H
#define __SYSTEM_CONTROL_H
#include "com_event.h"
#include "com_state.h"
#include "stm8l10x.h"
typedef enum
{
	END_REQ_IDEL,
    END_REQ_GET_ID,
	END_REQ_CALL,
	END_REQ_TAKE,
	CON_RES_GET_ID,
}RECV_REQ_ID;

typedef struct
{
	void ( *GPIOInit)(void);
    void ( *DriverInit )( void );
    void ( *Reset )( void );
    void ( *StartRx )( void );
    void ( *GetRxPacket )( uint8_t *buffer);
    void ( *SetTxPacket )( uint8_t *buffer, uint8_t size );
    uint32_t ( *Process )( void );
}s_SystemDriver;

void System_init(void);

extern void System_Add_EventFifo(SYSTEM_EVENT System_event);
void System_Tsk(void);



#endif
