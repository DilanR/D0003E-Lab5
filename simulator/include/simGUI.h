#ifndef _SIMGUI_
#define _SIMGUI_

#include <stdio.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include "simState.h"

#define CLEAR "\033[2J"
void initGUI(void);
void printGUI(void);
void setting(void);
void clear_terminal(void);



static struct termios settingsGUI;


#endif
