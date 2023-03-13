#include "include/simGUI.h"
#include "include/simState.h"
#include <bits/pthreadtypes.h>


pthread_mutex_t mutexState;

void print(void){
	pthread_mutex_lock(&mutexState);
	switch (getLights()) {
		case bothRed:
            clear_terminal();
			printf("North:  %d RED,     Bridge: %d,     South: %d RED\n", (int)queue[1], (int)queue[0], (int)queue[2]);
			printf("\n");
			break;
		
		case northGsouthR:
            clear_terminal();
			printf("North: %d GREEN,   Bridge: %d,     South: %d RED\n", (int)queue[1], (int)queue[0], (int)queue[2]);
			printf("\n");
			break;
			
		case southGnorthR:
            clear_terminal();
			printf("North: %d GREEN,   Bridge: %d,     South: %d RED\n", (int)queue[1], (int)queue[0], (int)queue[2]);
			printf("North: %d RED,     Bridge: %d,     South: %d GREEN\n", (int)queue[1], (int)queue[0], (int)queue[2]);
			printf("\n");
			break;
	}
	pthread_mutex_unlock(&mutexState);
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

