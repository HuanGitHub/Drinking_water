#include "FSM.h"
/*状态机注册*/
void FSM_Regist(FSM_t* pFsm, FsmTable_t* pTable)
{
    pFsm->FsmTable = pTable;
}

/*状态迁移*/
void FSM_StateTransfer(FSM_t* pFsm, int state)
{
    pFsm->curState = state;
}

/*事件处理*/
void FSM_EventHandle(FSM_t* pFsm, int event)
{
    FsmTable_t* pActTable = pFsm->FsmTable;
    void (*eventActFun)() = 0;  //函数指针初始化为空
    int NextState;
    int CurState = pFsm->curState;
    int flag = 0; //标识是否满足条件
	int SumItem = pFsm->stuMaxNum;
    int i;
 
    /*获取当前动作函数*/
    for (i = 0; i<SumItem; i++)
    {
        if (event == pActTable[i].event && CurState == pActTable[i].CurState)
        {
            flag = 1;
            eventActFun = pActTable[i].eventActFun;
            NextState = pActTable[i].NextState;
            break;
        }
    }
 
 
    if (flag) //如果满足条件了
    {
        /*动作执行*/
        if (eventActFun)
        {
            eventActFun();
        }
 
        //跳转到下一个状态
        FSM_StateTransfer(pFsm, NextState);
    }
    else
    {
        // do nothing
    }
}

/*==================================================================
* Function  : FSM_Init
* Description : 状态机初始化
* Input Para  : pFsm状态机对象，pTable状态迁移表，stuMaxNum迁移表数量
*               curState当前状态
* Output Para : 
* Return Value: 
==================================================================*/
void FSM_Init(FSM_t *pFsm, FsmTable_t *pTable, uint8_t stuMaxNum,uint8_t curState)
{
    pFsm->FsmTable = pTable;
    pFsm->curState = curState;
	pFsm->stuMaxNum  = stuMaxNum;
}
