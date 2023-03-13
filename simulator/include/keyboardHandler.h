#ifndef _KEYBOARDHANDLER_
#define _KEYBOARDHANDLER_

#include <stdio.h>
#include <stdlib.h>



#define ENQUEUNORTH 'n'
#define ENQUEUSOUTH 's'
#define EXIT 'e'


void *catchInput(void *ptr);

void sendNorth(int arg);
void sendSouth(int arg);


#endif
