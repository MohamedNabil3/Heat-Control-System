/*
* PushBTN0.c
*
* Created: 12/10/2021 11:06:41 AM
*  Author: karim
*/


#include "PushBTN1.h"


void BTN1_Initialization(void)
{
	DIO_SetPinDirection(BTN1_PORT, BTN1_PIN, BTN1_INP);
	DIO_SetPinPullUp(BTN1_PORT , BTN1_PIN);
}

uint8_t BTN1_Read(void)
{
	uint8_t val = 0;
	val = DIO_ReadPinValue(BTN1_PORT, BTN1_PIN);
	/*while(val == PRESSED)
	{
		val = DIO_ReadPinValue(BTN1_PORT, BTN1_PIN);
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
if(DIO_ReadPinValue(BTN1_PORT, BTN1_PIN) == PRESSED)
{
return PRESSED;
}
else
{
return NPRESSED;
}
*/