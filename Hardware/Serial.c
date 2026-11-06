#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
uint8_t Serial_RxData;
uint8_t Serial_Flage;
void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 USART_InitTypeDef USART_InitStructure;
	 USART_InitStructure.USART_BaudRate = 9600;  //波特率
     USART_InitStructure.USART_WordLength = USART_WordLength_8b;//有数据位的大小（8或者9，8无校验位9有校验位）
     USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位的大小
     USART_InitStructure.USART_Parity = USART_Parity_No;//是否有校验位（若有分奇校验和偶校验）
     USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//模式是接收还是发送或者接收和发送
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//数据流控（发送和接收都有，接收端会给发送端的数据流控发送信号发送端才能开始发送数据；；一般不用）
	 USART_Init(USART1, &USART_InitStructure);
	 
	 USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 
	 NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
     NVIC_Init(&NVIC_InitStructure);
	
  	 USART_Cmd(USART1, ENABLE);
	
}
void Serial_SendBite(uint8_t Byte)	
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}
void Serial_SendArray(uint8_t *Array,uint16_t length)
{
	for(uint16_t i=0;i<length;i++)
	{
		Serial_SendBite(Array[i]);
	}
}
void Serial_SendSrting(uint8_t *String)
{
     uint8_t i;
	for(i=0;String[i]!='\0';i++)
	{
		Serial_SendBite(String[i]);
	}
}


uint32_t Serial_pow(uint32_t x,uint32_t y)
{
	uint32_t Result = 1;
	while(y--)
	{
		Result*=x;
	}
		return Result;
}	

void Serial_SendNumber(uint32_t Num,uint16_t length)
{	 
	 for(uint16_t i=0;i<length;i++)
	{
		
		Serial_SendBite(Num / Serial_pow(10,length-i-1) % 10+'0');
	}	
	
}
int fputc(int ch,FILE *f)//printf的底层把打印显示到串口
{
	Serial_SendBite(ch);
	return ch;
}
 void Serial_Printf(char *format,...)
{
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendSrting(String);
}
uint8_t Serial_Getflage(void)
{
	if(Serial_Flage==1)
	{
		Serial_Flage=0;
		return 1;
	}
	return 0;
}
uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)== SET)
	{
		
		Serial_RxData= USART_ReceiveData(USART1);
		Serial_Flage=1;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}