
/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"
#include "stdio.h"        //����C�⺯��
#include "HX711.h"
#include "delay.h"
#include "stm8l10x_usart.h"
//����LED�������ӿ�
#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  GPIO_Pin_0
#define KEY_GPIO_PORT  GPIOB
#define KEY_GPIO_PINS  GPIO_Pin_1
//������Ҫ���
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
****��ڲ�������
****���ڲ�������
****������ע������ȷ��ʱ����
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
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
****��ڲ�������
****���ڲ�������
****������ע����������PD0��LED��������PB1�Ӱ���,��ѹ���������ⲿ�жϣ�LED��������Ϩ��
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void main(void)
{
	
	CLK_PeripheralClockConfig (CLK_Peripheral_USART,ENABLE); //ʹ������ʱ��
	//����2��Ϊ����USART��TXD��RXD����I/O�ڣ���������CH340���Ѿ�����Ӳ��������������Ҳ���ԣ��������CH340��Ӧ������
    GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);//TXD
    GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);//RXD
	USART_Init(USART_BAUDRATE,USART_WordLength_8D,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART��ʼ����9600��8N1
	USART_ITConfig (USART_IT_RXNE,ENABLE);//ʹ�ܽ����жϣ��ж�������28
    USART_Cmd (ENABLE);//ʹ��USART
    printf("USART_Printf\r\n"); //�����ַ�����ĩβ����
	//KEY
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED��GPD0�����������
    GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ��������GPB1��������
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_In_PU_IT);//��ʼ��������GPB1��������
    EXTI_DeInit (); //�ָ��жϵ��������� 
    EXTI_SetPinSensitivity (EXTI_Pin_1,EXTI_Trigger_Falling);//�ⲿ�ж�1���½��ش������ж�������9
    //Time4 
	CLK_PeripheralClockConfig (CLK_Peripheral_TIM4,ENABLE); //ʹ������ʱ�ӣ�STM8L����ʱ��Ĭ�Ϲرգ�ʹ��ǰ��ʹ��
	TIM4_DeInit();
    TIM4_TimeBaseInit(TIM4_Prescaler_128, 0xff);//16M/8/128=15.625K��0xff=255,255*��1/15.625��=0.01632S����Լ61���ж���1S
    TIM4_ITConfig(TIM4_IT_Update, ENABLE);//��������ж�ʹ�ܣ��ж�������25
//    TIM4_Cmd(ENABLE);//TIM4ʹ��
	//HX711
	Init_HX711pin();
	Get_Maopi();//��ëƤ����
	delay_ms(1000);
	delay_ms(1000);
	Get_Maopi();//���»�ȡëƤ����
	

    enableInterrupts();//ʹ���ж�
   
    while(1)
    {
		Get_Weight();
		printf("������ = %ld g\r\n",(u32)Weight_Shiwu); //��ӡ 
		
		delay_ms(1000);
		
		System_Tsk();

    }

}
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
