#include "include/simState.h"

void simState_init(void){

    sem_init(&semArrive, 0, 0);
    sem_init(&semDepart, 0, 0);


    port = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (port == -1){
        perror("open_port: Unable to open /dev/ttyACM0 - ");
    } else {
        fcntl(port, F_SETFL, 0);
    }

    tcgetattr(port, &settingsSimState);

    cfsetispeed(&settingsSimState, B9600);
    cfsetospeed(&settingsSimState, B9600);

    settingsSimState.c_cflag |= (CLOCAL | CREAD);
    settingsSimState.c_cflag &= ~PARENB;
    settingsSimState.c_cflag &= ~CSTOPB;
    settingsSimState.c_cflag &= ~CSIZE;
    settingsSimState.c_cflag |= CS8;
    settingsSimState.c_cflag &= ~CRTSCTS;
    
}