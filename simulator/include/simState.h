#ifndef _SIMSTATE_
#define _SIMSTATE_

#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
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

u_int64_t queue[3];

void initSimState(void);
void writePort(u_int8_t str);
void *readPort(void *arg);
void drive(u_int8_t arg);
void letCarsDrive(u_int8_t arg);
u_int8_t getLights(void);
int getCom(void);

#endif
