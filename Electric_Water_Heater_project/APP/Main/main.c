
#include "main.h"
//variables initialization

uint8_t btn1_read_;
uint8_t btn0_read_;
uint8_t power_flag=0;
uint8_t first_push_flag=0;
uint8_t degree=58;
uint8_t test=0;
uint8_t heat_flag=0;
uint8_t degree_addr = 64;
uint8_t access_flag=0;
fint32_t current_temp=0;
uint16_t last_10_temp[10] = {0,0,0,0,0,0,0,0,0,0};
uint8_t temp_index = 0;
uint8_t blink_7_segment = 0;
uint8_t relay_flag=0;

extern void sitting_temp(uint8_t,uint8_t);
extern float calcualate_avg_temp(uint16_t* arr);
extern void check_first_push(void);
extern void compare_temp(void);

int main(){
	
	Interrupt_Initialization(INT0_Signal);
	Timer0_WithInterrupt_Initialization(Normal_Mode,Pin_disconnected);
	Timer2_WithInterrupt_Initialization(Normal_Mode_ , Pin_disconnected_);
	ADC_Initialization(ADC1);
	BTN0_Initialization();
	BTN1_Initialization();
	LED0_Initialization();
	LED1_Initialization();
	LED2_Initialization();
	Relay_Initialization();
	
	/* Replace with your application code */
	while (1)
	{
		btn1_read_ = BTN1_Read();	//get button1 read
		btn0_read_ =BTN0_Read();	//get button0 read
		
		//check if the device is on or off
		if (power_flag==0);	//if off do noting
		
		else{	//if on
			if (access_flag==1)	//if there is a value in EEPROM put it into degree
			{
				degree=EEPROM_Read(degree_addr);
			}
			
			Timer2_Start(PreS_1024_);	//start timer2 to get the ADC read every 100 ms
			Timer2_WithInterrupt_SetDelay(Normal_Mode_ , 100 , 255);
			check_first_push();
			compare_temp();			
			if (first_push_flag==0)	//display the set_temp(degree) if the device isn't in setting mode
			{
				// LCD_Clear();
				// LCD_Write_Number(current_temp);
				SEVSEG_Display(current_temp);
			}
		}
		
	}
	return 0;
}






