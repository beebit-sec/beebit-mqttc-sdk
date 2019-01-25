#ifndef BEEBIT_ASYNC_H
#define BEEBIT_ASYNC_H

#include "beebit_cpabe.h"
#include "beebit_aes.h"

typedef struct
{
	/** The eyecatcher for this structure. Must be BEEBIT */
	const char struct_id[6];
	/** The version number of this structure.  Must be 0 */
	int struct_version;

        /* General */
	int security;

	/* CP-ABE */
	void* opts;
} BeebitAsyncOptions;

#define BeebitAsyncOptions_initializer {{'B', 'E', 'E','B','I','T'},0,0,NULL}

#define AC_CPABE 67

#endif
