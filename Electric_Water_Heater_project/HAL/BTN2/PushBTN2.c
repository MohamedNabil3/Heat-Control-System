/*
* PushBTN0.c
*
* Created: 12/10/2021 11:06:41 AM
*  Author: karim
*/


#include "PushBTN2.h"


void BTN2_Initialization(void)
{
	DIO_SetPinDirection(BTN2_PORT, BTN2_PIN, BTN2_INP);
	DIO_SetPinPullUp(BTN2_PORT , BTN2_PIN);
}

uint8_t BTN2_Read(void)
{
	uint8_t val = 0;
	val = DIO_ReadPinValue(BTN2_PORT, BTN2_PIN);
	/*while(val == PRESSED)
	{
		val = DIO_ReadPinValue(BTN2_PORT, BTN2_PIN);
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
if(DIO_ReadPinValue(BTN2_PORT, BTN2_PIN) == PRESSED)
{
return PRESSED;
}
else
{
return NPRESSED;
}
*/