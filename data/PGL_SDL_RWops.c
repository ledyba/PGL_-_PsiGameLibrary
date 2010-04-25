#include <stdio.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_rwops.h>
#include "../include/data/PGL_SDL_RWops.h"

/*�N���[�Y�����A����������ύX����*/
static int PGL_mem_close(SDL_RWops *context)
{
	if ( context ) {
		//���������J��
		free(context->hidden.mem.base);
		SDL_FreeRW(context);
	}
	return(0);
}

/*����������m��*/
SDL_RWops *PGL_SDL_RWFromMem(void *mem, int size){
	SDL_RWops *ops = SDL_RWFromMem(mem,size);
	if(ops != NULL){
		ops->close = PGL_mem_close;
	}
	return ops;
};

