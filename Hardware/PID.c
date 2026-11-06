#include "stm32f10x.h"                  // Device header
 
typedef struct
{
	float KP;
	float KI;
	float KD;
	float Out;
	float OutMax;
	float OutMin;
	float Error;
	float ErrorLast;
	float ErrorInt;
	float ErrorIntMax;
	float ErrorIntMin;
	float Target;
	float Actual;
	
}PID_t;
void PID_Init(PID_t *P)
{
	P->Out=0;
	P->Target =0;
	P->Error =0;
	P->ErrorInt=0;
	P->ErrorLast=0;
}

void PID_Update(PID_t *P)
{	
	P->ErrorLast = P->Error;
    P->Error= P->Target - P->Actual;
	if(P->KI  !=0)
	{
        P->ErrorInt += P->Error;
	}
	else 
	{
		P->ErrorInt = 0; 
	}
	if(P->ErrorInt >= P->ErrorIntMax){P->ErrorInt = P->ErrorIntMax;}
	if(P->ErrorInt <= P->ErrorIntMin){P->ErrorInt = P->ErrorIntMin;}
    P->Out = P->KP * P->Error 
	       + P->KI * P->ErrorInt 
	       + P->KD * (P->Error - P->ErrorLast );  
	
	if(P->Out > P->OutMax){P->Out = P->OutMax;}
	if(P->Out < P->OutMin){P->Out = P->OutMin;}
  	

}
