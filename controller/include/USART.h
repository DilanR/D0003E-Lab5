#ifndef _USART_
#define _USART_
#include <avr/io.h>
#include "Tinytimber.h"

typedef struct{
    Object super;
}USART;

#define INITUSART() {initObject()}

#define FOSC 8000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr);
unsigned char USART_Receive(void);

#endif
