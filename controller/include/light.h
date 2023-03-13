#ifndef _LIGHT_
#define _LIGHT_
#include "TinyTimber.h"


typedef struct light {
    Object super;
    int lightStatus; //0 = green south, 1 = green north
} Light;

void flipLight(Light *self, int arg);


#endif
