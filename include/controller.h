#ifndef _BRIDGE_
#define _BRIDGE_
#include "stdbool.h"
#include "include/TinyTimber.h"
#include "include/LCD.h"


//TODO: Petition to change structure to just one controller file 
//      Does there need to be support for no direction? 
//      In that case make direction enum 
typedef enum {
    north,
    south,
    both
} direction;
}



typedef struct controller {
    Object super;
    int carsOnBridge;
    int queueN;
    int queueS;
    direction lastDirection; //0 = north, 1 = south
    int state;
} controller;


#define northArrival 0
#define northEntryS  1
#define southArrival 2
#define southEntryS  3


#define northGreen   0
#define northRed     1
#define southGreen   2
#define southRed     3


#define initController() {initObject(), 0, 0, 0, both, bothRed}
#define bothRed 0b1010 //this only if no direction needs to be implemented
#define sRedNGreen 0b1001
#define SGreenNRed 0b0110


#define driveTime MSEC(5000)
#define maxOpenTime MSEC(15000)
#define waitTime MSEC(1000)



#endif
