 
#ifndef __TM1650_I2C_H
#define __TM1650_I2C_H
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "tim1.h"
#include "usart2.h"
#include <iostm8s103f3.h>
#include <intrinsics.h>
 
 
/**********************************
TM1650芯片控制20路灯函数
PB7为SCL口
PB6为SDA口
**********************************/
 
#define SCL_TM1650              PC_ODR_ODR7
#define SDA_TM1650               PC_ODR_ODR6
#define SDAM_TM1650              PC_IDR_IDR6
#define SET_SCL_OUT_TM1650()    {PC_DDR_DDR7=1; PC_CR1_C17 = 1; PC_CR2_C27 = 0;}
#define SET_SDA_OUT_TM1650()    {PC_DDR_DDR6=1; PC_CR1_C16 = 1; PC_CR2_C26 = 0;}
#define SET_SDA_IN_TM1650()     {PC_DDR_DDR6=0; PC_CR1_C16 = 0; PC_CR2_C26 = 0;}
 
 
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
 
#endif
