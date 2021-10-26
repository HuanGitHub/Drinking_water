
#include "System.h"
#include "com_event.h"
#include "com_state.h"
#include "fifo.h"
#include "FSM.h"
#include "HX711.h"
#define EVENT_FIFO_SIZE    8
#define MOTOR_TIME 5
tFifo System_event_fifo;
uint8_t System_event_Fifo[EVENT_FIFO_SIZE];

void System_init(void);
void System_Check_EVENT_Fifo(void);
void get_cup_weight(void);
void System_do_Down(void);
void time_out(void);
void System_set_Event(SYSTEM_EVENT event);
uint16_t System_time;
SYSTEM_EVENT System_Event;
FSM_t        System_fsm_t;
FsmTable_t   s_System_FsmTable_t[]=
{
	/* event */			      /* CurState */        	/* (*eventActFun) */ 				/* NextState */
	{SYSTEM_EVENT_NULL,      	SYSTEM_STATE_IDEL,     	System_Check_EVENT_Fifo,       		SYSTEM_STATE_IDEL   },
	{SYSTEM_EVENT_CUP_WEIGHT,   SYSTEM_STATE_IDEL,     	get_cup_weight,      	    			SYSTEM_STATE_IDEL   },
	{SYSTEM_EVENT_TIME_OUT,  	SYSTEM_STATE_IDEL,     	time_out,      				SYSTEM_STATE_IDEL 	},
	
};
void get_cup_weight()
{
	Get_Maopi();//称毛皮重量
	delay_ms(1000);
	delay_ms(1000);
	Get_Maopi();//重新获取毛皮重量
	
	TIM4_Cmd(ENABLE);//TIM4使能
	
}
void time_out()
{
	TIM4_Cmd(DISABLE);//TIM4使能
    Get_Weight();
	
	if(Weight_Shiwu > 10)
	{

		TIM4_Cmd(ENABLE);//TIM4使能
	}else{
	//beep led motor
		
	}
}
void System_do_Down()
{
//    MOTOR_Rota(MOTOR_REVERSE);
//	DelayMs(MOTOR_TIME);
//	MOTOR_Rota(MOTOR_STOP);
}

void System_Fifo_init()
{
	FifoInit(&System_event_fifo,(uint16_t*)System_event_Fifo,EVENT_FIFO_SIZE);
}

void System_init()
{
	FSM_Init(&System_fsm_t,s_System_FsmTable_t,sizeof(s_System_FsmTable_t)/sizeof(s_System_FsmTable_t[0]),SYSTEM_STATE_IDEL);
	System_Fifo_init();
}

SYSTEM_EVENT System_get_Event()
{
    int i=0;
	int isEmpty = IsFifoEmpty(&System_event_fifo);
	if(isEmpty)
	{
	     return SYSTEM_STATE_IDEL;
	}else{
	     return FifoPop(&System_event_fifo);
	}

//    for(;i<sizeof(rxData_event_Table)/sizeof(rxData_event_Table[0]);i++)
//    {
//        if(rxData_event_Table[i].req_id == System_DealData.pack.Flag)
//		{ 
//		    return rxData_event_Table[i].event;
//		}
//    }
}
void System_Check_EVENT_Fifo()
{
	SYSTEM_EVENT tmp_event = SYSTEM_EVENT_NULL;
	tmp_event = System_get_Event();
	System_set_Event(tmp_event);
	
}

void System_Add_EventFifo(SYSTEM_EVENT System_event)
{
    FifoPush(&System_event_fifo, System_event);
}
void System_set_Event(SYSTEM_EVENT event)
{
	System_Event = event;
}

void System_Tsk()
{
	FSM_EventHandle(&System_fsm_t,System_Event);
	if(SYSTEM_EVENT_NULL == System_Event)
	{
		halt();
	}
}

