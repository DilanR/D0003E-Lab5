#include "include/bridge.h"

//below is placeholder

void rmCar(Bridge *self, int arg) {
    self->carsOnBridge--;
}

void receiveSignal(Bridge *self, int signal) {
    
    int northQueue = signal & (northArrival << 1);
    int northEntry = signal & (northEntryS << 1);
    int southQueue = signal & (southArrival << 1);
    int southEntry = signal & (southEntryS << 1);


    if (northQueue) {
        self->queueN++;
    }

    if (northEntry) {
        self->queueN--;
        self->carsOnBridge++;
        AFTER(driveTime, self, rmCar, 0);
        //TODO: add AFTER call to remove car from bridge
    }

    if (southQueue) {
        self->queueS++;
    }

    if (southEntry) {
        self->queueS--;
        self->carsOnBridge++;
        AFTER(driveTime, self, rmCar, 0);
        //TODO: add AFTER call to remove car from bridge
    }
    // TODO: add function call to logistic handler for bridge and lights
}


void sendSignal(Bridge *self, int signal) {
    //xd fuck USART
    

}

void lightController(Bridge *self, bool direction) {
    //flip this shit
}

void bridgeHandler(Bridge *self) {
    //TODO: support to remove starvation from directions
}



//holds queues and receives status of lights, sends signal for car enter bridge
