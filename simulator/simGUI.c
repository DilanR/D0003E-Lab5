#include "include/simGUI.h"



void print(void){
	pthread_mutex_lock(&mutexState);
	switch (lights) {
		case bothRed:
            ClEAR();
			printf("North:  %d RED,     Bridge: %d,     South: %d RED\n", queue[1], queue[0], queue[2]);
			printf("\n");
			break;
		
		case northGsouthR:
            ClEAR();
			printf("North: %d GREEN,   Bridge: %d,     South: %d RED\n", queue[1], queue[0], queue[2]);
			printf("\n");
			break;
			
		case southGnorthR:
            ClEAR();
			printf("North: %d RED,     Bridge: %d,     South: %d GREEN\n", queue[1], queue[0], queue[2]);
			printf("\n");
			break;
	}
	pthread_mutex_unlock(&mutexState);
}

void setting(void){
	tcsetattr(com1, TCSANOW, &settingsGUI);
}

void clear_terminal(void){
	printf(CLEAR);
}

void initGUI(void){
	setting();
}