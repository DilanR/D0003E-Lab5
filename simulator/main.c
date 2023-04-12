#include "include/main.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

char *usb;
int com1;

u_int64_t direction;
u_int64_t queue[3];
u_int8_t signal_out; 
u_int8_t signal_in; 
int northLight;
int southLight;

u_int8_t output, input;

sem_t semArrive;
sem_t semDepart;

pthread_mutex_t ioMutex, stateMutex;

pthread_t keyboardThread;
pthread_t guiThread;
pthread_t serialInThread;
pthread_t serialOutThread;
pthread_t simThread;

void *catchInput(void *ptr) {
    while (1) {
        int i = getchar();

        /*
         * 3 option, queue north, queue south and exit
         */
        if (i == EXIT) {
            exit(EXIT_SUCCESS);
        } else if (i == ENQUEUNORTH) {
            pthread_mutex_lock(&stateMutex);
            signal_out = N_ARRIVAL;
            pthread_mutex_unlock(&stateMutex);
        } else if (i == ENQUEUSOUTH) {
            pthread_mutex_lock(&stateMutex);
            signal_out = S_ARRIVAL;
            pthread_mutex_unlock(&stateMutex);
        }
    }
}


void *printGUI(void *arg){
	while (1) {
        printf("==============================\n");
        printf("North Queue: %d\n", queue[NORTHQ]);
        printf("South Queue: %d\n", queue[SOUTHQ]);
        printf("Bridge: %d\n", queue[BRIDGEQ]);
        printf("North Light: %d\n", northLight);
        printf("South Light: %d\n", southLight);

		sleep(1);
	}
}

void clear_terminal(void){
	printf(CLEAR);
}

void initSimState(){

    sem_init(&semArrive, 0, 0);
    sem_init(&semDepart, 0, 0);


    com1 = open(usb, O_RDWR);

    if (com1 == -1){
        printf("open_port: Unable to open %s - ", usb);
        exit(EXIT_FAILURE);
    // } else {
    //     fcntl(com1, F_SETFL, 0);
    } else {
        printf("open_port: is open %s - \n", usb);
    }

    tcgetattr(com1, &settingsSimState);

    fcntl(com1, F_SETFL, O_NONBLOCK); 

    cfsetispeed(&settingsSimState, B9600);
    cfsetospeed(&settingsSimState, B9600);

    settingsSimState.c_cflag   = B9600 | CS8 | CSTOPB | CREAD | CLOCAL | HUPCL | INPCK;
    settingsSimState.c_lflag &= ~(ECHO | ECHONL | ICANON);
	tcsetattr(com1, TCSANOW, &settingsSimState);

    pthread_mutex_init(&ioMutex, NULL);
    pthread_mutex_init(&stateMutex, NULL);

    northLight = 0;
    southLight = 0;
    
}

void writeToPort(void *arg){
    // write and check that it passed serial
    pthread_mutex_lock(&ioMutex);
    int com1Temp = write(com1, &signal_out, 1);
    pthread_mutex_unlock(&ioMutex);
    if(com1Temp == -1){
        printf("write_port: Unable to write %d to %s",signal_out, usb);
        exit(EXIT_FAILURE);
    }

    pthread_t carThread;
    if((signal_out) == N_ARRIVAL){

        pthread_mutex_lock(&stateMutex);
        queue[NORTHQ]++;
        pthread_mutex_unlock(&stateMutex);
    }
    else if((signal_out) == N_ENTRY){
        //wait for semaphore to dispatch car (thread)
        sem_wait(&semDepart);
        pthread_mutex_lock(&stateMutex);
        queue[NORTHQ]--;
        pthread_mutex_unlock(&stateMutex);

        pthread_create(&carThread, NULL, &drive, NULL);
    }
    else if((signal_out) == S_ARRIVAL){
        pthread_mutex_lock(&stateMutex);
        queue[SOUTHQ]++;
        pthread_mutex_unlock(&stateMutex);

    }
    else if((signal_out) == S_ENTRY){
        //wait for semaphore to dispatch car (thread)
        sem_wait(&semDepart);
        pthread_mutex_lock(&stateMutex);
        queue[SOUTHQ]--;
        pthread_mutex_unlock(&stateMutex);
         
        pthread_create(&carThread, NULL, &drive, NULL);
    }
}


void *writePort(void *arg){

    while(1){
        if(signal_out){
            writeToPort(0);

            // reset signal out 
            pthread_mutex_lock(&stateMutex);
            signal_out = 0;
            pthread_mutex_unlock(&stateMutex);
        }
    }
}

void *readPort(void *arg){

    u_int8_t signal_in = 0;

    while(1){

        signal_in = 0;
        pthread_mutex_lock(&ioMutex);
        int isRead = read(com1, &signal_in, 1);
        pthread_mutex_unlock(&ioMutex);
        if (isRead != -1) {
            printf("reading: %d\n",signal_in);
        }

        
        /*
         * Determine next course of action depending on light status from controller
         */

        if (signal_in == (N_GREEN | S_RED)) {
            pthread_mutex_lock(&stateMutex);
            // update state
            signal_out = N_ENTRY;
            northLight = 1;
            southLight = 0;
            pthread_mutex_unlock(&stateMutex);
            // Allow car to pass bridge from north 
            sem_post(&semDepart);

        } else if (signal_in == (S_GREEN | N_RED)) {
            pthread_mutex_lock(&stateMutex);
            // update state
            signal_out = S_ENTRY;
            northLight = 0;
            southLight = 1;
            pthread_mutex_unlock(&stateMutex);
            // Allow car to pass bridge from south
            sem_post(&semDepart);

        } else if (signal_in == (S_RED | N_RED)) { //both red
            pthread_mutex_lock(&stateMutex);
            // update state
            signal_out = 0x0;
            northLight = 0;
            southLight = 0;
            pthread_mutex_unlock(&stateMutex);
        }

    }
}
/*
 * dispatches a car and updates bridge state
 */
void *drive(void* arg){

    pthread_mutex_lock(&stateMutex);
        queue[BRIDGEQ]++;
    pthread_mutex_unlock(&stateMutex);

    sleep(5); //time to cross bridge

    pthread_mutex_lock(&stateMutex);
        queue[BRIDGEQ]--;
    pthread_mutex_unlock(&stateMutex);

    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

    // first argument of program is serial file
    usb = argv[1];
    initSimState();

    pthread_t keyboardThread, guiThread, serialInThread, serialOutThread, simThread;

    pthread_create(&keyboardThread, NULL, &catchInput, NULL);
    pthread_create(&guiThread, NULL, &printGUI, NULL);
    pthread_create(&serialInThread, NULL, &readPort, NULL);
    pthread_create(&serialOutThread, NULL, &writePort, NULL);

    pthread_join(keyboardThread, NULL);
}
