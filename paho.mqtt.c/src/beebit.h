/*
#include "bee_des.h"
#include "bee_three_des.h"
#include "bee_aes.h"
#include "bee_elgamal.h"
#include "bee_rsa.h"
#include "bee_ecc.h"
#include "bee_cpabe.h"
#include "bee_kpabe.h"
#include "bee_hash.h"
#include "bee_md5.h"
#include "bee_sha_two.h"
#include "bee_sha_three.h"
#include "bee_ripemd.h"
*/
typedef struct
{
	/** The eyecatcher for this structure. Must be BEEBIT */
	const char struct_id[6];
	/** The version number of this structure.  Must be 0 */
	int struct_version;

        /* General */
	int security;

	/* CP-ABE */
	const unsigned char* pubKey;
	const unsigned char* secKey;
	const unsigned char* policy;
	//DES_Options* bee_des;
	//Three_DES_Options* bee_three_des;
	//AES_Options* bee_aes;
	//ElGamal_Options* bee_elgamal;
	//RSA_Options* bee_rsa;
	//ECC_Options* bee_ecc;
	//CPABE_Options* bee_cpabe;
	//KPABE_Options* bee_kpabe;
	//HASH_Options* bee_hash;
	//MD5_Options* bee_md5;
	//SHA_two_Options* bee_sha_two;
	//SHA_three_Options* bee_sha_three;
	//RIPEMD_Options* bee_ripemd;

} MQTTClient_BeeBitOptions;

#define MQTTClient_BeeBitOptions_initializer { \ 
	{'B', 'E', 'E','B','I','T'}, \
	0, \
	0, \
	NULL,\ 
	NULL,\
	NULL,\
	/*
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	NULL,\
	*/
}

#define DES 0
#define 3DES 1
#define AES 2
#define ElGamal 3
#define RSA 4
#define ECC 5
#define CPABE 6
#define KPABE 7
#define HASH 8
#define MD5 9
#define SHA_two 10
#define SHA_three 11
#define RIPEMD 12
