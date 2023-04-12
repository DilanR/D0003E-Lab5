#include "include/GUI.h"

void printNorthQueue(GUI *self, int arg) {
	printAt(arg, 0);
}

void printSouthQueue(GUI *self, int arg) {
	printAt(arg, 4);
}

void printCarsOnBridge(GUI *self, int arg) {
	printAt(arg, 2);
}