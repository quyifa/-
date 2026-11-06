#include "stm32f10x.h"                  // Device header
#include "MotorPWM.h"

void Motor_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin= GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Initstructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_12|GPIO_Pin_13);
}


void Motor_SetPWMA(int16_t PWM)//可以调节PWMA
{
	if(PWM>=0)
	{
		GPIO_ResetBits(GPIOB,  GPIO_Pin_14);
        GPIO_SetBits(GPIOB,  GPIO_Pin_15);
		MotorPWM_SetCompareA(PWM);
	}
	else
	{
		GPIO_ResetBits(GPIOB,  GPIO_Pin_15);
        GPIO_SetBits(GPIOB,  GPIO_Pin_14);
		MotorPWM_SetCompareA(-PWM);
	}
}
void Motor_SetPWMB(int16_t PWM)
{
	if(PWM>=0)
	{
		GPIO_ResetBits(GPIOB,  GPIO_Pin_13);
        GPIO_SetBits(GPIOB,  GPIO_Pin_12);
		MotorPWM_SetCompareB(PWM);
	}
	else
	{
		GPIO_ResetBits(GPIOB,  GPIO_Pin_12);
        GPIO_SetBits(GPIOB,  GPIO_Pin_13);
		MotorPWM_SetCompareB(-PWM);
	}
}
