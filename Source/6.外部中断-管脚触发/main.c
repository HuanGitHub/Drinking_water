
/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"
#include "stdio.h"        //包含C库函数
#include "HX711.h"
#include "delay.h"
#include "stm8l10x_usart.h"
//定义LED、按键接口
#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  GPIO_Pin_0
#define KEY_GPIO_PORT  GPIOB
#define KEY_GPIO_PINS  GPIO_Pin_1
//以下需要添加
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
#define USART_BAUDRATE    9600

PUTCHAR_PROTOTYPE
{  
  USART_SendData8(c);
  while (USART_GetFlagStatus(USART_FLAG_TXE) == RESET);

  return (c);
}
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
	
	CLK_PeripheralClockConfig (CLK_Peripheral_USART,ENABLE); //使能外设时钟
	//以下2句为设置USART的TXD、RXD所在I/O口，板子上有CH340，已经带了硬件上拉，不设置也可以，如果不带CH340则应该设置
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);//TXD
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);//RXD
	USART_Init(USART_BAUDRATE,USART_WordLength_8D,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART初始化，9600，8N1
	USART_ITConfig (USART_IT_RXNE,ENABLE);//使能接收中断，中断向量号28
    USART_Cmd (ENABLE);//使能USART
    printf("USART_Printf\r\n"); //发送字符串，末尾换行
	//KEY
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED，GPD0低速推挽输出
    GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPB1上拉输入
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_In_PU_IT);//初始化按键，GPB1上拉输入
    EXTI_DeInit (); //恢复中断的所有设置 
    EXTI_SetPinSensitivity (EXTI_Pin_1,EXTI_Trigger_Falling);//外部中断1，下降沿触发，中断向量号9
    //Time4 
	CLK_PeripheralClockConfig (CLK_Peripheral_TIM4,ENABLE); //使能外设时钟，STM8L外设时钟默认关闭，使用前需使能
	TIM4_DeInit();
    TIM4_TimeBaseInit(TIM4_Prescaler_128, 0xff);//16M/8/128=15.625K，0xff=255,255*（1/15.625）=0.01632S，大约61次中断是1S
    TIM4_ITConfig(TIM4_IT_Update, ENABLE);//向上溢出中断使能，中断向量号25
//    TIM4_Cmd(ENABLE);//TIM4使能
	//HX711
	Init_HX711pin();
	Get_Maopi();//称毛皮重量
	delay_ms(1000);
	delay_ms(1000);
	Get_Maopi();//重新获取毛皮重量
	

    enableInterrupts();//使能中断
   
    while(1)
    {
		Get_Weight();
		printf("净重量 = %ld g\r\n",(u32)Weight_Shiwu); //打印 
		
		delay_ms(1000);
		
		System_Tsk();

    }

}
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
