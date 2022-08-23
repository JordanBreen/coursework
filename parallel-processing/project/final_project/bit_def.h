#ifndef BIT_DEF_H
#define BIT_DEF_H
#include <math.h>
#define in_bit_range(i, b) ((i) < (pow(2,b)) ? (1) : (0))

typedef unsigned char  bit_8,  byte_1, byte;
typedef unsigned short bit_16, byte_2;
typedef unsigned int   bit_32, byte_4;
typedef unsigned long  bit_64, byte_8;
#endif
