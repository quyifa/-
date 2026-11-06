#include "stm32f10x.h"                  // Device header
#include "TrackInit.h"
float KP,KI,KD;
float Error0,Error1,Interror;
extern float Actual,Target,Out;
extern uint8_t out1,out2,out3,out4,out5,out6,out7,out8,out9,out10,out11,out12;
void TrackPID_Init()
{
	TrackSensor_Init();
	
	
}
void Track_PID()
{
	KP =10;
	KI =0;
	KD =100;
	Target = 0.0;
    Actual =((float)(10.0f)*out12 +(float)(9.0f)*out11 +(float)(7.0f)*out10 +(float)(5.0f)*out9 +(float)(3.0f)*out8 +(float)(1.0f)*out7+(float)(-1.0f)*out6 +(float)(-3.0f)*out5 +(float)(-5.0f)*out4 +(float)(-7.0f)*out3 +(float)(-9.0f)*out2 +(float)(-10.0f)*out1);
//    if(out12==1 & out11==0)
//	{
//		Actual=11;
//	}
//	if(out1==1 & out2==0)
//	{
//		Actual=-11;
//	}
	
//	if(Actual >12|Actual <-12){Actual =12;}
		
	Error1=Error0;
	
    Error0= Target - Actual;
    
    Out = KP *Error0 +KI *Interror +KD *(Error0 - Error1 );  
	
    Out =Out *5;	
//	if(out12==0&&out11==0)
//	{
//	if(Out >34.5){Out =34.5;}
//    if(Out <-34.5){Out =-34.5;}
//    }
//	else
//	{
//		if(Out >36){Out =36;}
//        if(Out <-36){Out =-36;}
//	}
//	if(out12==1&&out11==0)
//	{
	if(Out >260){Out =260;}
    if(Out <-260){Out =-260;}
//    }
//	if(out12==1&&out11==1&&out10 ==1)
//	{
//	if(Out >40){Out =40;}
//    if(Out <-40){Out =-40;}
    //}
}
