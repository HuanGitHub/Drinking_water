#ifndef __FSM__H
#define __FSM__H
#include "stm8l10x.h"
typedef struct 
{
    int event;
	int CurState;
	void (*eventActFun)();
	int NextState;
}FsmTable_t;

typedef struct FSM_s
{
    FsmTable_t *FsmTable;         /* 状态迁移表 */
    uint8_t curState;             /* 状态机当前状态 */
	uint8_t stuMaxNum;              /* 状态机条数*/
}FSM_t;
void FSM_Init(FSM_t *pFsm, FsmTable_t *pTable, uint8_t stuMaxNum,uint8_t curState);
void FSM_EventHandle(FSM_t* pFsm, int event);

#endif
