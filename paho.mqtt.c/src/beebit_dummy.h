#ifndef BEEBIT_DUMMY_H
#define BEEBIT_DUMMY_H

extern int init_dummy();
#include "beebit.h"

#define RV_DUMMY 192

extern int beebit_dummy_encode(const BeebitOptions*, char*, int, char**);
extern int beebit_dummy_decode(const BeebitOptions*, char*, int, char**);

typedef struct {
	const char name[8];
} BeebitDUMMYOptions;

#define BeebitDUMMYOptions_initializer {{'R','V','_','D','U','M','M','Y',}}

#endif
