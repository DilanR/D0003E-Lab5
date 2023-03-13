#include "include/simGUI.h"
#include "include/simState.h"
#include <bits/pthreadtypes.h>


pthread_mutex_t mutexState;

void print(void){
	//pthread_mutex_lock(&mutexState);
    int *queue = getQueues();
	while (1) {
		printf("\nCARS\n")
		printf("North: %d, Bridge: %d, South: %d\n", (int)queue[1], (int)queue[0], (int)queue[2]);
	
		printf(printf("\nLIGHTS\n"))
		if(light == northGsouthR)
			printf("North GREEN, South RED: %d",  

		else if(light == southGnorthR)
			printf("North RED, South GREEN: %d \n",  

		else {
			printf("North RED, South RED: %d \n", 
		}


		sleep(1);
	}
	
	// switch (getLights()) {
	// 	case bothRed:
    //         clear_terminal();
	// 		printf("North:  %d RED,     Bridge: %d,     South: %d RED\n", (int)queue[1], (int)queue[0], (int)queue[2]);
	// 		printf("\n");
	// 		break;
		
	// 	case northGsouthR:
    //         clear_terminal();
	// 		printf("North: %d GREEN,   Bridge: %d,     South: %d RED\n", (int)queue[1], (int)queue[0], (int)queue[2]);
	// 		printf("\n");
	// 		break;
			
	// 	case southGnorthR:
    //         clear_terminal();
	// 		printf("North: %d GREEN,   Bridge: %d,     South: %d RED\n", (int)queue[1], (int)queue[0], (int)queue[2]);
	// 		printf("North: %d RED,     Bridge: %d,     South: %d GREEN\n", (int)queue[1], (int)queue[0], (int)queue[2]);
	// 		printf("\n");
	// 		break;
	// }
	// pthread_mutex_unlock(&mutexState);
}

void setting(void){
	tcsetattr(getCom(), TCSANOW, &settingsGUI);
}

void clear_terminal(void){
	printf(CLEAR);
}

void initGUI(void){
	setting();
}

