
#include "System.h"
#include "com_event.h"
#include "com_state.h"
#include "fifo.h"
#include "FSM.h"
#include "HX711.h"
#include "TM1650.h"
#include "delay.h"
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
SYSTEM_EVENT System_Event = SYSTEM_EVENT_NULL;
FSM_t        System_fsm_t;
u8	user_timing = 0;
FsmTable_t   s_System_FsmTable_t[]=
{
	/* event */			      /* CurState */        	/* (*eventActFun) */ 				/* NextState */
	{SYSTEM_EVENT_NULL,      	SYSTEM_STATE_IDEL,     	System_Check_EVENT_Fifo,       		SYSTEM_STATE_IDEL   },
	{SYSTEM_EVENT_CUP_WEIGHT,   SYSTEM_STATE_IDEL,     	get_cup_weight,      	    			SYSTEM_STATE_IDEL   },
	{SYSTEM_EVENT_TIME_OUT,  	SYSTEM_STATE_IDEL,     	time_out,      				SYSTEM_STATE_IDEL 	},
	{SYSTEM_EVENT_REQ_UP,  		SYSTEM_STATE_IDEL,     	time_out,      				SYSTEM_STATE_IDEL 	},
	{SYSTEM_EVENT_REQ_DOWN,  	SYSTEM_STATE_IDEL,     	time_out,      				SYSTEM_STATE_IDEL 	},
	
};
s32 last_weight = 0;
void get_cup_weight()
{
	Get_Maopi();//称毛皮重量
	delay_ms(1000);
	delay_ms(1000);
	Get_Maopi();//重新获取毛皮重量
	
	TIM4_Cmd(ENABLE);//TIM4使能
	if(last_weight == 0)
	{
		System_Add_EventFifo(SYSTEM_EVENT_TIME_OUT);
	}
	
}
void time_add_des()
{
	if(SYSTEM_EVENT_REQ_UP == System_Event)
	{
	    user_timing ++ ;
	}else{
		if(user_timing>1){
			user_timing -- ;
		}
	}
	TM1650_show_u8(user_timing);
}
void time_out()
{
	TIM4_Cmd(DISABLE);//TIM4使能
    Get_Weight();
	if(last_weight != 0)
	{
	    if((last_weight - Weight_Shiwu) > 10)
		{
			
		}else{
			if(Weight_Shiwu == Weight_Maopi)
			{
				//air cup
			}
			// beep
			
		}
	}else{
		
	}

	last_weight = Weight_Shiwu;
	TIM4_Cmd(ENABLE);//TIM4使能
	
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

