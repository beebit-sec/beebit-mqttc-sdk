#include"beebit_Async.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<beebitcpabe.h>

#define SIZE 10

int beebit_encode_Async(BeebitAsyncOptions* beehandle, char* pt, char** bee_buf)
{
	unsigned char* ct = NULL;
	int enc_length=0;
	int rc = 0;

	switch(beehandle->security)
	{
		case AC_CPABE:
			enc_length = cpabe_enc(((BeebitCPABEOptions*)(beehandle->opts))->pk, pt, strlen(pt), ((BeebitCPABEOptions*)(beehandle->opts))->ap, &ct);
			if(enc_length == -1){
				printf("ENC ERROR!\n");
				return -1;
			}
			break;
	}

	int encodelen = enc_length;

	unsigned char* bee_len_buf = malloc(sizeof(unsigned char)*4);
	do
	{	
		char d = encodelen % 128;
              	encodelen /= 128;
              	if(encodelen > 0)
              	{
              		d |= 0x80;
              	}
              	bee_len_buf[rc++] = d;
	} while (encodelen > 0);

	unsigned char* bee_buf_temp = malloc(sizeof(unsigned char)*(rc + enc_length));	
	switch(beehandle->security)
	{
		case AC_CPABE:
			memcpy(bee_buf_temp,&(beehandle->security), 1);
			memcpy(bee_buf_temp+1,bee_len_buf, rc);
			memcpy(bee_buf_temp+rc+1, ct, enc_length);
			*bee_buf = bee_buf_temp;
			break;
	}
	return enc_length+rc+1;
}

int beebit_decode_Async(BeebitAsyncOptions* beehandle, char* ct, char** pt)
{	
	int multiplier = 1 ;
	int number = 1;
	int value = 0;
	do
	{
		value += (ct[number] &127) * multiplier;
		multiplier *= 128;
	 } while((ct[number++] &128) != 0);
	*(ct+number+value)='\0';
	int length=0;
	switch(ct[0])
	{
		case AC_CPABE:
			length=cpabe_dec(((BeebitCPABEOptions*)(beehandle->opts))->pk,((BeebitCPABEOptions*)(beehandle->opts))->sk, ct+number, value, pt);
			if(length==-1){
				printf("DEC FAIL\n");
				return -1;
			}
			break;
	}
	return length;
}	
