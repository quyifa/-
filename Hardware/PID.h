#ifndef _PID_H_
#define _PID_H_
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

void PID_Update(PID_t *P);
void PID_Init(PID_t *P);
#endif
