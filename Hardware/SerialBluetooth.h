#ifndef _SerialBLUETOOTH_H_
#define _SerialBLUETOOTH_H_
#include <stdio.h>

extern char SerialBluetooth_RxPacket[];
extern uint8_t SerialBluetooth_TxPacket[];
void SerialBluetooth_Init(void);
void SerialBluetooth_SendBite(uint8_t Byte);
void SerialBluetooth_SendArray(uint8_t *Array,uint16_t length);
void SerialBluetooth_SendSrting(uint8_t *String);
uint32_t SerialBluetooth_pow(uint32_t x,uint32_t y);
void SerialBluetooth_SendNumber(uint32_t Num,uint16_t length);
void SerialBluetooth_Printf(char *format,...);
void USART1_IRQHandler(void);
uint8_t SerialBluetooth_Getflage(void);
extern char SerialBluetooth_RxPacket[];
extern uint8_t SerialBluetooth_Flage;

#endif
