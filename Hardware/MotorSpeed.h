#ifndef _MOTORSPEED_H_
#define _MOTORSPEED_H_
void MotorSpeed_Init();
void  EXTI2_IRQHandler(void);
void  EXTI3_IRQHandler(void );
int16_t MotorspeedA_val(void );
int16_t MotorspeedB_val(void );

	
#endif
