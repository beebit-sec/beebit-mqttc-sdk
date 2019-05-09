#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"beebit_lower.h"

void init_dummy() {
	beebit_handler_map[RV_DUMMY][ENCODE] = beebit_dummy_encode;
	beebit_handler_map[RV_DUMMY][DECODE] = beebit_dummy_decode;
}

int beebit_dummy_encode(const BeebitOptions* opt, char* src, int src_len, char** dst) {
	int dst_len = create_mqtt_tts_msg(opt->security, src, src_len, dst); 
	return dst_len;
}

int beebit_dummy_decode(const BeebitOptions* opt, char* src, int src_len, char** dst) {	
	int number = get_mqtt_tts_tl_byte_number(src);
	int tl = get_mqtt_tts_tl(src);

	char* dst_buf = (char*)malloc(sizeof(char)*tl);	
	memcpy(dst_buf, src+number, tl);
	*dst = dst_buf;

	return tl;
}	
