#include "include/simState.h"

void simState_init(void){

    sem_init(&semArrive, 0, 0);
    sem_init(&semDepart, 0, 0);


    com1 = open("/dev/ttyACM0", O_RDWR);

    if (com1 == -1){
        perror("open_port: Unable to open /dev/ttyACM0 - ");
    } else {
        fcntl(com1, F_SETFL, 0);
    }

    tcgetattr(com1, &settingsSimState);

    cfsetispeed(&settingsSimState, B9600);
    cfsetospeed(&settingsSimState, B9600);

	settingsSimState.c_cflag &= ~CSIZE; 	// Clear char size
	settingsSimState.c_cflag |= CS5;	    // set 5 bit char size
	settingsSimState.c_cflag &= ~CSTOPB;    // 1 stop bit
	settingsSimState.c_cflag &= ~PARENB;    // no parity
	settingsSimState.c_cflag |= CREAD;	    // Enable receive
	settingsSimState.c_cc[VMIN] =  1;       // Read at least 1 char

    lights = bothRed;
    
}

void *arrivalW(void *arg){
    
    uint64_t tempDir;
    
    sem_wait(&semArrive);
    pthread_mutex_lock(&mutexState);
    tempDir = direction;
    pthread_mutex_unlock(&mutexState);
    arrival(tempDir);
    return NULL;

}

void arrival(uint64_t direction){
    sem_wait(&semArrive);
    queue[direction]++;
    sem_post(&semDepart);
}

void *departureNS(void *arg){
    departure();
    return NULL;
}

void *carsOnBridge(void *arg){

    return NULL;
}

void *readPort(void *arg){
}