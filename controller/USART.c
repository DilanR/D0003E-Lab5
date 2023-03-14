#include "include/USART.h"
#include "include/LCD.h"

void USART_Init (unsigned int ubrr){
    // Set baud rate
    UBRRH = (unsigned char)(ubrr>>8);
    UBRRL = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSRB = (1<<RXEN)|(1<<TXEN);
    // Set frame format: 8data, 2stop bit
    UCSRC = (1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit(USART *self, unsigned char signal) {
    //xd fuck USART 
    while (!(UCSRA & (1 << UDRE)));

    int data = UDR;
    UDR = 0x0;
    UDR = data;
}

unsigned char USART_Receive(USART *self, int arg){
    // Wait for data to be received
    while(!(UCSRA & (1<<RXC)));

    USART_Transmit(self, UDR);
    return UDR;
    // Get and return received data from buffer
}

