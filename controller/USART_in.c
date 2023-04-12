#include "include/USART_in.h"
#include "include/LCD.h"
#include "include/controller.h"

void USART_Init (unsigned int ubrr){
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0) | (1 << RXCIE0);
    // Set frame format: 8data, 1 stop bit
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}



void USART_Receive(USART_in *self, int arg){
    // Wait for data to be received
	

    while(!(UCSR0A & (1<<RXC0)));
	
    volatile uint8_t input = UDR0;
	
	RECEIVESIGNAL(self->cont,input);
	
  
    // Get and return received data from buffer
}

