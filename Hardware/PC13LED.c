#include "stm32f10x.h"                  // Device header


void PC13LED_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits (GPIOC ,GPIO_Pin_13 );
	GPIO_SetBits (GPIOA ,GPIO_Pin_1 );
}
void PC13LED_ON(void )
{	
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,0);     
}
void PC13LED_OFF(void)
{	
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,1);     
}
void LED_Turn ()
{
	if(GPIO_ReadOutputDataBit(GPIOC ,GPIO_Pin_13 )==0)
	{
		GPIO_SetBits (GPIOC ,GPIO_Pin_13 );
	}
	else 
	{
		GPIO_ResetBits (GPIOC ,GPIO_Pin_13 );
	}
}