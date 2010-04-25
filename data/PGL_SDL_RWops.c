#include <stdio.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_rwops.h>
#include "../include/data/PGL_SDL_RWops.h"

/*クローズだけ、少し挙動を変更する*/
static int PGL_mem_close(SDL_RWops *context)
{
	if ( context ) {
		//メモリを開放
		free(context->hidden.mem.base);
		SDL_FreeRW(context);
	}
	return(0);
}

/*メモリから確保*/
SDL_RWops *PGL_SDL_RWFromMem(void *mem, int size){
	SDL_RWops *ops = SDL_RWFromMem(mem,size);
	if(ops != NULL){
		ops->close = PGL_mem_close;
	}
	return ops;
};

