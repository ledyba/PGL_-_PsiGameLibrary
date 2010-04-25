#ifndef ERROR_SYSTEM_H_
#define ERROR_SYSTEM_H_
/*ErrorSystem*/
void initErrorSystem(void (*quit)());
void raiseError(const char* error ,const char* error2);
#endif
