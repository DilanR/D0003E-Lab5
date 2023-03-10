#include "include/Joystick.h"
#include "include/GUI.h"
#include "include/PulseGen.h"



void buttonInit(void) {                                                                        
        EIMSK |= (1<<PCIE1) | (1<<PCIE0); //Enable external interrupts for pins [15:8]   
        PCMSK1 |= (1<<PCINT15) | (1<<PCINT14) | (1<<PCINT12); //Enable interrupt on pin 15.
        PCMSK0 |= (1<<PCINT3) | (1<<PCINT2); //Enable interrupt on pin 15.
        PORTB |= (1<<PINB7) | (1<<PINB6) | (1<<PINB4);
        PORTE |= (1<<PINE3) | (1<<PINE2);
}

void buttonLR(ButtonHandler *this, int arg) {
    //Context switch
    if (!(PINE & (1 << LEFT))) {
        //left or right???
        ASYNC(this->gui, switchState, 1);
    } else if (!(PINE & (1 << RIGHT))) {
        //left or right???
        ASYNC(this->gui, switchState, 1);
    }
}

void buttonUDC(ButtonHandler *this, int arg) {
    PulseGen *p;
    p = this->gui->currentP == 1 ? this->gui->p1 : this->gui->p2;
    //call PulseGen methods
    if (!(PINB & (1 << DOWN))) {
        //down
        ASYNC(p, dec_freq, 0);
    } else if (!(PINB & (1 << UP))) {
        //up
        ASYNC(p, inc_freq, 0);
    } else if (!(PINB & (1 << CENTER))) {
        //push
        ASYNC(p, reset_freq, 0);
    }
}
