#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <bits/pthreadtypes.h>

//GUI
#define CLEAR "\033[2J"
void *printGUI(void *arg);
void clear_terminal(void);

static struct termios settingsGUI;

//Keyboard
#define ENQUEUNORTH 'n'
#define ENQUEUSOUTH 's'
#define EXIT 'e'

void *catchInput(void *ptr);
void sendNorth(int arg);
void sendSouth(int arg);

//queue
#define BRIDGEQ 0
#define NORTHQ  1
#define SOUTHQ  2


#define STOP        0b0000
//Sim State
#define N_ARRIVAL   0b0001
#define N_ENTRY     0b0010 
#define S_ARRIVAL   0b0100
#define S_ENTRY     0b1000

//Cont State
#define N_GREEN     0b0001
#define N_RED       0b0010
#define S_GREEN     0b0100
#define S_RED       0b1000

static struct termios settingsSimState;

void getLights(void);
void getQueue(void);
void initSimState();
void *writePort(void *arg);
void writeToPort(void *arg);
void *readPort(void *arg);
void *drive(void* arg);
void *letCarsDrive(void* arg);


#endif
