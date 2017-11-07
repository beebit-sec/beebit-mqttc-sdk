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
} MQTTClient_BeeOptions;

#define MQTTClient_BeeOptions_initializer { \ 
	{'B', 'E', 'E','B','I','T'}, \
	0, \
	0, \
	NULL,\ 
	NULL,\
	NULL,\ 
}

#define CPABE 6
