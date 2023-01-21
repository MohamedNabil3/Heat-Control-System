/*
* PushBTN0.c
*
* Created: 12/10/2021 11:06:41 AM
*  Author: karim
*/


#include "PushBTN0.h"


void BTN0_Initialization(void)
{
	DIO_SetPinDirection(BTN0_PORT, BTN0_PIN, BTN0_INP);
	DIO_SetPinPullUp(BTN0_PORT , BTN0_PIN);
}

uint8_t BTN0_Read(void)
{
	uint8_t val = 0;
	val = DIO_ReadPinValue(BTN0_PORT, BTN0_PIN);
	/*while(val == PRESSED)
	{
		val = DIO_ReadPinValue(BTN0_PORT, BTN0_PIN);
		if (val==NPRESSED)
		{
			val=PRESSED;
			break;
		}
	}*/
	_delay_ms(10);
	return val;
}


/*
uint8_t values = NPRESSED;
_delay_ms(10);
if(DIO_ReadPinValue(BTN0_PORT, BTN0_PIN) == PRESSED)
{
return PRESSED;
}
else
{
return NPRESSED;
}
*/