#include "include/keyboardHandler.h"
#include <pthread.h>
#include "include/bridge.h"
#include "include/car.h"
#include "include/LCD.h"
#include "include/TinyTimber.h"
#include "include/USART.h"
#include "include/light.h"


void interruptInit() {
    EIFR  = 0xC0;
    EMISK = 0xC0;

}

int main() {

    LCDInit();
    interruptInit();
    USART_Init(MYUBRR);



    pthread_t keyboardThread, displayThread;

    int kt = pthread_create(&keyboardThread, NULL, &catchInput, NULL);
    //int dt = pthread_create(&displayThread, NULL, &print, NULL);
    
    pthread_join(keyboardThread, NULL);
    //pthread_join(displayThread, NULL);

    return 0;
}
