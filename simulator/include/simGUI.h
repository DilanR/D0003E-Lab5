#ifndef simGUI.h
#define simGUI.h

#include <stdio.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include "simState.h"


void initGUI(void);
void printGUI(void);
void settingGUI(void);

static struct termios settingsGUI;


#endif