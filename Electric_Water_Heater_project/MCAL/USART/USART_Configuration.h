/*
* USART_Configuration.h
*
* Created: 1/1/2022 9:54:07 AM
*  Author: karim
*/


#ifndef USART_CONFIGURATION_H_
#define USART_CONFIGURATION_H_

#include "Configuration.h"

#define Freq 160000
#define BaudRate 96

//USART Mode
typedef enum
{
	Synchronous = 0,
	Asynchronous = 1
}USART_Mode;
//USART Parity
typedef enum
{
	Disable = 0,
	Odd_EN = 1,
	Even_EN = 2
}USART_Parity;
//USART Stop bits
typedef enum
{
	Bit_1 = 0,
	Bit_2 = 1
}USART_StopBits;
//USART Data
typedef enum
{
	Bits_5 = 0,
	Bits_6 = 1,
	Bits_7 = 2,
	Bits_8 = 3,
	Bits_9 = 4,
}USART_Data;
//USART Status
typedef enum
{
	USART_OK = 0,
	USART_NOK = 1
}USART_Status;

#endif /* USART_CONFIGURATION_H_ */