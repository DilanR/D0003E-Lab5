#include "include/keyboardHandler.h"
#include "include/simState.h"

// TODO update display and dispatch car
void sendNorth(int arg) {
    printf("north");
    queue[North] += 1;
    writePort(arg);    
}

void sendSouth(int arg) {
    printf("south");
    queue[South] += 1;
    writePort(arg);
}

void *catchInput(void *ptr) {
    while (1) {
        int i = getchar();

        if (i == EXIT) {
            exit(EXIT_SUCCESS);
        } else if (i == ENQUEUNORTH) {
            sendNorth(0);
        } else if (i == ENQUEUSOUTH) {
            sendSouth(2);
        }
    }
}

