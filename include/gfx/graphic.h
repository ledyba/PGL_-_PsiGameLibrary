#ifndef GRAPHIC_H_
#define GRAPHIC_H_
/*テクスチャを生成して、返す。*/
SDL_Surface* getTextureSurface(SDL_Surface* Image,int width, int height,int blending);
GLuint genNewTextureID();
SDL_Surface* loadGraphix(SDL_RWops* data);
#endif
