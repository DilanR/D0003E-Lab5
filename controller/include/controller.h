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




typedef struct controller {
    Object super;
    GUI *gui;
	USART_out *usart_out;
    int queue[3];
	int carsPassed;
    uint8_t state;
} controller;

#define INITCONTROLLER(gui, usart_out, init) {initObject(), gui, usart_out, {0,0,0},0, init}

void receiveSignal(controller *self, uint8_t signal);
void rmCar (controller *self, int arg);
void updategui(controller *self, int arg);
void init(controller *self, int arg);
void lightHandler(controller *self, int dir);


#define RECEIVESIGNAL(cont, signal) ASYNC(cont, receiveSignal, signal)
#define LIGHTHANDLER(cont, arg)		ASYNC(cont, lightHandler, arg)

// Queue elements
#define BRIDGE 0
#define NORTH 1
#define SOUTH 2

//INPUT SIGNALS
#define NARRIVAL	0b0001
#define NENTRY		0b0010
#define SARRIVAL	0b0100
#define SENTRY		0b1000

//OUTPUT SIGNALS
#define NGREEN		0b0001
#define NRED		0b0010
#define SGREEN		0b0100
#define SRED		0b1000

// COMPOSITE OUTPUT SIGNALS
#define BRED (SRED | NRED)
#define SREDNGREEN (SRED | NGREEN)
#define SGREENNRED (SGREEN | NRED)

//CONSTANTS
#define driveTime MSEC(5000)
#define maxOpenTime MSEC(15000)
#define waitTime MSEC(1000)
#define bridgeLimit 5


#endif
