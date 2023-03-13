#include "include/simGUI.h"

void initSimGUI(void){
    settingsSimState();
}

void print(void){
	pthread_mutex_lock(&mutexState);
	switch (lights) {
		case bothRed:
            //clear terminal?
			printf("North:  %d RED,     Bridge: %d,     South: %d RED\n", queues[1], queues[0], queues[2]);
			printf("\n");
			break;
		
		case northGsouthR:
            //clear terminal?
			printf("North: %d GREEN,   Bridge: %d,     South: %d RED\n", queues[1], queues[0], queues[2]);
			printf("\n");
			break;
			
		case southGnorthR:
            //clear terminal?
			printf("North: %d RED,     Bridge: %d,     South: %d GREEN\n", queues[1], queues[0], queues[2]);
			printf("\n");
			break;
	}
	pthread_mutex_unlock(&mutexState);
}