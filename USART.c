#include "include/USART.h":

void USARt_Init (usigned int ubrr){
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


unsigned char USART_Receive(void){
    // Wait for data to be received
    while(!(UCSR0A & (1<<RXC0)));

    unsigned int signal = UDR0;
    // Get and return received data from buffer
    ASYNC(self, receiveSignal, signal);
}