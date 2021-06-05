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

typedef struct encode_info {
	beebit_handler encode;
	beebit_handler decode;
	unsigned char code;
} encode_info;

typedef struct encode_info_list_node {
	encode_info value;
	struct encode_info_list_node* next;
} encode_info_list_node;

typedef struct encode_info_list {
	encode_info_list_node* head;
} encode_info_list;

extern encode_info_list beebit_handler_map;

extern int encode_info_list_push_front(encode_info value);

extern int get_mqtt_tts_tl_byte_number(char* src);
extern int get_mqtt_tts_tl(char* src);

#define BeebitOptions_initializer {{'B','E','E','B','I','T'}, 0, 0, NULL}
#include "beebit_extend.h"

#endif
