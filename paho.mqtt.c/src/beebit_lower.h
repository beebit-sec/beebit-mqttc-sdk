#ifndef BEEBIT_LOWER_H
#define BEEBIT_LOWER_H

extern int init_lower();
#include "beebit.h"

#define RV_LOWER 193

extern int beebit_lower_encode(const BeebitOptions*, char*, int, char**);
extern int beebit_lower_decode(const BeebitOptions*, char*, int, char**);

typedef struct {
	const char name[8];
} BeebitLOWEROptions;

#define BeebitLOWEROptions_initializer {{'R','V','_','L','O','W','E','R',}}

#endif
