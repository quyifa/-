#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"

//MyI2C_Start(void);
//void MyI2C_Stop(void);
//void MyI2C_SendByte(uint8_t Byte);
//uint8_t MyI2C_ReceiveByte(void);
//void MyI2C_SendAck(uint8_t Byte);
//uint8_t MyI2C_ReceiveAck(void);
#define MPU6050_ADDRESS         0xD0
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
	MyI2C_Start();                          //开始
	MyI2C_SendByte(MPU6050_ADDRESS);        //发送主机地址
	MyI2C_ReceiveAck();                     //接收应答
	MyI2C_SendByte(RegAddress);             //发送主机里要用的寄存器
	MyI2C_ReceiveAck();                     //接收应答
	MyI2C_SendByte(Data);                   //给寄存器发送数据
	MyI2C_ReceiveAck();                     //接收应答
	MyI2C_Stop();                           //停止
	
}
void MPU6050_ReadReg(uint8_t RegAddress,uint8_t *DataArray,uint8_t count)
{
	uint8_t i;
	MyI2C_Start();                                  //开始
	MyI2C_SendByte(MPU6050_ADDRESS);                //发送主机地址
	MyI2C_ReceiveAck();                             //接收应答
	MyI2C_SendByte(RegAddress);                     //发送主机里要用的寄存器
	MyI2C_ReceiveAck();                             //接收应答
	                                                 
	MyI2C_Start();                                   //开始
	MyI2C_SendByte(MPU6050_ADDRESS|0x01);            //发送主机地址并给最后一位写入是读还是写如操作，（0）写，（1）读。
	MyI2C_ReceiveAck();                              //接收应答
	for(i=0;i<count;i++)
	{
	   DataArray[i] = MyI2C_ReceiveByte();             //接收收据
		if(i<count-1)
		{			
	       MyI2C_SendAck(0);  
	    }
		else
		{
			MyI2C_SendAck(1); 
		}
	}                             
	MyI2C_Stop();                                    //停止
	                                                 
	                                      
}
void MPU6050_Init(void)
{
	MyI2C_Init();
	//配置寄存器
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);//向MPU6050_PWR_MGMT_1寄存器里面写入0x01；
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);
	MPU6050_WriteReg(MPU6050_CONFIG,0x00);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
    
}

 void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)
{
	uint8_t Data[14];
	MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H,Data,14);
	*AccX = Data[0]<<8|Data[1];
	*AccY = Data[2]<<8|Data[3];
	*AccZ = Data[4]<<8|Data[5];
	*GyroX= Data[8]<<8|Data[9];
	*GyroY= Data[10]<<8|Data[11];
	*GyroZ= Data[12]<<8|Data[13];
}	
//void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)
//{
	
//	uint16_t DataH;
//	uint16_t DataL;
	//读取加速度传感器的X值存入*AccX中
//	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
//	*AccX = (DataH<<8)|DataL;//本来DataH值在低八位左移8位后变为高八位然后|（与）DataL刚好
//	
//	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
//	  *AccY = (DataH<<8)|DataL;

//	
//	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
//	  *AccZ = (DataH<<8)|DataL;

//	
//	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
//	  *GyroX = (DataH<<8)|DataL;

//	
//	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
//	  *GyroY = (DataH<<8)|DataL;

//    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
//	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
//	  *GyroZ = (DataH<<8)|DataL;
 
//}      