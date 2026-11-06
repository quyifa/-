#include "stm32f10x.h"                  // Device header

void Encoder_Init(void)
{
	/*编码器A 用TIM3*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//A相 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;    //ARR周期
    TIM_TimeBaseInitStructure.TIM_Prescaler= 1-1;    //PSC预分频器
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//A
	
	
	
	//输入捕获单元配置(只有下面几个有用，所以其他的直接默认配置）
	//A相
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;	
    TIM_ICInit(TIM3, &TIM_ICInitStructure);	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;	
    TIM_ICInit(TIM3, &TIM_ICInitStructure);	
	
	
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Rising);
	
	
	TIM_ClearFlag (TIM3 ,TIM_FLAG_Update );
    
	
	TIM_SetCounter(TIM3, 0);
	

	TIM_Cmd(TIM3,ENABLE);
	
	/*编码器B，用TIM4*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Period = 65536-1;    //ARR周期
    TIM_TimeBaseInitStructure.TIM_Prescaler= 1-1;    //PSC预分频器
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//B
	
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;	
    TIM_ICInit(TIM4, &TIM_ICInitStructure);	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;	
    TIM_ICInit(TIM4, &TIM_ICInitStructure);	
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);
	
	TIM_ClearFlag (TIM4 ,TIM_FLAG_Update );
	
	TIM_SetCounter(TIM4, 0);
	
	TIM_Cmd(TIM4,ENABLE);
}

//测量速度
int16_t Encoder_Get(uint8_t n)
{
	if(n==0)
	{
		int16_t Temp;
		Temp=TIM_GetCounter(TIM3);//存入Temp后TIM_GetCounter(TIM3)为0
		TIM_SetCounter(TIM3, 0);	
		return Temp;
    }
	if(n==1)
	{
		int16_t Temp;
		Temp=TIM_GetCounter(TIM4);//存入Temp后TIM_GetCounter(TIM4)为0
		TIM_SetCounter(TIM4, 0);	
		return Temp;
    }
}
