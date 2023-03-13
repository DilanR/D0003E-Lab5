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

#define driveTime 5000000
#define waitTime  1000000

static struct termios settingsSimState;

int com1;

uint64_t direction;
uint64_t queue[3];
unsigned int lights;

sem_t semArrive;
sem_t semDepart;

pthread_t mutexState;
pthread_t mutexId;

void initSimState(void);
void writePort(u_int8_t str);
void *readPort(void *arg);
void drive(void *arg);
void letCarsDrive(void *arg);

#endif