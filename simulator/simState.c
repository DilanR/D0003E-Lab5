#include "include/simState.h"
#include <sys/types.h>

static u_int8_t lights;
static int com1;
sem_t semArrive;
sem_t semDepart;

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

int getCom(){
    return com1;
}

void drive(u_int8_t arg){
    u_int8_t direction = arg;
    usleep(driveTime);
    writePort(direction);
    usleep(waitTime);
    writePort(3);
}

void letCarsDrive(u_int8_t arg){
    u_int8_t direction = arg;
    while(1){
        sem_wait(&semArrive);
        drive(direction);
        sem_post(&semDepart);
    }
}
