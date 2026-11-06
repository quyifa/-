#ifndef _TRACKPID_H_
#define _TRACKPID_H_
void TrackPID_Init();
void Track_PID();
extern float KP,KI,KD;
extern float Error0,Error1,Interror;
extern float Actual,Target,Out;
extern uint8_t out1,out2,out3,out4,out5,out6,out7,out8,out9,out10,out11,out12;

#endif
