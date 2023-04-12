#include "include/controller.h"


//shit should be mostly done, just need to make small adjustments
void updategui(controller *self, int arg) {
	
	ASYNC(self->gui, printNorthQueue, self->queue[NORTH]);
	ASYNC(self->gui, printCarsOnBridge, self->queue[BRIDGE]);
	ASYNC(self->gui, printSouthQueue, self->queue[SOUTH]);
	
}

void init(controller *self, int arg){
	//print first initial gui
	updategui(self,0);
	//set arbitrary light on,
	LIGHTHANDLER(self, self->state);
	
}

void receiveSignal(controller *self, uint8_t signal) {
	
	//signal = signal & 0b1111;
	// Car Arrives from north
	if (signal & NARRIVAL) { 
		self->queue[NORTH]++;
	} 
	// Car Departs from north
	else if (signal & NENTRY) {
		self->queue[NORTH]--;
		self->queue[BRIDGE]++;
		self->carsPassed++;
		AFTER(driveTime, self, rmCar, 0);
	} 
	// Car Arrives from south
	else if (signal & SARRIVAL) {
		self->queue[SOUTH]++;
	} 
	// Car Departs from south
	else if (signal & SENTRY) {
		self->queue[SOUTH]--;
		self->queue[BRIDGE]++;
		self->carsPassed++;
		AFTER(driveTime, self, rmCar, 0);
	}
	// TODO: add function call to logistic handler for bridge and lights
	updategui(self,0);

}

//remove passing car from bridge
void rmCar (controller *self, int arg) {
	self->queue[BRIDGE]--;
	updategui(self,0);	
}

void lightHandler(controller *self, int dir){
	// which queue to consider depends on direction
	int ADJECENT, OPPOSITE, GOAHEAD, HALT;
	LCDDR13 = (dir == NORTH) ? 1 : 0;
	ADJECENT = (dir == NORTH) ? NORTH : SOUTH;
	OPPOSITE = (dir == NORTH) ? SOUTH : NORTH;
	GOAHEAD = (dir == NORTH) ? SREDNGREEN : SGREENNRED;
	
	// Cars can pass if adjecent direction has a queue and 
	// the bridge is not full or the the opposite queue is empty
	if (self->queue[ADJECENT] > 0 && (self->carsPassed <= bridgeLimit || self->queue[OPPOSITE] == 0)){
		//set correct state (light) and transmit to simulator
		self->state = ADJECENT;
		USARTTRANSMIT(self->usart_out, GOAHEAD);
		//Consider same direction again to allow for more cars in same direction
		AFTER(waitTime, self, lightHandler, ADJECENT);
	}
	
	// To Prevent starvation alternate direction of allowed cars if.
	// current dir is the one consider and cars exists on opposite queue and bridge is in use. 
	else if (self->state == ADJECENT && self->queue[OPPOSITE] != 0 && self->queue[BRIDGE] != 0) {
		//reset cars passed and disallow cars from passing bridge until empty
		self->carsPassed = 0;
		self->state = BRED;
		USARTTRANSMIT(self->usart_out, BRED);
		// switch direction to consider
		AFTER(driveTime, self, lightHandler, OPPOSITE);
	} 
	// alternate lights if both queues empty
	else {
		self->carsPassed = 0;
		self->state = BRED;
		USARTTRANSMIT(self->usart_out, BRED);
		AFTER(waitTime, self, lightHandler, OPPOSITE);
		
	}
	
	
}



