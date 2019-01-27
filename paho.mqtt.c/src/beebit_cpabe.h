#ifndef BEEBIT_CPABE_H
#define BEEBIT_CPABE_H

extern void init_cpabe();
#include "beebit.h"

#define AC_CPABE 67

extern int beebit_cpabe_encode(const BeebitOptions*, char*, int, char**);
extern int beebit_cpabe_decode(const BeebitOptions*, char*, int, char**);

typedef struct {
	const char* pk; // public key
	const char* sk; // secret key
	const char* ap; // access policy
} BeebitCPABEOptions;

#define BeebitCPABEOptions_initializer {NULL, NULL, NULL}

#endif
