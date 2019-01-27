#include <stdio.h>
#include <string.h>
#include "beebit.h"

beebit_handler beebit_handler_map[256][2];

void init_beebit() { 
	int i;
	for(i=0;i<NOM;i++) {
		init_sec_map[i]();
	}
}
