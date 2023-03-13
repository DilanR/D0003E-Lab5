#include "include/TinyTimber.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "include/LCD.h"
#include "include/controller.h"
#include "include/GUI.h"
#include "include/USART.h"

static GUI gui = INITGUI();
static USART usart = INITUSART();
static controller cont = INITCONTROLLER(&gui, &usart);

void interruptInit() {
    EIFR  = 0xC0;
    EIMSK = 0xC0;
}

void interrupts(controller *self, int arg){
    //UPDATEGUI(&gui, cont.states);
    SYNC(&cont, bridgeHandler, 0);
}
int main(){
    sei();
    LCDInit();
    interruptInit();
    USART_Init(MYUBRR);


    INSTALL(&usart, USART_Receive, IRQ_USART0_RX);

    return TINYTIMBER(&cont, interrupts, 0);
}
