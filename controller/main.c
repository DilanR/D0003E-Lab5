#include "include/TinyTimber.h"
#include <avr/io>
#include "include/LCD.h"
#include "include/USART.h":

void interruptInit() {
    EIFR  = 0xC0;
    EMISK = 0xC0;

}
int main(){
    LCDInit();
    interruptInit();
    USART_Init(MYUBRR);

    
    controller c = initController();
    USART usart = initUSART(&c);
    INSTALL(&usart, USART_Receive, IRQ_USART0_RX)


}
