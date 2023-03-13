#ifndef _CONTROLLER_
#define _CONTROLLER_
#include "stdbool.h"
#include "TinyTimber.h"
#include "GUI.h"


//TODO: Petition to change structure to just one controller file 
//      Does there need to be support for no direction? 
//      In that case make direction enum 
typedef enum {
    north,
    south,
    both
} direction;



typedef struct controller {
    Object super;
    GUI *gui;
    int carsOnBridge;
    int queueN;
    int queueS;
    direction lastDirection; //0 = north, 1 = south
    int state;
    //int states[3] = {queueN, carsOnBridge, queueS};
} controller;


#define northArrival 0
#define northEntryS  1
#define southArrival 2
#define southEntryS  3


#define northGreen   0
#define northRed     1
#define southGreen   2
#define southRed     3


#define INITCONTROLLER(gui) {initObject(), gui, 0, 0, 0, both, bothRed}
#define bothRed 0b1010 //this only if no direction needs to be implemented
#define sRedNGreen 0b1001
#define SGreenNRed 0b0110


#define driveTime MSEC(5000)
#define maxOpenTime MSEC(15000)
#define waitTime MSEC(1000)



#endif
