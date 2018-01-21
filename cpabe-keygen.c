#include <stdio.h>
#include "../beebitcpabe.h"

int main(void)
{
	if(cpabe_keygen("./Key1","./pubKey","./mstKey",3,"assistant","unoop","years = 2") == -1){
		printf("KEY1 ERROR\n");
		return -1;
	}
	printf("KEY1 SUCCESS\n");

	char* p[] = {"student","years = 1"};
	
	if(cpabe_vkeygen("./Key2","./pubKey","./mstKey",2, p) == -1){
		printf("KEY2 ERROR\n");
		return -1;
	}
	printf("KEY2 SUCCESS\n");
	
	if(cpabe_keygen("./Key3","./pubKey","./mstKey",3,"student","years = 4","passoop") == -1){
		printf("KEY3 ERROR\n");
		return -1;
	}
	printf("KEY3 SUCCESS\n");
	
	if(cpabe_keygen("./Key4","./pubKey","./mstKey",2,"teacher","years = 1") == -1){
		printf("KEY4 ERROR\n");
		return -1;
	}
	printf("KEY4 SUCCESS\n");
	
	if(cpabe_keygen("./Key5","./pubKey","./mstKey",2,"assistant","years = 5") == -1){
		printf("KEY5 ERROR\n");
		return -1;
	}
	printf("KEY5 SUCCESS\n");
	
	if(cpabe_keygen("./Key6","./pubKey","./mstKey",2,"teacher","years = 5") == -1){
		printf("KEY6 ERROR\n");
		return -1;
	}
	printf("KEY6 SUCCESS\n");
	
	if(cpabe_keygen("./Key7","./pubKey","./mstKey",2,"student","years = 3") == -1){
		printf("KEY7 ERROR\n");
		return -1;
	}
	printf("KEY7 SUCCESS\n");
	
	if(cpabe_keygen("./Key8","./pubKey","./mstKey",3,"administrative","teacher","years = 4") == -1){
		printf("KEY8 ERROR\n");
		return -1;
	}
	printf("KEY8 SUCCESS\n");
	
	if(cpabe_keygen("./Key9","./pubKey","./mstKey",3,"assistant","unoop","years = 4") == -1){
		printf("KEY9 ERROR\n");
		return -1;
	}
	printf("KEY9 SUCCESS\n");
	
	if(cpabe_keygen("./Key10","./pubKey","./mstKey",3,"student","passoop","years = 7") == -1){
		printf("KEY10 ERROR\n");
		return -1;
	}
	printf("KEY10 SUCCESS\n");
	
	return 0;
}
