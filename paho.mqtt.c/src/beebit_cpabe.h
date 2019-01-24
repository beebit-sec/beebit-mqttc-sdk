#ifndef BEEBIT_CPABE_H
#define BEEBIT_CPABE_H

typedef struct 
{
	const unsigned char* pk; // public key
	const unsigned char* sk; // secret key
	const unsigned char* ap; // access policy

} BeebitCPABEOptions;

#define BeebitCPABEOptions_initializer {NULL, NULL, NULL}

#endif
