typedef struct 
{
	const unsigned char* pubKey;
	const unsigned char* secKey;

} Bee_AES_Options;

#define Bee_AES_Options_initializer { \	
	NULL, \
	NULL, \
}
