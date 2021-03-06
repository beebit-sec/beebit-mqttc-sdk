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

typedef struct {
	beebit_handler encode;
	beebit_handler decode;
	unsigned char code;
}aaa;

typedef struct _aaa_list_data
{
	aaa value;
	struct _aaa_list_data* next;
}aaa_list_data;

typedef struct
{
	aaa_list_data* begin;

	aaa_list_data* lpCurrent;
}aaa_list;

extern aaa_list beebit_handler_map;

#include<stdlib.h>
inline static void aaa_list_push_front(aaa value)
{
	aaa_list_data* p = malloc(sizeof(aaa_list_data));
	if (!p)
		exit(-1);//bad alloc

	p->value = value;
	p->next = beebit_handler_map.begin;

	beebit_handler_map.begin = p;
}

inline static void aaa_list_iterator_constructor()
{
	beebit_handler_map.lpCurrent = beebit_handler_map.begin;
}

inline static aaa_list_data* aaa_list_iterator_notDone()
{
	return beebit_handler_map.lpCurrent;
}

inline static void aaa_list_iterator_next()
{
	beebit_handler_map.lpCurrent = beebit_handler_map.lpCurrent->next;
}

inline static aaa* aaa_list_iterator_currentItem()
{
	return &beebit_handler_map.lpCurrent->value;
}

extern int get_mqtt_tts_tl_byte_number(char* src);
extern int get_mqtt_tts_tl(char* src);

#define BeebitOptions_initializer {{'B','E','E','B','I','T'}, 0, 0, NULL}
#include "beebit_extend.h"

#endif
