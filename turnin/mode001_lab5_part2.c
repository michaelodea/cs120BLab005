/*	        Name & E-mail: Michael O'Dea, mode001
 *	 	Lab Section: 025 
 *	  	Assignment: Lab #4  Exercise #2 
 *	   	Exercise Description: Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. Pressing 
 *	   	PA0 increments PORTC once (stopping at 9). Pressing PA1 decrements PORTC once (stopping at 0). If 
 *	   	both buttons are depressed (even if not initially simultaneously), PORTC resets to 0.
 *	    	
 *	     	I acknowledge all content contained herein, excluding template or example
 *	      	code, is my own original work.
 */

//DEMO: https://drive.google.com/open?id=15gH0jOW6dVBCxkgPvWUCiVd7zOth2JLA


#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{BEGIN, INITIAL, ADD, MINUS, waitADD, waitMINUS, RESET} state;

unsigned char A0;
unsigned char A1;


void Tick(){

	A0 = (~PINA & 0x01);
	A1 = (~PINA & 0x02);

	switch(state){
		case BEGIN:
		state = INITIAL;
		break;
		
		case INITIAL:
		if(A0 && !A1){
			state = ADD;
		}
		else if(!A0 && A1){
			state = MINUS;
		}
		else if(A0 && A1){
			state = RESET;
		}
		else{
			state = INITIAL;
		}
		break;

		case ADD:
              	state = waitADD;
		break;
			
		case MINUS:
		state = waitMINUS;			
		break;
		
		case waitADD:
		if(!A0 && !A1){
			state = INITIAL;
		}
		else if(A0 && A1){
			state = RESET;
		}
		else{
			state = waitADD;
		}
		break;

		case waitMINUS:
		if(!A0 && !A1){
			state = INITIAL;
		}
		else if(A0 && A1){
			state = RESET;
		}
		else{
			state = waitMINUS;
		}
		break;

		case RESET:
		state = waitMINUS;
		break;
	
		default:
		state = BEGIN;
		break;
	}


	switch(state){
		case BEGIN:
		break;

		case INITIAL:
		break;

		case ADD:
		if(PORTC < 9){
			PORTC = PORTC + 1;
		}
		else{
			PORTC = 0x09;
		}
		break;

		case MINUS:
		if(PORTC > 0){
			PORTC = PORTC - 1;
		}
		else{
			PORTC = 0x00;
		}
		break;
		
		case waitADD:
		break;
		
		case waitMINUS:
		break;
		
		case RESET: 
		PORTC = 0x00;
		break;
	}

}
int main(void) {

    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    state = BEGIN;
    PORTC = 0x00;
    while (1) {
		Tick();
    }
    return 1;
}



