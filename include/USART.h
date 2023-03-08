#include <avr/io.h>
#include <tinytimber.h>

//TODO: struct?

#define FOSC 8000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr);
unsigned char USART_Receive(void);