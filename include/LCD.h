#include <avr/io.h>
#define MASK_0	0xF
#define MASK_1	0xF0
#define MASK_2	0xF00
#define MASK_3	0xF000

void LCDInit(void);
void writeChar(char ch, int pos);
void printAt(long num, int pos);
