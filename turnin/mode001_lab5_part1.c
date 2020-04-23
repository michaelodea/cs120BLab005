/*	Author: Michael O'Dea, mode001
 *	Lab Section: 025
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: (From an earlier lab) A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 
 *	15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, 
 *	PC5 lights. If the level is 3 or 4, PC5 and PC4 light. 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..C1. 13-15 lights 
 *	PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. Use buttons on PA3..PA0 and mimic 
 *	the fuel-level sensor with presses. 

 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo: https://drive.google.com/open?id=15LLV9Xp1zlmnfD28QKbrkXdlydBTjHss

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char fuelLevel = 0x00;
	unsigned char lightSensor = 0x00;

    /* Insert your solution below */
    while (1) {
	
	    fuelLevel = (~PINA & 0x0F);
	 
	 	if(fuelLevel == 0x00){lightSensor = 0x40;}
		else if((fuelLevel == 0x01) | (fuelLevel == 0x02)){lightSensor = 0x60;}
		else if((fuelLevel == 0x03) | (fuelLevel == 0x04)){lightSensor = 0x70;}
		else if((fuelLevel == 0x05) | (fuelLevel == 0x06)){lightSensor = 0x38;}
		else if((fuelLevel == 0x07) | (fuelLevel == 0x08) | (fuelLevel == 0x09)){lightSensor = 0x3C;}
		else if((fuelLevel == 0x0A) | (fuelLevel == 0x0B) | (fuelLevel == 0x0C)){lightSensor = 0x3E;}
		else if((fuelLevel == 0x0D) | (fuelLevel == 0x0E) | (fuelLevel == 0x0F)){lightSensor = 0x3F;}
		else{lightSensor = 0x00;}

		PORTC = lightSensor;
			
    }
    return 0;
}
