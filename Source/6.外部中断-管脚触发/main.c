
/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"
//定义LED、按键接口
#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  GPIO_Pin_0
#define KEY_GPIO_PORT  GPIOB
#define KEY_GPIO_PINS  GPIO_Pin_1
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：不精确延时函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Delay(__IO uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：主函数，PD0接LED，灌流，PB1接按键,按压按键触发外部中断，LED被点亮或熄灭
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void main(void)
{
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED，GPD0低速推挽输出
    
    GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPB1上拉输入
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_In_PU_IT);//初始化按键，GPB1上拉输入
    EXTI_DeInit (); //恢复中断的所有设置 
    EXTI_SetPinSensitivity (EXTI_Pin_1,EXTI_Trigger_Falling);//外部中断1，下降沿触发，中断向量号9
    
    enableInterrupts();//使能中断
   
    while(1)
    {
        

    }

}
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/