/*
* USART.c
*
* Created: 1/1/2022 9:54:23 AM
*  Author: karim
*/

#include "USART.h"

USART_Status USART_Initialization(USART_Mode modes, USART_Parity parity, USART_StopBits stopbits, USART_Data data)
{
	/*
	BaudRate variable
	Choose mode
	Choose parity
	Choose stop bits
	Choose data
	Calculate Baudrate equation
	*/
	uint16_t UBRR_Val = 0;
	CLR_BIT(DDRD, PD0);//Rx
	SET_BIT(DDRD, PD1);//Tx
	UCSRB = (1 << RXEN) | ( 1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UBRR_Val = (((Freq) / (16 * BaudRate)) - 1 );
	UBRRL = UBRR_Val;
	UBRRH = UBRR_Val >> 8;
	return USART_OK;
}
USART_Status USART_Transmit_Character(uint8_t TrData)
{
	
	while (GET_BIT(UCSRA, UDRE) != 1);
	UDR = TrData;
	return USART_OK;
}
USART_Status USART_Receive_Character(uint8_t* ReData)
{
	while (GET_BIT(UCSRA, RXC) != 1);
	*ReData = UDR;
	return USART_OK;
}
USART_Status USART_Transmit_String(uint8_t* TrString)
{
	while (*TrString != '\0')
	{
		while(USART_Transmit_Character(*TrString) != USART_OK);
		TrString++;
	}
	return USART_OK;
}
/*USART_Status USART_Receive_String(uint8_t* ReString)
{
uint8_t receive = 0;
while (*ReString != '\0' )
{
while(USART_Receive_Character(&receive) != USART_OK);
*ReString += receive;
}
return USART_OK;
}*/

//another code for USART receive string
USART_Status USART_Receive_String(uint8_t* ReString)
{
	uint8_t receive = 0,i=0;
	while(USART_Receive_Character(&receive) != USART_OK);
	*(ReString+i) = receive;
	ReString[i]='\0';
	return USART_OK;
}