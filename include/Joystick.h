#include "TinyTimber.h"
#include "GUI.h"
#include <avr/io.h>

//TODO Change to correct pin
#define DOWN PINB7
#define UP PINB6
#define CENTER PINB4
#define RIGHT PINE2
#define LEFT PINE3

typedef struct {
    Object super;
    GUI *gui; //TODO gui
}ButtonHandler;

#define INITJOYSTICK(gui) {initObject(), gui} 

//#define HANDELDOWN(gui) ASYNC(gui->)

void buttonInit(void);
void buttonLR(ButtonHandler *this, int arg); //argument to switch gui
void buttonUDC(ButtonHandler *this, int arg);
