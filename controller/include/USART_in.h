#ifndef _USART_
#define _USART_
#include <avr/io.h>
#include "TinyTimber.h"
#include "controller.h"
#include "USART_out.h"

typedef struct{
    Object super;
	controller *cont;
	USART_out *usart_out;
}USART_in;

#define INITUSARTIN(cont, usart_out) {initObject(), cont, usart_out}

#define FOSC 8000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr);
unsigned char USART_Receive(USART_in *self, int arg);


#define USARTRECEIVE(usart) SYNC(usart, USART_Receive, 0)


#endif
