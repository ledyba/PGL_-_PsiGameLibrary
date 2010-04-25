#ifndef SPRITE_AREA_H_
#define SPRITE_AREA_H_
/*スプライトの一部分を表すオブジェクト*/

typedef struct{
	const SPRITE* sprite;
	GLfloat coord[8];
}SPRITE_AREA;

void makeSpriteArea(SPRITE_AREA* sprite_area,const SPRITE* sprite,int x,int y,int w,int h);
void makeDefaultSpriteArea(SPRITE_AREA* sprite_area,const SPRITE* sprite);
void drawSpriteArea(const glPoint* point,const SPRITE_AREA* sprite_area,float angle);
void drawSpriteAreaA(const glPoint* point,const SPRITE_AREA* sprite_area,float angle);
void drawSpriteAreaC(const glPoint* point,const SPRITE_AREA* sprite_area,float angle,const GLfloat* color);

#endif
