typedef struct 
{
	const unsigned char* pubKey;
	const unsigned char* secKey;
	const unsigned char* policy;

} Bee_CPABE_Options;

#define Bee_CPABE_Options_initializer { \	
	NULL, \
	NULL, \
	NULL, \
}
