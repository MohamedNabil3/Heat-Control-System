/*
* Functions.c
*
* Created: 2/13/2022 3:59:58 PM
*  Author: moham
*/

#include "main.h"
extern uint8_t btn1_read_;
extern uint8_t btn0_read_;
extern uint8_t power_flag;
extern uint8_t first_push_flag;
extern uint8_t degree;
extern uint8_t test;
extern uint8_t heat_flag;
extern uint8_t degree_addr;
extern uint8_t access_flag;
extern fint32_t current_temp;
extern uint16_t last_10_temp[10];
extern uint8_t temp_index ;
extern uint32_t Timer2_OVF;
extern uint32_t Number_OVF;
extern uint8_t blink_7_segment;
extern uint8_t relay_flag;



void sitting_temp(uint8_t,uint8_t);
float calcualate_avg_temp(uint16_t* arr);
void check_first_push(void);
void compare_temp(void);
//===============================================================================================

ISR(INT0_vect){		//interrupt when pushing BTN2
	power_flag^=1;
	if(power_flag==0){	//if the device is off
		//	turn off all displays & stop timers 
		LED0_OFF();
		LED1_OFF();
		LED2_OFF();
		Timer0_Stop();
		Timer2_Stop();
		first_push_flag=0;
		SEVSEG_Disable1();
		SEVSEG_Disable2();
		SEVSEG_Dot_Disable();
		//LCD_disable();
	}
	else {		//if the device is on
		LED0_ON();
		SEVSEG_Initialization();
		//LCD_Initialization();
		test=1;	//to reset the counter

	}
}


//===============================================================================================


ISR(TIMER0_OVF_vect){
										//the delay will be 5000 milisec
	static uint32_t cnt=0;	
	if(test==1){	//restart count from 0 if user press the buttons 0 or 1
		cnt=0;
		test=0;
		blink_7_segment=1;		
	}
	if( blink_7_segment )	// if the flag blink_7_segment = 1 initialize 7_segment and display the set_temp
	{
		SEVSEG_Initialization();
		SEVSEG_Display(degree);
	}
	else        // if the flag blink_7_segment = 0 disable 7_segment
	{
		SEVSEG_Disable1();
		SEVSEG_Disable2();
	}

	if(cnt==Number_OVF){		//if counter reach number of overflows
		SEVSEG_Initialization();	//initialize 7_segment if it is disable
		Timer0_Stop();			//stop the timer
		first_push_flag=0;		//clr flag
		blink_7_segment=0;		//clr flag
		cnt=0;					//make  counter =0
	}
	
	else if(cnt%(Number_OVF/5)==0){		//every 1 sec blink 7_segment
		blink_7_segment ^= 1;
	}
	cnt++;
}


//===============================================================================================


ISR(TIMER2_OVF_vect)
{
	static uint32_t timer2_count = 0;
	
	if(timer2_count < Timer2_OVF)
	{
		timer2_count++;
	}
	else
	{
		// ADC read
		last_10_temp[temp_index] = (500.0 * ADC_Read()) / 1024.0 ; // degree
		temp_index++;

		if(temp_index > 9)
		{
			temp_index = 0;		//reset index every 10 reads
			current_temp=calcualate_avg_temp(last_10_temp);		//get the avg
			if (heat_flag==1)	//if the heating element is on blink led1 every 1 sec
			{
				LED1_TGL();
			}
		}
		timer2_count = 0;

	}
}


//===============================================================================================

void check_first_push(void){
	
	if((first_push_flag==0&&btn0_read_==PRESSED)||(first_push_flag==0&&btn1_read_==PRESSED)){	//check if buttons are clicked for the first time to enter setting mode
		first_push_flag=1;	//raise the flag
		blink_7_segment = 1;
		Timer0_Start(PreS_1024);	//start timer0 so that if 5 seconds spend without using buttons ,exit setting mode
		Timer0_WithInterrupt_SetDelay(Normal_Mode,5000,255);
	}
	else
	{	//if this isn't the first click call the function of setting mode
		if( (btn0_read_==PRESSED) ||(btn1_read_==PRESSED) ){
			sitting_temp(btn0_read_,btn1_read_);	
		}
	}
	
}

//================================================


//change set_temp(degree)
void sitting_temp(uint8_t btn0_read_,uint8_t btn1_read_){
	if(btn0_read_==PRESSED&&degree<75){		//if BTN0 is pressed
		degree+=5;
		EEPROM_Write(degree_addr , degree); // Saving new temperature on EEPROM
		access_flag=1;		//raise flag
		test=1;	//if user press the button make test = 1 to restart the counter in Timer0
		Timer0_Stop();
		Timer0_Start(PreS_1024);
		Timer0_WithInterrupt_SetDelay(Normal_Mode,5000,255);
	}
	else if(btn1_read_==PRESSED&&degree>35) {		//if BTN1 is pressed
		degree-=5;
		EEPROM_Write(degree_addr , degree); // Saving desired temperature on EEPROM
		access_flag=1;
		test=1;
		Timer0_Stop();
		Timer0_Start(PreS_1024);
		Timer0_WithInterrupt_SetDelay(Normal_Mode,5000,255);
	}
	else if((btn1_read_==PRESSED&&degree==35)||(btn0_read_==PRESSED&&degree==75)) {		//this condition to indicate that degree must be in range 35 to 75
		test=1;
		Timer0_Stop();
		Timer0_Start(PreS_1024);
		Timer0_WithInterrupt_SetDelay(Normal_Mode,5000,255);
	}

}


//===============================================================================================

//get the avg temp of the last 10 reads of ADC
float calcualate_avg_temp(uint16_t* arr)
{
	uint16_t sum = 0;
	
	for(uint8_t i = 0 ; i < 10 ; i++)
	{
		sum += arr[i];
	}
	
	return (float ) sum / (float ) 10;
}

//===============================================================================================

void compare_temp(void){
	
	//compare the current temp with set_temp
	
	if (current_temp == degree)
	{
		LED1_OFF(); // Heating element off
		LED2_OFF(); // Cooling element off
		heat_flag=0;	//clr flag of heating element
		if (relay_flag==0)
		{
			Relay_ON();
			_delay_ms(10);
			Relay_OFF();
			relay_flag=1;// raise the flag so that relay will not operate again
		}

	}
	else if(current_temp<=degree-5){
		heat_flag=1;	//raise flag of heating element
		relay_flag=0;	//reset the flag of relay
		LED2_OFF(); // Cooling element off
	}
	else if (current_temp>=degree+5)
	{
		heat_flag=0;	//raise flag of heating element
		relay_flag=0;
		LED1_OFF(); // Heating element off
		LED2_ON(); // Cooling element on
	}
	
}

//======================================================