#ifndef _SERIAL_H_
#define _SERIAL_H_
#include <stdio.h>

void Serial_Init(void);
void Serial_SendBite(uint8_t Byte);
void Serial_SendArray(uint8_t *Array,uint16_t length);
void Serial_SendSrting(uint8_t *String);
uint32_t Serial_pow(uint32_t x,uint32_t y);
void Serial_SendNumber(uint32_t Num,uint16_t length);
void Serial_Printf(char *format,...);
void USART1_IRQHandler(void);
uint8_t Serial_Getflage(void);
uint8_t Serial_GetRxData(void);

#endif
