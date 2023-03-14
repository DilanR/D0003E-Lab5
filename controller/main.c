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

static controller cont = INITCONTROLLER(&gui, &usart_out);

static USART_in usart = INITUSARTIN(&cont, &usart_out);
void interruptInit() {
    EIFR  = 0xC0;
    EIMSK = 0xC0;
}

void interrupts(controller *self, int arg){
    //UPDATEGUI(&gui, cont.states);
    ASYNC(&cont, bridgeHandler, 0);
}
int main(){
    sei();
    LCDInit();
    interruptInit();
    USART_Init(MYUBRR);
    //initController(0);
	//printAt(1,1);


    INSTALL(&usart, USART_Receive, IRQ_USART0_RX);

    return TINYTIMBER(&cont, interrupts, 0);
}
