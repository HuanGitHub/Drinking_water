
/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"
//����LED�������ӿ�
#define LED_GPIO_PORT  GPIOD
#define LED_GPIO_PINS  GPIO_Pin_0
#define KEY_GPIO_PORT  GPIOB
#define KEY_GPIO_PINS  GPIO_Pin_1
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
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED��GPD0�����������
    
    GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ��������GPB1��������
    GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode_In_PU_IT);//��ʼ��������GPB1��������
    EXTI_DeInit (); //�ָ��жϵ��������� 
    EXTI_SetPinSensitivity (EXTI_Pin_1,EXTI_Trigger_Falling);//�ⲿ�ж�1���½��ش������ж�������9
    
    enableInterrupts();//ʹ���ж�
   
    while(1)
    {
        

    }

}
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/