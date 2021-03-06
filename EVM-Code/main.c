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
#include <avr/interrupt.h>
#include <avr/signal.h>
#include "lcd.h"

volatile unsigned int   clock_millisecond=0;
#define START_TIMER0 TCCR1B=(1<<WGM12)|(1<<CS11)|(1<<CS10)
#define STOP_TIMER0  TCCR1B &= 0B11111000
#define CLEAR_TIMER0 TCNT0 = 0
int state = 0;
int intakeVote = 0;
int adminMode = 0;

int main(void){
	DDRB = 0x00;
	DDRC = 0xFF;
	DDRD = 0xFF;
	OCR1A=250;									//For TImer
	TIMSK|=(1<<OCIE1A);							//For Timer
	
	sei();								//Timer Globally defined
	_delay_ms(50);						//giving delay of 50ms
	
	
	 int16_t COUNTA = 0; // person1 votes storing memory
	 char SHOWA [16]; // person1 votes displaying character on LCD
	 int16_t COUNTB = 0;  // person2 votes storing memory
	 char SHOWB [16]; // person2 votes displaying character on LCD
	 int16_t COUNTC = 0; // person3 votes storing memory
	 char SHOWC [16]; // person3 votes displaying character on LCD
	 int16_t COUNTD = 0; // person4 votes storing memory
	 char SHOWD [16]; //person4 votes displaying character on LCD
	
	
	Lcd4_Init();
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("ShikharShikharShikharShikharShikharShikharShikharShikharShikhar");
    while (1) 
    {
		switch(state){
			case 0:
			if(!bit_is_clear(PINB,5)){
				adminMode = 1;
				state  = 2;
				Lcd4_Clear();
				Lcd4_Write_String("Admin Mode");
				_delay_ms(200);
			}else{
				
				if(!bit_is_clear(PINB, 4)){
					intakeVote = 1;
					Lcd4_Clear();
					Lcd4_Set_Cursor(1,1);
					Lcd4_Write_String("1:BJP 2:AAP");
					Lcd4_Set_Cursor(2,1);
					Lcd4_Write_String("3:CPI 4:TMC");
					START_TIMER0;
					state = 1;
					_delay_ms(200);
				}
			}
				break;
			case 1:
				
				if(!bit_is_clear(PINB,5)){
					intakeVote = 0;
					STOP_TIMER0;
					CLEAR_TIMER0;
					clock_millisecond = 0;
					Lcd4_Clear();
					state = 2;
					Lcd4_Clear();
					Lcd4_Write_String("Admin Mode");
					_delay_ms(200);
				
				}else{
					if(!bit_is_clear(PINB, 4)){
						intakeVote = 0;
						STOP_TIMER0;
						CLEAR_TIMER0;
						clock_millisecond = 0;
						Lcd4_Clear();
						state = 0;
						_delay_ms(200);
						
						}else{
						if(!bit_is_clear(PINB,0)){
							PORTC |= (1<<0);
							COUNTA++;
							STOP_TIMER0;
							state = 0;
							Lcd4_Clear();
							}else if(!bit_is_clear(PINB,1)){
							PORTC |= (1<<1);
							COUNTB++;
							STOP_TIMER0;
							state = 0;
							Lcd4_Clear();
							}else if(!bit_is_clear(PINB,2)){
							PORTC |= (1<<2);
							COUNTC++;
							STOP_TIMER0;
							state = 0;
							Lcd4_Clear();
							}else if(!bit_is_clear(PINB,3)){
							PORTC |= (1<<3);
							COUNTD++;
							STOP_TIMER0;
							state = 0;
							Lcd4_Clear();
						}
						
					}
					
				}
				break;
			case 2:
				if(!bit_is_clear(PINB,5)){
					intakeVote = 0;
					adminMode = 0;
					Lcd4_Clear();
					state = 0;
					_delay_ms(200);
				}else{
					if(!bit_is_clear(PINB,6)){
						Lcd4_Clear();
						COUNTA = 0;
						COUNTB = 0;
						COUNTC = 0;
						COUNTD = 0;
						Lcd4_Write_String("Resetting");
					}else if(!bit_is_clear(PINB,7)){
						Lcd4_Clear();
						itoa(COUNTA,SHOWA,10);
						itoa(COUNTB,SHOWB,10);
						itoa(COUNTC,SHOWC,10);
						itoa(COUNTD,SHOWD,10);
						
						strcat(SHOWA,"");
						strcat(SHOWA,SHOWB);
						strcat(SHOWA,SHOWC);
						strcat(SHOWA,SHOWD);
						Lcd4_Set_Cursor(1,1);
						Lcd4_Write_String(SHOWA);
					}
				}
				break;
				
				
		}
	}
	
	
	
	
}


ISR(TIMER1_COMPA_vect){
	clock_millisecond++;
	if(clock_millisecond == 10000){
		intakeVote = 0;
		STOP_TIMER0;
		CLEAR_TIMER0;
		clock_millisecond = 0;
		Lcd4_Clear();
		state = 0;
	}
}