#ifndef BEEBIT_H
#define BEEBIT_H

#include "beebit_cpabe.h"
#include "beebit_aes.h"

typedef struct {
	/** The eyecatcher for this structure. Must be BEEBIT */
	const char struct_id[6];

	/** The version number of this structure.  Must be 0 */
	int struct_version;

        /* Security mechanism */
	int security;

	/* Options for security mechanism*/
	void* opts;
} BeebitOptions;

#define BeebitOptions_initializer {{'B', 'E', 'E','B','I','T'}, 0, 0, NULL}

#define SC_DES 0
#define SC_TDES 1
#define SC_AES 2
#define AC_ELG 64
#define AC_RSA 65
#define AC_ECC 66
#define AC_CPABE 67
#define AC_KPABE 68
#define HS_HASH 128
#define HS_MD5 129
#define HS_SHA2 130
#define HS_SHA3 131
#define HS_RIPEMD 132

#endif
