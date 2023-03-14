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

    settingsSimState.c_cflag   = B9600 | CS8 | CSTOPB | CREAD | CLOCAL | HUPCL | INPCK;
    settingsSimState.c_lflag &= ~(ECHO | ECHONL | ICANON);
	tcsetattr(com1, TCSANOW, &settingsSimState);


    light = bothRed;
    
}

void writePort(u_int8_t str){
    write(com1, str, 1);
}

void *readPort(void *arg){
    
    while(1){
        
        read(com1, &light, 1);
    
        if(light == 0b1010){
            light = bothRed;
        } else if(light == 0b1001){
            light = northGsouthR;
        } else if(light == 2){
            light = southGnorthR;
            
        }

    }
}

void drive(void* arg){
    carsOnBridge++;
    sleep(5);
    carsOnBridge--;

    pthread_exit(NULL);
}

void letCarsDrive(void* arg){

    while (1) {
        if (queue[North] > 0 && light == northGsouthR) {
            queue[North]--;
            pthread_create(&car, NULL, drive, NULL);

            writePort(1);
            sleep(1);
        } else if (queue[South] > 0 && light == southGnorthR) {
            queue[South]--;
            pthread_create(&car, NULL, drive, NULL);

            writePort(3);
            sleep(1);
    }
    

}