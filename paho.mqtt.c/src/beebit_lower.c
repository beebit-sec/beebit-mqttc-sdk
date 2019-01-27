#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"beebit_lower.h"

void init_lower() {
	beebit_handler_map[RV_LOWER][ENCODE] = beebit_lower_encode;
	beebit_handler_map[RV_LOWER][DECODE] = beebit_lower_decode;
}

int beebit_lower_encode(const BeebitOptions* opt, char* src, int src_len, char** dst) {
	int dst_len = create_mqtt_tts_msg(opt->security, src, src_len, dst); 
	return dst_len;
}

int beebit_lower_decode(const BeebitOptions* opt, char* src, int src_len, char** dst) {	
	int multiplier = 1 ;
	int number = 1;
	int dst_len = 0;
	do {
		dst_len += (src[number] & 127) * multiplier;
		multiplier *= 128;
	 } while((src[number++] &128) != 0);

	char* dst_buf = (char*)malloc(sizeof(char)*dst_len);	
	memcpy(dst_buf, src+number, dst_len);

	int i;
	for(i=0;i<dst_len;i++) {
		dst_buf[i] = tolower(dst_buf[i]);
	}
	*dst = dst_buf;

	return dst_len;
}	
