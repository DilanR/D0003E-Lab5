#include "include/main.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

int com1;

u_int64_t direction;
u_int64_t queue[3];
u_int8_t light;
u_int8_t car; 

sem_t semArrive;
sem_t semDepart;

int carsOnBridge;
pthread_t car;
pthread_t mutexState;
pthread_t mutexId;
pthread_mutex_t mutex;

void sendNorth(int arg) {
    printf("north");
    queue[North] += 1;
    writePort(arg);    
}

void sendSouth(int arg) {
    printf("south");
    queue[South] += 1;
    writePort(arg);
}

void *catchInput(void *ptr) {
    while (1) {
        int i = getchar();

        if (i == EXIT) {
            exit(EXIT_SUCCESS);
        } else if (i == ENQUEUNORTH) {
            sendNorth(0);
        } else if (i == ENQUEUSOUTH) {
            sendSouth(2);
        }
    }
}


void *printGUI(void *arg){
	while (1) {

		printf("CARS & LIGHTS");
		if(light == bothRed){
			printf("North:  %d RED,     Bridge: %d,     South: %d RED\n", queue[1], queue[0], queue[2]);
		}
		else if(light == northGsouthR){
			printf("North: %d GREEN,   Bridge: %d,     South: %d RED\n", queue[1], queue[0], queue[2]);
		}
		else if(light == southGnorthR){
			printf("North: %d RED,     Bridge: %d,     South: %d GREEN\n", queue[1], queue[0], queue[2]);
		}

		sleep(1);
	}
}

void clear_terminal(void){
	printf(CLEAR);
}

void initSimState(void){

    sem_init(&semArrive, 0, 0);
    sem_init(&semDepart, 0, 0);


    com1 = open("/dev/ttyACM0", O_RDWR);

    if (com1 == -1){
        printf("open_port: Unable to open /dev/ttyACM0 - ");
    // } else {
    //     fcntl(com1, F_SETFL, 0);
    // }

    tcgetattr(com1, &settingsSimState);

    cfsetispeed(&settingsSimState, B9600);
    cfsetospeed(&settingsSimState, B9600);

    settingsSimState.c_cflag   = B9600 | CS8 | CSTOPB | CREAD | CLOCAL | HUPCL | INPCK;
    settingsSimState.c_lflag &= ~(ECHO | ECHONL | ICANON);
	tcsetattr(com1, TCSANOW, &settingsSimState);

    pthread_mutex_init(&mutex, NULL);

    light = bothRed;
    
}

void writeToPort(int arg){
    int com1Temp = write(com1, &arg, sizeof(arg));

    if((car & 1) == 1){
        queue[North]++;
    }
    if(((car >> 1) & 1) == 1){
        queue[North]--;
    }
    if(((car >> 2) & 1) == 1){
        queue[South]++;
    }
    if(((car & 3) & 1) == 1){
        queue[South]--;
    }
    if(com1Temp == -1){
        printf("write_port: Unable to write /dev/ttyACM0 - ");
    }
}


void *writePort(void *str){

    while(1){
        if(car){
            pthread_mutex_lock(&mutex);
            write(com1, &str, sizeof(str));
            pthread_mutex_unlock(&mutex);
            car = 0;
        }
    }
}

void *readPort(void *arg){
    
    while(1){
        if(!light){
        pthread_mutex_lock(&mutex);
        int tempcom1 = read(com1, &light, sizeof(light));

        if(light){
            printf("Light: %d \n" light)
        }
        pthread_mutex_unlock(&mutex);
        }
        if(tempcom1 == -1){
            printf("read_port: Unable to read /dev/ttyACM0 - ");
        }

    }
}

void *drive(void* arg){
    carsOnBridge++;
    sleep(5);
    carsOnBridge--;

    pthread_exit(NULL);
}

void *letCarsDrive(void* arg) {

    while (1) {
        if (queue[North] > 0 && light == northGsouthR) {
            queue[North]--;
            pthread_create(&car, NULL, &drive, NULL);

            writePort(1);
            sleep(1);
        } else if (queue[South] > 0 && light == southGnorthR) {
            queue[South]--;
            pthread_create(&car, NULL, &drive, NULL);

            writePort(3);
            sleep(1);
        }
    }
}

int main() {

    initSimState();

    pthread_t keyboardThread, guiThread, serialInThread, serialOutThread, simThread;

    pthread_create(&keyboardThread, NULL, &catchInput, NULL);
    pthread_create(&guiThread, NULL, &printGUI, NULL);
    pthread_create(&serialInThread, NULL, &readPort, NULL);
    pthread_create(&serialOutThread, NULL, &writePort, NULL);
    pthread_create(&simThread, NULL, &letCarsDrive, NULL);
    //int dt = pthread_create(&displayThread, NULL, &print, NULL);
    while (1);
    return 0;
    /*
    pthread_join(keyboardThread, NULL);
    pthread_join(keyboardThread, NULL);
    pthread_join(keyboardThread, NULL);
    pthread_join(keyboardThread, NULL);
    pthread_join(keyboardThread, NULL);
    //pthread_join(displayThread, NULL);
    return 0;
    */
}
