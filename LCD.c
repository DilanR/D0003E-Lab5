#include "include/LCD.h"
#include <avr/io.h>

uint16_t scc[10] = {0x1551, 0x0110, 0x1E11, 0x1B11, 0x0B50, 0x1B41, 0x1F41, 0x0111, 0x1F51, 0x1B51};


void LCDInit(void){
        /*Enable LCD, Low power waveform*/
        LCDCRA = (1<<LCDEN) | (1<<LCDAB);
        /*Async clock source, 1/3 bias 1/4 Duty, 25 segments*/
        LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
        /*PSC = 16, divide = 8*/
        LCDFRR = (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
        /*Drive time 300us, CC Max voltage 3.35V*/
        LCDCCR = (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);
        
}

void writeChar(char ch, int pos){
	if(pos>=0 && pos<=5){
		uint8_t index = (uint8_t)ch-48;
		uint8_t even = 0x00;
		uint8_t mask = 0xF0; //we need to clear the nibble b4 writing 2 it
		if(pos%2 != 0){
			even = 0x04;
			mask = 0x0F;
		}
		uint8_t *LCDREG = (uint8_t*)&LCDDR0;
		LCDREG += pos/2;
		*LCDREG &= mask;
		*LCDREG  |= ((scc[index] & MASK_0)<<even);
		LCDREG += 0x5;
		*LCDREG &= mask;
		*LCDREG  |= (((scc[index] & MASK_1)>>0x4)<<even);
		LCDREG += 0x5;
		*LCDREG &= mask;
		*LCDREG  |= (((scc[index] & MASK_2)>>0x8)<<even);
		LCDREG += 0x5;
		*LCDREG &= mask;
		*LCDREG  |= (((scc[index] & MASK_3)>>0xC)<<even);
	}
}

void printAt(long num, int pos) {
	int pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}
