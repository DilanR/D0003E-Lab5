#include "include/TinyTimber.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "include/LCD.h"
#include "include/controller.h"
#include "include/GUI.h"
#include "include/USART_in.h"
#include "include/USART_out.h"

static GUI gui = INITGUI();
static USART_out usart_out = INITUSARTOUT();
static controller cont = INITCONTROLLER(&gui, &usart_out, NORTH);
static USART_in usart_in = INITUSARTIN(&cont, &usart_out);

void interruptInit() {
	
    EIFR  = 0xC0;
    EIMSK = 0xC0;
}

int main(){
	CLKPR = 0x80;
	CLKPR = 0x00;

    LCDInit();
    interruptInit();
    USART_Init(MYUBRR);



    INSTALL(&usart_in, USART_Receive, IRQ_USART0_RX);

    return TINYTIMBER(&cont, init, 0);
	
}
