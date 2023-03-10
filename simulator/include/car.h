#ifndef _CAR_
#define _CAR_
#include "stdbool.h"


typedef struct{
    bool dir; // North = 0, South = 1
}car;

#define INITCAR(dir) (car) {dir}

#define NORTH 1
#define SOUTH 0

void passBridge(car *this);

#endif
