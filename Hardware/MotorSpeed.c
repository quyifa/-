#include "stm32f10x.h"                  // Device header

volatile uint16_t countA=0,countB=0;
void MotorSpeed_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4|GPIO_Pin_5;//23是读取编码器数，45是读取电机旋转方向；
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig (GPIO_PortSourceGPIOA,GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
		
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init (&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init (&NVIC_InitStructure);

}

int16_t   MotorspeedA_val(void )
{
	int16_t tmear;
	tmear=countA;
	countA=0;
	return tmear ;
}
int16_t   MotorspeedB_val(void )
{
	int16_t tmear;
	tmear=countB;
	countB=0;
	return tmear ;
}
void  EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)==SET )
	{
		if(GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_4 )==1)
		{
			countA++;
		}		
		else 
		{
			countA --;
		}
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}
void  EXTI3_IRQHandler(void )
	{
	if(EXTI_GetITStatus(EXTI_Line3)==SET )
	{
		if(GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_5 )==1)
		{
			countB++;
		}
		else 
		{
			countB --;
		}
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}