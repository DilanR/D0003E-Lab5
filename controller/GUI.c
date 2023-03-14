#include "include/GUI.h"

void updateGUI(GUI *self, int *arg) {
    printAt(arg[0], 0); //queueN
    printAt(arg[1], 2); //carsOnBridge
    printAt(arg[2], 4); //queueS
}

void printNorthQueue(GUI *self, int arg) {
    printAt(arg, 0);
}

void printSouthQueue(GUI *self, int arg) {
    printAt(arg, 4);
}

void printCarsOnBridge(GUI *self, int arg) {
    printAt(arg, 2);
}
