/*
 * USART_out.c
 *
 * Created: 2023-03-14 15:00:21
 *  Author: dilred-6
 */ 
#include "include/USART_out.h"

void USART_Transmit(USART_out *self, int signal) {
	//xd fuck USART
	int data = 0;
	if (signal == 0){ 
		data = 0xA; // 0xA = 0b1010
	}
	 else if (signal == 1){
		data = 0x9; //Ox9 = 0b1001
	}
	else if (signal == 2){ 
		data = 0x6;	//0x6 = 0b0110
	}
	

	while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = data;
}