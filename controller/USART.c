#include "include/USART.h"

void USART_Init (unsigned int ubrr){
    // Set baud rate
    UBRRH = (unsigned char)(ubrr>>8);
    UBRRL = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSRB = (1<<RXEN)|(1<<TXEN);
    // Set frame format: 8data, 2stop bit
    UCSRC = (1<<USBS)|(3<<UCSZ0);
}


unsigned char USART_Receive(USART *self, int arg){
    // Wait for data to be received
    while(!(UCSRA & (1<<RXC)));

    return UDR;
    // Get and return received data from buffer
}

void USART_Transmit(USART *self, unsigned char signal) {
    //xd fuck USART 
    while (!(UCSRA & (1 << UDRE)));

    UDR = signal;
}
