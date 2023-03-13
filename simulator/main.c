#include "include/keyboardHandler.h"
#include <pthread.h>


int main() {

    pthread_t keyboardThread, displayThread;

    int kt = pthread_create(&keyboardThread, NULL, &catchInput, NULL);
    //int dt = pthread_create(&displayThread, NULL, &print, NULL);
    
    pthread_join(keyboardThread, NULL);
    //pthread_join(displayThread, NULL);

    return 0;
}
