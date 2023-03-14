#ifndef _USART_
#define _USART_
#include <avr/io.h>
#include "TinyTimber.h"

typedef struct{
    Object super;
}USART;

#define INITUSART() {initObject()}

#define FOSC 8000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr);
unsigned char USART_Receive(USART *self, int arg);
void USART_Transmit (USART *self, unsigned char signal);

#define USARTRECEIVE(usart) SYNC(usart, USART_Receive, 0)
#define USARTTRANSMIT(usart, signal) ASYNC(usart, USART_Transmit, signal)

#endif
