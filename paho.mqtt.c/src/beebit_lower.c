#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"beebit_lower.h"

void init_lower() {
	aaa tmp = { beebit_lower_encode,beebit_lower_decode,RV_LOWER };
	aaa_list_push_front(tmp);
}

int beebit_lower_encode(const BeebitOptions* opt, char* src, int src_len, char** dst) {
	int dst_len = create_mqtt_tts_msg(opt->security, src, src_len, dst); 
	return dst_len;
}

int beebit_lower_decode(const BeebitOptions* opt, char* src, int src_len, char** dst) {	
	int number = get_mqtt_tts_tl_byte_number(src);
	int tl = get_mqtt_tts_tl(src);

	char* dst_buf = (char*)malloc(sizeof(char)*tl);	
	memcpy(dst_buf, src+number, tl);

	int i;
	for(i=0;i<tl;i++) {
		dst_buf[i] = tolower(dst_buf[i]);
	}
	*dst = dst_buf;

	return tl;
}
