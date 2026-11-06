#include "stm32f10x.h" 
#include "OLED.h"
#include "PC13LED.h"
#include "Delay.h"
#include "Timer.h"
#include "Key.h"
#include "MPU6050.h"
#include "Motor.h"
#include "MotorPWM.h"
#include "Encoder.h"
#include "SerialBluetooth.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "PID.h"
#include "TrackInit.h"
int16_t AX,AY,AZ,GX,GY,GZ,count,count1;
float AngleGuro,AngleAcc,Angle;
uint8_t KeyNum,RunFlag1,RunFlag2;
int16_t LeftPWM,RightPWM,AvePWM,DifPWM;
float  LeftSpeed,RightSpeed,AveSpeed,DifSpeed;
uint8_t out1,out2,out3,out4,out5,out6,out7,out8;
PID_t AnglePID = {
	.KP = 10.0,
	.KI = 0.3,
	.KD = 10.0,
	
	.OutMax = 70,
	.OutMin = -70,
	.ErrorIntMax = 220,
	.ErrorIntMin = -220,
};
PID_t SpeedPID = {
	.KP = 1.15,
	.KI = 0.1,
	.KD = 0,
	.Target=0,
	.OutMax = 20,
	.OutMin = -20,
	.ErrorIntMax = 200,
	.ErrorIntMin = -200,
	
};
PID_t TurnPID = {
	.KP = 4.0,
	.KI = 3.0,
	.KD = 0,
	.Target=0,
	.OutMax = 50,
	.OutMin = -50,
	.ErrorIntMax = 1.5,
	.ErrorIntMin = -1.5,
	
};
PID_t TrackPID = {
	.KP = 3,
	.KI = 0,
	.KD = 0.5,
	.Target=0,
	.OutMax = 70,
	.OutMin = -70,
	
	
};
int main(void)
{	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	
    OLED_Init();
	PC13LED_Init();
	Timer_Init();
	Key_Init();
	MPU6050_Init();
    Motor_Init();
	MotorPWM_Init();
	Encoder_Init();
    SerialBluetooth_Init();
	TrackSensor_Init();

   while(1)
	  {
/**********************************************循迹*************************************/	  
		  if(KeyNum == 2){RunFlag2 =! RunFlag2;}
		  if(RunFlag2 ){GPIO_WriteBit (GPIOA ,GPIO_Pin_1 ,0);}
			 out1 =GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_9 );
			 out2 =GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_10 );
			 out3 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_0 );
			 out4 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_1 );
			 out5 =GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_12 );	
			 out6 =GPIO_ReadInputDataBit(GPIOA ,GPIO_Pin_15 );
			 out7 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_3 );
			 out8 =GPIO_ReadInputDataBit(GPIOB ,GPIO_Pin_4 );
		  
/***********************************************************************************/	
/*如果按键一按下它的	PC13LED_ON   对应的灯就会亮，亮了代表程序在运行	  因为RunFlag1是   1   的时候灯才亮
  亮了之后初始化对应的PID防止上一次的值影响本次程序*/
		  if(RunFlag1 ){PC13LED_ON();}
		  else {PC13LED_OFF();}
		  
		  KeyNum  = Key_GetNum();
		  if(KeyNum == 1)
		  {
			 if(RunFlag1==0)
			 {
				 PID_Init(&AnglePID);                                                                                                                                              
				 PID_Init(&SpeedPID);
				 PID_Init(&TurnPID); 
				 RunFlag1 = 1;
			 }
			 else
			 {
				 RunFlag1 = 0 ;
			 }
		  }
 /*LED屏幕显示*/
		  OLED_Printf(0,0,OLED_6X8 ,"%s","Angle");
		  OLED_Printf(0,8,OLED_6X8 ,"KP:%05.2f",AnglePID.KP);
		  OLED_Printf(0,16,OLED_6X8 ,"KI:%05.2f",AnglePID.KI);
		  OLED_Printf(0,24,OLED_6X8 ,"KD:%05.2f",AnglePID.KD);
		  OLED_Printf(0,32,OLED_6X8 ,"Ta:%+05.1f",AnglePID.Target);
		  OLED_Printf(0,40,OLED_6X8 ,"Ac:%+05.1f",AnglePID.Actual);
		  OLED_Printf(0,48,OLED_6X8 ,"Ou:%+05.1f",AnglePID.Out);
		  
		  OLED_Printf(50,0,OLED_6X8 ,"%s","Speed");
		  OLED_Printf(50,8,OLED_6X8 ,":%05.2f",SpeedPID.KP);
		  OLED_Printf(50,16,OLED_6X8 ,":%05.2f",SpeedPID.KI);
		  OLED_Printf(50,24,OLED_6X8 ,":%05.2f",SpeedPID.KD);
		  OLED_Printf(50,32,OLED_6X8 ,":%+05.1f",SpeedPID.Target);
		  OLED_Printf(50,40,OLED_6X8 ,":%+05.1f",SpeedPID.Actual);
		  OLED_Printf(50,48,OLED_6X8 ,":%+05.1f",SpeedPID.Out);
		  
		  OLED_Printf(88,0,OLED_6X8 ,"%s","Turn");
		  OLED_Printf(88,8,OLED_6X8 ,":%05.2f",TurnPID.KP);
		  OLED_Printf(88,16,OLED_6X8 ,":%05.2f",TurnPID.KI);
		  OLED_Printf(88,24,OLED_6X8 ,":%05.2f",TurnPID.KD);
		  OLED_Printf(88,32,OLED_6X8 ,":%+05.1f",TurnPID.Target);
		  OLED_Printf(88,40,OLED_6X8 ,":%+05.1f",TurnPID.Actual);
		  OLED_Printf(88,48,OLED_6X8 ,":%+05.1f",TurnPID.Out);
		  
		  OLED_Update ();
 		  
/*蓝牙打印发送PID对应的参数	*/	  
		  
		   if(SerialBluetooth_Flage ==1 )//在SerialBluetooth接收到为1；进行下面操作；
		  {
			 char *Tag = strtok(SerialBluetooth_RxPacket,",");
			
			 if(strcmp (Tag,"slider")== 0)
			 {
				 char  *Nam = strtok (NULL,",");
				 char *val = strtok (NULL,",");
				 //Angle
				 if(strcmp(Nam,"AngleP") == 0)
				 {
					AnglePID.KP=atof(val);//atof表示把蓝牙发送过来的值变为浮点数类行的并赋值给对应的参数；
				 }
				 else if(strcmp(Nam,"AngleI") == 0)
				 {
					 AnglePID.KI=atof(val);
				 }	
				 else if(strcmp(Nam,"AngleD") == 0)
				 {
					AnglePID.KD=atof(val); 
				 }
				 //Speed
				 else if(strcmp(Nam,"SpeedP") == 0)
				 {
					SpeedPID.KP=atof(val);
				 }
				 else if(strcmp(Nam,"SpeedI") == 0)
				 {
					 SpeedPID.KI=atof(val);
				 }	
				 else if(strcmp(Nam,"SpeedD") == 0)
				 {
					SpeedPID.KD=atof(val); 
				 }
				 //Turn
				 else if(strcmp(Nam,"TurnP") == 0)
				 {
					TurnPID.KP=atof(val);
				 }
				 else if(strcmp(Nam,"TurnI") == 0)
				 {
					 TurnPID.KI=atof(val);
				 }	
				 else if(strcmp(Nam,"TurnD") == 0)
				 {
					TurnPID.KD=atof(val); 
				 }
				 //Track
				 else if(strcmp(Nam,"TrackP") == 0)
				 {
					TrackPID.KP=atof(val);
				 }
				 else if(strcmp(Nam,"TrackI") == 0)
				 {
					 TrackPID.KI=atof(val);
				 }	
				 else if(strcmp(Nam,"TrackD") == 0)
				 {
					TrackPID.KD=atof(val); 
				 }
				 SerialBluetooth_Flage = 0;//置标志位为零；
			 } 
			
		 //控制轮子的速度和转向
			 if(strcmp(Tag,"joystick")==0)//strcmp判断Tag是否与joystick相等，若相等返回值为0 反之为 1；
			  {
				  int8_t no1=atoi(strtok(NULL,","));
				  int8_t Angle_power=atoi(strtok(NULL,","));//strtok是分割。以“，”为标准分割数据；
				  int8_t Turn_power=atoi(strtok(NULL,","));//atoi是把阿斯克马值转换为int；	 
				  int8_t no2=atoi(strtok(NULL,","));
				  
				  SpeedPID.Target = -Angle_power;
				  TurnPID .Target = Turn_power;
				  
				  SerialBluetooth_Flage = 0;//置标志位为零；
		      }
		  
	    }
		  //发送数据打印到蓝牙屏幕上
		 SerialBluetooth_Printf("[plot,%f,%f,%f]",TurnPID.ErrorInt ,AnglePID .ErrorInt,SpeedPID.ErrorInt);
   }
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2 ,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM2 ,TIM_IT_Update);
		Key_Tick();//非堵塞式按键需要这个在定时中断里面
		count ++;
		//角度环10ms进行一次
		if(count>=10)
		{
			count = 0;
			MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);//用I2C读取陀螺仪和加速度；
			GX += 22;//Gx是陀螺仪，每次加22是因为它有静态误差需要校准；
		    AngleAcc = atan2(AY,AZ) / 3.1415926 * 180;//AngleAcc代表加速度最后换算为多少°；
			AngleGuro = Angle + GX / 32768.0 * 2000 * 0.01;/*AngleGuro代表的是陀螺仪  除32768是因为陀螺仪原始采样值为32768
			角度除32768就是在里面占了多少份  然后*2000是陀螺仪的量程就是+-2000   *0.1是因为这个定时器的中断时间就是0.01ms*/
		    
			float  a=0.01;
			Angle = a * AngleAcc + (1-a) * AngleGuro;//互补滤波
			
			if(Angle >35 || Angle <-35)//如果倾斜角度大于35，默认已经不可以自己回正，之后停止该程序；
			{
				RunFlag1 = 0;
			}
			if(RunFlag1 )
			{//进行PID调控
				AnglePID.Actual = Angle;
				PID_Update(&AnglePID);
				AvePWM = AnglePID.Out;//平均PWM只是调控直立，DifPWM是通过TurnPID进行调控然后加入到两个电机的最终的PWM上；
				LeftPWM = AvePWM - DifPWM /2; 
				RightPWM = AvePWM + DifPWM /2; 
				if(LeftPWM >100){LeftPWM = 100;}if(LeftPWM <-100){LeftPWM = -100;}	//进行PWM限幅防止输出值太大；
				if(RightPWM >100){RightPWM = 100;}if(RightPWM <-100){RightPWM = -100;}
				Motor_SetPWMA(LeftPWM);
				Motor_SetPWMB(RightPWM);
			}
			else
			{
				Motor_SetPWMA(0);
				Motor_SetPWMB(0);
			}			
		}	
		count1++;
        if(count1>=50)
		{//进行编码器电机的读取，调节速度PID
			count1 = 0;
			
			LeftSpeed = Encoder_Get(0)/44.0/0.05/9.27666;
			RightSpeed = Encoder_Get(1)/44.0/0.05/9.27666;
			
			AveSpeed =  (LeftSpeed + RightSpeed) / 2.0;
			DifSpeed = LeftSpeed - RightSpeed;
			
			if(RunFlag1)
			{  
				//循迹环
				if(RunFlag2)
                {  
					SpeedPID.Target = -2;//给速度一个值让它保持这个速度进行循迹；   
					TrackPID.Actual = (float)(6.5f)*out1
									 + (float)(5.5f)*out2
									 + (float)(3.5f)*out3
									 + (float)(1.0f)*out4//
									 + (float)(-1.0f)*out5//
									 + (float)(-3.5f)*out6
									 + (float)(-5.5f)*out7
									 + (float)(-6.5f)*out8;
									 /*循迹PID和转弯PID的串级PID*/
                     PID_Update(&TrackPID);								 
                     TurnPID.Target = TrackPID.Out;									 
				}
				/*速度环*****************速度环和角度环（直立环）的串级PID
				速度的目标值默认为0，和实际速度进行计算获得 SpeedPID.Out赋值给AnglePID.Target让角度环进行计算 */
				SpeedPID.Actual = AveSpeed;
				PID_Update(&SpeedPID);
				AnglePID.Target = SpeedPID.Out;
				
				//转向环******************调节转弯，也可以让左右轮速度保持一致
				TurnPID.Actual = DifSpeed;
				PID_Update(&TurnPID);
				DifPWM = TurnPID.Out;
			}

		}    		
	}	
}
