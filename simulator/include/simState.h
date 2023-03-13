#ifndef simState.h
#define simState.h

#include <stdio.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>

#define Bridge 0
#define North  1
#define South  2

#define bothRed      0
#define northGsouthR 1
#define southGnorthR 2

static struct termios settingsSimState;

int port;

uint64_t direction;
uint64_t queue[3];
unsigned int lights;

sem_t semArrive;
sem_t semDepart;

pthread_t mutexState;
pthread_t mutexId;

void initSimState(void);
void *arrivalW(void *arg);
void arrival(uint64_t direction);
void *departureNS(void *arg);
void *carsOnBridge(void *arg);
void *readPort(void *arg);


#endif