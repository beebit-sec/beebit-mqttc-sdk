#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<beebitcpabe.h>
#include"beebit.h"

/* Generate MQTT-TTS packet */
int beebit_encode(BeebitOptions* opt, unsigned char* src, unsigned char** pkt) {
	unsigned char* dst = NULL;
	int dst_len = 0;
	int pkt_len = 1; // Lenth of fixed header
	int rc = 0;

	/* Perform security mechanism */
	switch(opt->security) {
	case AC_CPABE:
		dst_len = cpabe_enc(((BeebitCPABEOptions*)(opt->opts))->pk, src, ((BeebitCPABEOptions*)(opt->opts))->ap, &dst);
		if(dst_len == -1) {
			printf("ENC ERROR!\n");
			return EXIT_FAILURE;
		}
		printf("%d\n", dst_len);
		break;
	case SC_AES:
		break;
	default :
		break;
	}
	pkt_len += dst_len;

	/* TODO: Generate security specific header */


	/* Generate compressed payload length */
	int encode_len = dst_len;
	unsigned char* bee_len_buf = malloc(sizeof(unsigned char)*4);
	do {	
		char d = encode_len % 128;
              	encode_len /= 128;
              	if(encode_len > 0) {
              		d |= 0x80;
              	}
              	bee_len_buf[rc++] = d;
	} while (encode_len > 0);
	pkt_len += rc;

	/* Generate MQTT-TTS packet */
	unsigned char* bee_buf_temp;	
	switch(opt->security) {
	case AC_CPABE:
		bee_buf_temp = (unsigned char*)malloc(sizeof(unsigned char)*pkt_len);	
		memcpy(bee_buf_temp, &(opt->security), 1);
		memcpy(bee_buf_temp+1, bee_len_buf, rc);
		memcpy(bee_buf_temp+1+rc, dst, dst_len);
		*pkt = bee_buf_temp;
		free(bee_len_buf);
		break;
	case SC_AES:
		break;
	default :
		break;
	}
	return pkt_len;
}

int beebit_decode(BeebitOptions* opt, unsigned char* src, unsigned char** pkt) {	
	int multiplier = 1 ;
	int number = 1;
	int value = 0;
	do {
		value += (src[number] & 127) * multiplier;
		multiplier *= 128;
	 } while((src[number++] &128) != 0);
	
	int len = 0;
	switch(src[0]) {
	case AC_CPABE:
		printf("%d\n",value);
		len = cpabe_dec(((BeebitCPABEOptions*)(opt->opts))->pk,((BeebitCPABEOptions*)(opt->opts))->sk, src+number, pkt);
		if(len == -1){
			printf("DEC FAIL\n");
			return -1;
		}
		break;
	case SC_AES:
		break;
	default :
		break;
	}
	return len;
}	
