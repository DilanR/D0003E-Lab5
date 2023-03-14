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

//State
#define Bridge 0
#define North  1
#define South  2

#define bothRed      0
#define northGsouthR 1
#define southGnorthR 2

static struct termios settingsSimState;

void getLights(void);
void getQueue(void);
void initSimState(void);
void *writePort(void *str);
void *readPort(void *arg);
void *drive(void* arg);
void *letCarsDrive(void* arg);


#endif
