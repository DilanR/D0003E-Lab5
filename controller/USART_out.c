/*
 * USART_out.c
 *
 * Created: 2023-03-14 15:00:21
 *  Author: dilred-6
 */ 
#include "include/USART_out.h"

void USART_Transmit(USART_out *self, unsigned char signal) {
	//xd fuck USART
	while (!(UCSR0A & (1 << UDRE0)));

	int data = signal;

	UDR0 = 0x0;
	UDR0 = data;
}