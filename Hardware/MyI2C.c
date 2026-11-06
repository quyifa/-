#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#define  SCL_PORT         GPIOB
#define  SCL_Pin          GPIO_Pin_10
//写入
 
 void MyI2C_W_SCL(uint8_t BitVal)//写入SCL高低电平
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction) BitVal);
}
void MyI2C_W_SDA(uint8_t BitVal)//写入SDA高低电平
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction) BitVal);
}
uint8_t MyI2C_R_SDA(void)//接收从机发送的字符
{
	uint8_t BitValue;
	BitValue=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	return BitValue;
}
void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
}
//开始：SDA和SCL分别拉高电瓶，然后SDA和SCL拉低电瓶
void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);	
    MyI2C_W_SDA(0);	
	MyI2C_W_SCL(0);	
}
//停止：SDA先拉低电瓶，然后SCL和SDA拉高店平
void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);	
	MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);		
}
//发送：发送8位字符，然后SCL先拉高在拉低
void MyI2C_SendByte(uint8_t Byte)
{
	for(uint8_t i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte & (0x80>>i));//每一次只能读取一位，如第一次循环读取Byte高位&0x80（1000  0000），第一位非0及1，1&1还是1，然后0x80右移一位，开始下一位。
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);	
	}
}
//接收：先要让SDA拉高把SDA限权交给从机，SCL拉高 Byte接收字符 SCL拉低
uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t Byte=0x00;
	MyI2C_W_SDA(1);
	for(uint8_t i=0;i<8;i++)
	{
		 MyI2C_W_SCL(1);
		 if( MyI2C_R_SDA()==1){Byte|=(0x80>>i);}//MyI2C_R_SDA()==1代表接收到一个高电平（1）| 0x80，1|1=1如果是0直接补0跳出循环进行下一次运算。
		 MyI2C_W_SCL(0);	
	}
	return Byte;
}
//发送应答：发送一个信号，然后拉高SCL在拉低。
void MyI2C_SendAck(uint8_t BytAck)
{
	    MyI2C_W_SDA(BytAck);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);	
}
//接收应答：先拉高SDA转换权限，然后拉高SCL，接收信号，拉低SCL。
uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t Ack ;
	MyI2C_W_SDA(1);	 
	MyI2C_W_SCL(1);
    Ack=MyI2C_R_SDA();
	MyI2C_W_SCL(0);	
	return Ack;
}
