#include "include/USART_in.h"
#include "include/LCD.h"
#include "include/controller.h"

void USART_Init (unsigned int ubrr){
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}



void USART_Receive(USART_in *self, int arg){
    // Wait for data to be received
    while(!(UCSR0A & (1<<RXC0)));
	uint8_t data = UDR0;

    //USART_Transmit(self, UDR0);
	USART_Transmit(self->usart_out, UDR0);
	RECEIVESIGNAL(self->cont,UDR0);

    //ASYNC(self->cont, USART_Receive, data);
    //return UDR0;
    // Get and return received data from buffer
}

