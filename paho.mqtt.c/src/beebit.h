/*
#include "Bee_des.h"
#include "Bee_three_des.h"
#include "Bee_elgamal.h"
#include "Bee_rsa.h"
#include "Bee_ecc.h"
#include "Bee_kpabe.h"
#include "Bee_hash.h"
#include "Bee_md5.h"
#include "Bee_sha_two.h"
#include "Bee_sha_three.h"
#include "Bee_ripemd.h"
*/

#include "Bee_CPABE.h"
#include "Bee_AES.h"

typedef struct
{
	/** The eyecatcher for this structure. Must be BEEBIT */
	const char struct_id[6];
	/** The version number of this structure.  Must be 0 */
	int struct_version;

        /* General */
	int security;

	/* CP-ABE */
	
	void* options;
//	Bee_CPABE_Options* options;

} MQTTClient_BeeBitOptions;

#define MQTTClient_BeeBitOptions_initializer { \ 
	{'B', 'E', 'E','B','I','T'}, \
	0, \
	0, \
	NULL, \
}

#define DES 0
#define Three_DES 1
#define AES 2
#define ElGamal 3
#define Rsa 4
#define ECC 5
#define CPABE 6
#define KPABE 7
#define HASH 8
#define MD5 9
#define SHA_two 10
#define SHA_three 11
#define RIPEMD 12
