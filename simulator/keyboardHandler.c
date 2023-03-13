#include "include/keyboardHandler.h"
#include "include/simState.h"

// TODO update display and dispatch car
void sendNorth() {
    printf("north");
    
}

void sendSouth() {
    printf("south");


}

void *catchInput(void *ptr) {
    while (1) {
        int i = getchar();

        if (i == EXIT) {
            exit(EXIT_SUCCESS);
        } else if (i == ENQUEUNORTH) {
            sendNorth();
        } else if (i == ENQUEUSOUTH) {
            sendSouth();
        }
    }
}

