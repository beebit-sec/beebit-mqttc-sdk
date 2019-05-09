#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "beebit.h"

beebit_handler beebit_handler_map[256][2];

void init_beebit() { 
	int i;
	for(i=0;i<NOM;i++) {
		init_sec_map[i]();
	}
}

int create_mqtt_tts_msg(unsigned char sec, char*payload, int payloadlen, char** dst) {

	int dst_len = 1; // Lenth of fixed header
	int rc = 0;

	dst_len += payloadlen;

	/* Generate compressed payload length */
	int payload_len = payloadlen;
	char* plen_buf = malloc(sizeof(char)*4);
	do {	
		char d = payload_len % 128;
              	payload_len /= 128;
              	if(payload_len > 0) {
              		d |= 0x80;
              	}
              	plen_buf[rc++] = d;
	} while (payload_len > 0);
	dst_len += rc;

	/* Generate MQTT-TTS message */
	char* dst_buf;	
	dst_buf = (char*)malloc(sizeof(char)*dst_len);	
	memcpy(dst_buf, &sec, 1);
	memcpy(dst_buf+1, plen_buf, rc);
	memcpy(dst_buf+1+rc, payload, payloadlen);
	*dst = dst_buf;
	free(plen_buf);
	return dst_len;
}

int get_mqtt_tts_tl_byte_number(char* src) {
	int multiplier = 1;
	int number = 1;
	int tl = 0;
	do {
		tl += (src[number] & 127) * multiplier;
		multiplier *= 128;
	} while((src[number++] &128) != 0);
	return number;
}

int get_mqtt_tts_tl(char* src) {
	int multiplier = 1;
	int number = 1;
	int tl = 0;
	do {
		tl += (src[number] & 127) * multiplier;
		multiplier *= 128;
	} while((src[number++] &128) != 0);
	return tl;
}
