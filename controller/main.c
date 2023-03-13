#include "include/TinyTimber.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "include/LCD.h"
#include "include/controller.h"
#include "include/GUI.h"
//#include "include/USART.h"

static GUI gui = INITGUI();
static controller cont = INITCONTROLLER(&gui);
//static USART usart = INITUSART(&cont);

void interruptInit() {
    EIFR  = 0xC0;
    EMISK = 0xC0;
}

void interrupts(controller *self, int arg){
    //UPDATEGUI(&gui, cont.states);
}
int main(){
    sei();
    LCDInit();
    interruptInit();
    //USART_Init(MYUBRR);

    INSTALL(&usart, USART_Receive, IRQ_USART0_RX);

    return TINYTIMBER(&cont, interrupts, 0);
}
