#include "include/simState.h"
#include <sys/types.h>

static u_int8_t lights;
static int com1;
static int queue[3];
sem_t semArrive;
sem_t semDepart;

void initSimState(void){


    sem_init(&semArrive, 0, 0);
    sem_init(&semDepart, 0, 0);


    com1 = open("/dev/ttyS0", O_RDWR);

    if (com1 == -1){
        perror("open_port: Unable to open /dev/ttyACM0 - ");
    } else {
        fcntl(com1, F_SETFL, 0);
    }

    tcgetattr(com1, &settingsSimState);

    cfsetispeed(&settingsSimState, B9600);
    cfsetospeed(&settingsSimState, B9600);

	// settingsSimState.c_cflag &= ~CSIZE; 	// Clear char size
	// settingsSimState.c_cflag |= CS5;	    // set 5 bit char size
	// settingsSimState.c_cflag &= ~CSTOPB;    // 1 stop bit
	// settingsSimState.c_cflag &= ~PARENB;    // no parity
	// settingsSimState.c_cflag |= CREAD;	    // Enable receive
	// settingsSimState.c_cc[VMIN] =  1;       // Read at least 1 char

    lights = bothRed;
    
}

void writePort(u_int8_t str){
    write(com1, &str, 1);
}

void *readPort(void *arg){
    u_int8_t light = getLights();

    while(1){
        
        read(com1, &light, 1);
    
        if(light == 0){
            light = 0;
        } else if(light == 1){
            light = 1;
        } else if(light == 2){
            light = 2;
        } else if (light == 3){
            light = 3;
        }
            
    }

}

u_int8_t getLights() {
    return lights;
}

int getCom() {
    return com1;
}

int *getQueues() {
    return queue;
}

void *drive(void* arg){
    queue[Bridge]++;
    sleep(5);
    queue[Bridge]--;

    pthread_exit(NULL);
}

void *letCarsDrive(void* arg){

    while (1) {
        pthread_t car;

        if (queue[North] > 0 && getLights() == northGsouthR) {
            queue[North]--;
            pthread_create(&car, NULL, &drive, NULL);

            writePort(1);
            sleep(1);
        } else if (queue[South] > 0 && getLights() == southGnorthR) {
            queue[South]--;
            pthread_create(&car, NULL, &drive, NULL);

            writePort(3);
            sleep(1);
        }
    }
}
