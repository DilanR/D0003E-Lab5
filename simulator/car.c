#include "include/car.h"
#include "stdbool.h"


typedef struct{
    bool dir; // North = 1, South = 0
}car;

#define INITCAR(dir) (car) {dir}

#define NORTH 1
#define SOUTH 0

//If respective light red or queue exists, join queue else pass bridge

