#include "include/controller.h"
#include "include/GUI.h"

//shit should be mostly done, just need to make small adjustments

void receiveSignal(controller *self, int signal) {
    
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

//below is placeholder

void rmCar (controller *self, int arg) {
    self->carsOnBridge--;
}

void sendSignal (controller *self, int signal) {
    //xd fuck USART 
    while (!(USR0A & (1 << UDRE0)));


    USR0D = signal;
}

void lightController (controller *self, bool direction) {
    //flip this shit
    bool output;
    if (direction == south) {
        output = SGreenNRed;
    } else if(direction == north) {
        output = SGreenNRed;
    }
    return output;
}

void bridgeHandler (controller *self, int arg) {
    //TODO: support to remove starvation from directions
    
    if (self->queueN > 0 && self->queueS == 0){
        
        if(self->carsOnBridge == 0) {
            
            if (self->lastDirection == south)

                lightController(self, south);    
            
            }
        //TODO: if we we need all red then add else for bothRed here
    }

    else if (self->queueS > 0 && self->queueN == north){
        
        if(self->carsOnBridge == 0) {
            
            if (self->lastDirection == north)

                lightController(self, north);    
            
            }
            //TODO: if we we need all red then add else for bothRed here      
    }

    else {
        
        if (self->state == bothRed && self->carsOnBridge == 0) {
            
            /*
            if(self->lastDirection == south || self->lastDirection == both) {
                lightController(self, north);
            } TODO: if support for both needed keep this
            */
            if (self->lastDirection == north) {
                lightController(self, south);
            }
            else {
                lightController(self, north);
            }
        }

        //below wont work but its a start need to integrage time support
        else if (self->state == northGreen && self->carsOnBridge == 0) {
            sendSignal(self, south);
        }

        else if (self->state == southGreen && self->carsOnBridge == 0) {
            sendSignal(self, north);
        }

    }


    //UPDATEGUI(self->gui, *self->states);
    printAt(self->queueN, 0);
    printAt(self->carsOnBridge, 2);
    printAt(self->queueS, 4);

}



//holds queues and receives status of lights, sends signal for car enter bridge
