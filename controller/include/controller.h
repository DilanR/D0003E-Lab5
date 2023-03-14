#ifndef _CONTROLLER_
#define _CONTROLLER_
#include "stdbool.h"
#include "TinyTimber.h"
#include <avr/io.h>
#include "GUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "USART_out.h"


//TODO: Petition to change structure to just one controller file 
//      Does there need to be support for no direction? 
//      In that case make direction enum 

typedef struct controller {
    Object super;
    GUI *gui;
	USART_out *usart_out;
    int carsOnBridge;
    int queueN;
    int queueS;
    int carsPassed;
    int direction; //0 = north, 1 = south
    int state;
    //int states[3] = {queueN, carsOnBridge, queueS};
} controller;

#define INITCONTROLLER(gui, usart_out) {initObject(), gui, usart_out, 0, 0, 0, 0, both, bothRed}

bool lightController (controller *self, bool direction);
void receiveSignal(controller *self, int signal);
void rmCar (controller *self, int arg);
void bridgeHandler(controller *self, int arg);

#define RECEIVESIGNAL(cont, signal) ASYNC(cont, receiveSignal, signal)


#define northArrival 0
#define northEntryS  1
#define southArrival 2
#define southEntryS  3


#define red          0
#define northGreen   1
#define southGreen   2



#define bothRed 0b1010 //this only if no direction needs to be implemented
#define sRedNGreen 0b1001
#define SGreenNRed 0b0110


#define driveTime MSEC(5000)
#define maxOpenTime MSEC(15000)
#define waitTime MSEC(1000)



#endif
