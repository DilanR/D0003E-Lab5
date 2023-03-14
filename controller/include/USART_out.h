/*
 * USART_out.h
 *
 * Created: 2023-03-14 15:01:35
 *  Author: dilred-6
 */ 


#ifndef USART_OUT_H_
#define USART_OUT_H_
#include "TinyTimber.h"
#include <avr/io.h>

typedef struct{
	Object super;
}USART_out;

#define INITUSARTOUT() {initObject()}

void USART_Transmit (USART_out *self, unsigned char signal);

#define USARTTRANSMIT(usart_out, signal) ASYNC(usart_out, USART_Transmit, signal)

#endif /* USART_OUT_H_ */