/*
 * USART.h
 *
 * Created: 1/1/2022 9:54:16 AM
 *  Author: karim
 */ 


#ifndef USART_H_
#define USART_H_

#include "USART_Configuration.h"

USART_Status USART_Initialization(USART_Mode modes, USART_Parity parity, USART_StopBits stopbits, USART_Data data);
USART_Status USART_Transmit_Character(uint8_t TrData);
USART_Status USART_Receive_Character(uint8_t* ReData);
USART_Status USART_Transmit_String(uint8_t* TrString);
USART_Status USART_Receive_String(uint8_t* ReString);


#endif /* USART_H_ */