/*
 * GccApplication1.c
 *
 * Created: 3/24/2016 1:02:09 PM
 * Author : Dexter
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


int main(void)
{
	DDRB = 0x00;
	DDRC = 0xFF;
	DDRD = 0xFF;
	_delay_ms(50); //giving delay of 50ms
	
	 int16_t COUNTA = 0; // person1 votes storing memory
	 char SHOWA [16]; // person1 votes displaying character on LCD
	 int16_t COUNTB = 0;  // person2 votes storing memory
	 char SHOWB [16]; // person2 votes displaying character on LCD
	 int16_t COUNTC = 0; // person3 votes storing memory
	 char SHOWC [16]; // person3 votes displaying character on LCD
	 int16_t COUNTD = 0; // person4 votes storing memory
	 char SHOWD [16]; //person4 votes displaying character on LCD
	
	
	Lcd4_Init();
	int state = 0;
	int intakeVote = 0;
	int timer = 4; 
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,1);
    while (1) 
    {
		switch(state){
			case 0:
				if(!bit_is_clear(PINB, 4)){
					intakeVote = 1;
					Lcd4_Clear();
					Lcd4_Set_Cursor(1,1);
					Lcd4_Write_String("Please cast your vote");
					state = 1;
				}
				break;
			case 1:
				if(timer >15){
					Lcd4_Clear();
					Lcd4_Set_Cursor(1,1);
					Lcd4_Write_String("Error : Time Limit Exceeded!");
					state = 0;
				}else if(intakeVote == 0){
					Lcd4_Clear();
					Lcd4_Set_Cursor(1,1);
					Lcd4_Write_String("Error : Not Authorised!");
					state = 0;
				}else if(intakeVote == 1){
					if(!bit_is_clear(PINB,0)){
						COUNTA++;
						state = 0;
						Lcd4_Clear();
					}else if(!bit_is_clear(PINB,1)){
						COUNTB++;
						state = 0;
						Lcd4_Clear();
					}else if(!bit_is_clear(PINB,2)){
						COUNTC++;
						state = 0;
						Lcd4_Clear();
					}else if(!bit_is_clear(PINB,3)){
						COUNTD++;
						state = 0;
						Lcd4_Clear();
					}
					
				}
					
				
				break;
				
				
		}
	}
	
	
	
}

