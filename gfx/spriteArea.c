#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/basic/type_define.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"

/*スプライトエリアを設定する。*/
void makeSpriteArea(SPRITE_AREA* sprite_area,const SPRITE* sprite,int x,int y,int w,int h){
	sprite_area->sprite = sprite;
	GLfloat sx =  (GLfloat)x / sprite->RealWidth;
	GLfloat sy =  (GLfloat)y / sprite->RealHeight;
	GLfloat ex =  (GLfloat)(x+w) / sprite->RealWidth;
	GLfloat ey =  (GLfloat)(y+h) / sprite->RealHeight;
	GLfloat* coord = sprite_area->coord;
	coord[0] = ex;	coord[1] = sy;
	coord[2] = ex;	coord[3] = ey;
	coord[4] = sx;	coord[5] = ey;
	coord[6] = sx;	coord[7] = sy;
}
/*通常のスプライトエリアを設定する。*/
void makeDefaultSpriteArea(SPRITE_AREA* sprite_area,const SPRITE* sprite){
	sprite_area->sprite = sprite;
	GLfloat sx = 0.0f;
	GLfloat sy = 0.0f;
	GLfloat ex = (GLfloat)sprite->Width / sprite->RealWidth;
	GLfloat ey = (GLfloat)sprite->Height / sprite->RealHeight;
	GLfloat* coord = sprite_area->coord;
	coord[0] = ex;	coord[1] = sy;
	coord[2] = ex;	coord[3] = ey;
	coord[4] = sx;	coord[5] = ey;
	coord[6] = sx;	coord[7] = sy;
}

/*スプライトのエリアを描写する*/
void drawSpriteArea(const glPoint* point,const SPRITE_AREA* sprite_area,float angle){
	drawSpriteF(sprite_area->sprite,point,sprite_area->coord, angle,NULL);
}
void drawSpriteAreaA(const glPoint* point,const SPRITE_AREA* sprite_area,float angle){
	drawSpriteA(sprite_area->sprite,point,sprite_area->coord, angle,NULL);
}
void drawSpriteAreaC(const glPoint* point,const SPRITE_AREA* sprite_area,float angle,const GLfloat* color){
	drawSpriteF(sprite_area->sprite,point,sprite_area->coord, angle,color);
}
