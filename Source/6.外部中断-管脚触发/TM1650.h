 
#ifndef __TM1650_I2C_H
#define __TM1650_I2C_H
#include "stm8l10x.h"

#define TM1650_SCL_PORT   GPIOB
#define TM1650_SCL_PIN    GPIO_Pin_3

#define TM1650_SDA_PORT   GPIOB
#define TM1650_SDA_PIN    GPIO_Pin_4


#define SCL_TM1650(a) if(a){GPIO_SetBits(TM1650_SCL_PORT, TM1650_SCL_PIN);}else{GPIO_ResetBits(TM1650_SCL_PORT, TM1650_SCL_PIN);}//PA3
#define SDA_TM1650(a) if(a){GPIO_SetBits(TM1650_SDA_PORT, TM1650_SDA_PIN);}else{GPIO_ResetBits(TM1650_SDA_PORT, TM1650_SDA_PIN);}//PA3
#define SDAM_TM1650              GPIO_ReadInputDataBit(TM1650_SCL_PORT, TM1650_SCL_PIN)//PA2
#define SET_SCL_OUT_TM1650()    {GPIO_Init(TM1650_SCL_PORT, TM1650_SCL_PIN, GPIO_Mode_Out_PP_High_Fast);}
#define SET_SDA_OUT_TM1650()    {GPIO_Init(TM1650_SDA_PORT, TM1650_SDA_PIN, GPIO_Mode_Out_PP_High_Fast);}
#define SET_SDA_IN_TM1650()     {GPIO_Init(TM1650_SDA_PORT, TM1650_SDA_PIN, GPIO_Mode_In_FL_No_IT);}
 
 
void IIC_Init_TM1650(void);
void TDelay_us(u8 z);
void I2C_Start_TM1650(void);
void I2C_Stop_TM1650(void);
void IIC_Ack_TM1650(void);
void IIC_NAck_TM1650(void);
uint8_t IIC_Wait_Ack_TM1650(void);
void IIC_WrByte_TM1650(uint8_t txd);
 
//u8 Scan_Key(void);
void TM1650_Set(u8 add,u8 dat);
void Init_Tm1650(void);
void TM1650_show_u8(u8 num);
 
#endif
