/*
 * USART_out.c
 *
 * Created: 2023-03-14 15:00:21
 *  Author: dilred-6
 */ 
#include "include/USART_out.h"
#include "include/LCD.h"

void USART_Transmit(USART_out *self, unsigned char signal) {
	
	
	while (!(UCSR0A & (1 << UDRE0)));

	UDR0 = signal;
}