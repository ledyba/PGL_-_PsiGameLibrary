#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/gfx/graphic.h"
   
SDL_Surface* getTextureSurface(SDL_Surface* Image,int width, int height,int blending){
	int flag = SDL_SWSURFACE;
	int depth = 0;
	Uint32 r = 0,g = 0,b = 0,a = 0;
	/*ブレンディングごとの設定*/
	if(blending == TRUE){
		depth = 32;
		flag |= SDL_SRCALPHA;
		#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
		r =	0x000000FF; 
		g =	0x0000FF00; 
		b =	0x00FF0000; 
		a =	0xFF000000;
		#else
		r = 0xFF000000;
		g = 0x00FF0000;
		b = 0x0000FF00;
		a = 0x000000FF;
		#endif
	}else{
		depth = 24;
		flag |= 0;
		#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
		r = 0x0000FF;
		g = 0x00FF00;
		b = 0xFF0000;
		a = 0x000000;
		#else
		r = 0xFF0000;
		g = 0x00FF00;
		b = 0x0000FF;
		a = 0x000000;
		#endif
	}
	/*サーフェイスの作成*/
	SDL_Surface *tmpImage = SDL_CreateRGBSurface( flag, width, height, depth,r,g,b,a);
	if( Image != NULL ){
		if(blending){
			SDL_SetAlpha(Image,0,0);
		}
		/*サイズを設定する。*/
		SDL_Rect area = {0,0,Image->w,Image->h};
		/*合成*/
	    SDL_BlitSurface(Image,&area,tmpImage,&area);
	}
	/*
	char R,B,G,A;
	char* pixel = tmpImage->pixels;
	memcpy(&R,pixel,sizeof(R));
	memcpy(&G,pixel+1,sizeof(G));
	memcpy(&B,pixel+2,sizeof(B));
	memcpy(&A,pixel+3,sizeof(A));
	fprintf(stdout,"%02x,%02x,%02x,%02x\n",(char)R,(char)G,(char)B,(char)A);
	static int once = 5;
	if(blending && once == 0){
		SDL_SetAlpha(Image_converted,0,0);
		SDL_SaveBMP(Image_converted,"1.bmp");
		SDL_SetAlpha(Image,0,0);
		SDL_SaveBMP(Image,"2.bmp");
		SDL_SetAlpha(tmpImage,0,0);
		SDL_SaveBMP(tmpImage,"3.bmp");
	}
	once--;
	*/
	return tmpImage;
}
    /*VRAMにテクスチャをおく*/
    const static GLfloat prioritie = 1.0;
GLuint genNewTextureID(){
	GLuint id;
	glGenTextures( 1, &id );
	/*テクスチャの優先度の設定*/
    glPrioritizeTextures(1,&id,&prioritie);
	return id;
}

SDL_Surface* loadGraphix(SDL_RWops* data){
	return IMG_LoadPNG_RW(data);
}


