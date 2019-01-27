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
	int dst_len = 1; // Lenth of fixed header
	int rc = 0;

	ct_len = cpabe_enc_l(((BeebitCPABEOptions*)(opt->opts))->pk, src, src_len, ((BeebitCPABEOptions*)(opt->opts))->ap, &ct);

	if(ct_len == -1) {
		printf("[AC_CPABE] Encrypt failed!\n");
		return EXIT_FAILURE;
	}
	dst_len += ct_len;

	/* MQTT-TTS header filed: payload length */
	int payload_len = ct_len;
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

	/* Generate MQTT-TTS packet */
	char* dst_buf;	
	dst_buf = (char*)malloc(sizeof(char)*dst_len);	
	memcpy(dst_buf, &(opt->security), 1); // Fixed header
	memcpy(dst_buf+1, plen_buf, rc);   // Payload length
	memcpy(dst_buf+1+rc, ct, ct_len);   // Payload (ciphertext)
	*dst = dst_buf;

	free(ct);
	free(plen_buf);
	return dst_len;
}

/* MQTT-TTS -> MQTT */
int beebit_cpabe_decode(const BeebitOptions* opt, char* src, int src_len, char** dst) {	
	int multiplier = 1 ;
	int number = 1;
	int ct_len = 0;
	do {
		ct_len += (src[number] & 127) * multiplier;
		multiplier *= 128;
	 } while((src[number++] &128) != 0);
	
	int dst_len = 0;
	dst_len = cpabe_dec(((BeebitCPABEOptions*)(opt->opts))->pk,((BeebitCPABEOptions*)(opt->opts))->sk, src+number, dst);
	if(dst_len == -1){
		printf("[AC_CPABE] Decrypt failed!\n");
		return -1;
	}

	return dst_len;
}	
