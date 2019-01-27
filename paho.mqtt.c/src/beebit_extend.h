#ifndef BEEBIT_EXTEND_H
#define BEEBIT_EXTEND_H

#define NOM 2

/* Ciphertext-Policy Attribute-Based Encryption */
#include "beebit_cpabe.h"
#include "beebit_dummy.h"

typedef void (*init_sec)();
extern init_sec init_sec_map[NOM];

#define __EXTEND__ "AC_CPABE,67\n"\
		   "DUMMY, 192"

#endif

//#define SC_DES 0
//#define SC_TDES 1
//#define SC_AES 2
//#define AC_ELG 64
//#define AC_RSA 65
//#define AC_ECC 66
//#define AC_CPABE 67
//#define AC_KPABE 68
//#define HS_HASH 128
//#define HS_MD5 129
//#define HS_SHA2 130
//#define HS_SHA3 131
//#define HS_RIPEMD 132
//#define RV_DUMMY 192
