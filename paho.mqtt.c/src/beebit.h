#ifndef BEEBIT_H
#define BEEBIT_H

typedef struct {
	/** The eyecatcher for this structure. Must be BEEBIT */
	const char struct_id[6];

	/** The version number of this structure.  Must be 0 */
	int struct_version;

        /* Security mechanism */
	unsigned char security;

	/* Options for security mechanism*/
	void* opts;
} BeebitOptions;

extern void init_beebit();
extern int create_mqtt_tts_msg(unsigned char sec, char*payload, int payloadlen, char** dst);
typedef int (*beebit_handler)(BeebitOptions*, char*, int, char**);
extern beebit_handler beebit_handler_map[256][2];

#define BeebitOptions_initializer {{'B','E','E','B','I','T'}, 0, 0, NULL}
#define ENCODE 0
#define DECODE 1
#include "beebit_extend.h"

#endif
