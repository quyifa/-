#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
   char SerialBluetooth_RxPacket[40];

   uint8_t SerialBluetooth_Flage =0;
   //配置蓝牙的基础配置
void SerialBluetooth_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//蓝牙用USART2；

	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//单片机的输入引脚对应串口的发送（tx）
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 USART_InitTypeDef USART_InitStructure; 
	 USART_InitStructure.USART_BaudRate = 9600;  //波特率
     USART_InitStructure.USART_WordLength = USART_WordLength_8b;//有数据位的大小（8或者9，8无校验位9有校验位）
     USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位的大小
     USART_InitStructure.USART_Parity = USART_Parity_No;//是否有校验位（若有分奇校验和偶校验）
     USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;//模式是接收还是发送或者接收和发送
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//数据流控（发送和接收都有，接收端会给发送端的数据流控发送信号发送端才能开始发送数据；；一般不用）
	 USART_Init(USART2, &USART_InitStructure);
	 
	 USART_ITConfig(USART2, USART_IT_RXNE,ENABLE);
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 
	 NVIC_InitTypeDef NVIC_InitStructure;
	 NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
     NVIC_Init(&NVIC_InitStructure);
	
  	 USART_Cmd(USART2, ENABLE);
	
}

//发送一个字节；
void SerialBluetooth_SendBite(uint8_t Byte)	
{
	USART_SendData(USART2,Byte);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//等待标志位，发送中标志位是RESET，等待发送完毕在进行下一步；
}

//发送数组；本质是每次发送一个字节；
void SerialBluetooth_SendArray(uint8_t *Array,uint16_t length)
{
	for(uint16_t i=0;i<length;i++)
	{
		SerialBluetooth_SendBite(Array[i]);
	}
}

//发送字符串；字符串的本质就是数组；
void SerialBluetooth_SendSrting(uint8_t *String)
{
     uint8_t i;
	for(i=0;String[i]!='\0';i++)
	{
		SerialBluetooth_SendBite(String[i]);
	}
}


uint32_t SerialBluetooth_pow(uint32_t x,uint32_t y)
{
	uint32_t Result = 1;
	while(y--)
	{
		Result*=x;
	}
		return Result;
}	


//发送数字；
void SerialBluetooth_SendNumber(uint32_t Num,uint16_t length)
{	 
	 for(uint16_t i=0;i<length;i++)
	{
		
		SerialBluetooth_SendBite(Num / SerialBluetooth_pow(10,length-i-1) % 10+'0');
	}	
	
}

//print打印到串口；
int fputc(int ch,FILE *f)//printf的底层把打印显示到串口
{
	SerialBluetooth_SendBite(ch);
	return ch;
}
 void SerialBluetooth_Printf(char *format,...)
{
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	SerialBluetooth_SendSrting(String);
}
uint8_t SerialBluetooth_Getflage(void)
{
	if(SerialBluetooth_Flage==1)
	{
		SerialBluetooth_Flage=0;
		return 1;
	}
	return 0;
}



//蓝牙/串口发送文本包；发送开启外部中断；
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)== SET)
	{
		static uint8_t Rxstare=0;
		static uint8_t Prxpacket=0;
		uint8_t RxData=USART_ReceiveData(USART2);//接收到的数据存到Rxdata里面；
		
		if(Rxstare == 0&&SerialBluetooth_Flage==0)//数据轴的顺序记录（Rxstare），SerialBluetooth_Flage等待上一次接收完在接收下一次；
		{
			if(RxData=='[')//RxData等于[它是包头；然后Rxstare==1；进行下一步；
			{
				Rxstare=1;
				Prxpacket=0;
			}			
		}
	    else if(Rxstare == 1)//Rxstare==1来到这一步，if  RxData是]来到了包尾，说明这个数据接收完毕赋SerialBluetooth_Flage为1；if没有就接收数据到数组里；
		{
			 
			if(RxData == ']')
			{
				Rxstare=0;
				SerialBluetooth_RxPacket [Prxpacket] = '\0';

				SerialBluetooth_Flage=1;
			}
			else
			{
			SerialBluetooth_RxPacket [Prxpacket] = RxData;
			Prxpacket++;
			}
		}
		
		
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}