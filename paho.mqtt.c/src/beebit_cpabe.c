#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<beebitcpabe.h>
#include"beebit_cpabe.h"

void init_cpabe() {
	beebit_handler_map[AC_CPABE][ENCODE] = beebit_cpabe_encode;
	beebit_handler_map[AC_CPABE][DECODE] = beebit_cpabe_decode;
}

/* MQTT -> MQTT-TTS */ 
int beebit_cpabe_encode(const BeebitOptions* opt, char* src, int src_len, char** dst) {
	char* ct = NULL;
	int ct_len = 0;
	
	ct_len = cpabe_enc_l(((BeebitCPABEOptions*)(opt->opts))->pk, src, src_len, ((BeebitCPABEOptions*)(opt->opts))->ap, &ct);

	if(ct_len == -1) {
		printf("[AC_CPABE] Encrypt failed!\n");
		return EXIT_FAILURE;
	}

	int dst_len = create_mqtt_tts_msg(opt->security, ct, ct_len, dst);

	return dst_len;
}

/* MQTT-TTS -> MQTT */
int beebit_cpabe_decode(const BeebitOptions* opt, char* src, int src_len, char** dst) {	
	int number = get_mqtt_tts_tl_byte_number(src);
	int tl = get_mqtt_tts_tl(src);

	int dst_len = 0;
	dst_len = cpabe_dec(((BeebitCPABEOptions*)(opt->opts))->pk,((BeebitCPABEOptions*)(opt->opts))->sk, src+number, tl, dst);
	if(dst_len == -1){
		printf("[AC_CPABE] Decrypt failed!\n");
		return -1;
	}

	return dst_len;
}	
