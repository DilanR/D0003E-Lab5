#ifndef _GUI_
#define _GUI_

#include "LCD.h"
#include "TinyTimber.h"

typedef struct{
    Object super;

}GUI;

#define INITGUI() {initObject()}


void printNorthQueue(GUI *self, int arg);
void printSouthQueue(GUI *self, int arg);
void printCarsOnBridge(GUI *self, int arg);

#endif
