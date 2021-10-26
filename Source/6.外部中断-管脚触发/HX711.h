#ifndef __HX711_H
#define __HX711_H

#include "stm8l10x.h"
#include "stm8l10x_gpio.h"


#define HX711_SCK(a) if(a){GPIO_SetBits(GPIOA, GPIO_Pin_3);}else{GPIO_ResetBits(GPIOA, GPIO_Pin_3);}//PA3

#define HX711_DOUT_SETIN GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT)//PA2
#define HX711_DOUT_SETOUT GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_High_Fast)//PA2
#define HX711_DOUT_GET GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)//PA2
#define HX711_DOUT_OUT(a) if(a){GPIO_SetBits(GPIOA, GPIO_Pin_2);}else{GPIO_ResetBits(GPIOA, GPIO_Pin_2);}//PA2

extern void Init_HX711pin(void);
extern u32 HX711_Read(void);
extern void Get_Maopi(void);
extern void Get_Weight(void);

extern u32 HX711_Buffer;
extern u32 Weight_Maopi;
extern s32 Weight_Shiwu;
extern u8 Flag_Error;

#endif

