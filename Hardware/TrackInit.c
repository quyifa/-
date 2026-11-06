#include "stm32f10x.h"                  // Device header



void TrackSensor_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); 
	
	GPIO_InitTypeDef GPIO_Initstructure ;
	
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin= GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_15|GPIO_Pin_12;
	GPIO_Initstructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin= GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
//	 //红外引脚读取
//		 out1 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_6 );//右
//	     out2 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_5 );
//	     out3 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_4 );
//	     out4 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_3 );
//	     out5 =GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_15 );
//	
//	     out6 =GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_12 );
//	     out7 =GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_11 );
//	
//	     out8 =GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_8 );//左
//	     out9 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_15 );
//	     out10 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_14 );
//	     out11 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_13 );
//	     out12 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_12 );
//	     //0   灯亮
}
