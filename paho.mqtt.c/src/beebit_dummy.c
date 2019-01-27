#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"beebit_dummy.h"

void init_dummy() {
	beebit_handler_map[RV_DUMMY][ENCODE] = beebit_dummy_encode;
	beebit_handler_map[RV_DUMMY][DECODE] = beebit_dummy_decode;
}

int beebit_dummy_encode(const BeebitOptions* opt, char* src, int src_len, char** dst) {
	int dst_len = create_mqtt_tts_msg(opt->security, src, src_len, dst); 
	return dst_len;
}

int beebit_dummy_decode(const BeebitOptions* opt, char* src, int src_len, char** dst) {	
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
		dst_buf[i] = toupper(dst_buf[i]);
	}
	*dst = dst_buf;

	return dst_len;
}	
