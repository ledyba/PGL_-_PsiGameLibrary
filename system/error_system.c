#include <stdio.h>
#include <windows.h>
#include "../include/system/error_system.h"


static void (*quit_func)();

void initErrorSystem(void (*quit)()){
	quit_func = quit;
}
void raiseError(const char* error ,const char* error2){
	fprintf(stderr,error);
	fprintf(stderr,error2);
	fprintf(stderr,"\n");
	quit_func();
	exit(0);
}
