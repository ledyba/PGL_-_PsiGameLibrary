#ifndef SPRITE_H_
#define SPRITE_H_
/*テクスチャを管理する、スプライト*/

typedef struct{
	GLuint TexID;		//テクスチャID
	int blending;
	int	Width;		//ドット数
	int RealWidth;
	int	Height;		//ドット数
	int RealHeight;
}SPRITE;
/*初期化*/
void initSpriteSystem();
/*空のスプライトを作成*/
void makeEmptySprite(SPRITE* sprite,int w, int h,int blending,int enable_compression);
/*上書きするか、新規作成か*/
void updateSpriteFromSurface(SPRITE* sprite,SDL_Surface* surface,int enable_compression);
void getSpriteFromSurface(SPRITE* sprite,SDL_Surface* surface,int blending,int enable_compression);
/*サイズ情報を設定*/
void setSpriteSizeInformation(SPRITE* sprite,int w,int h);
/*スプライトを削除*/
void deleteSprite(SPRITE* sprite);
void drawSpriteA(const SPRITE* sprite,const glPoint* point,const GLfloat coord[8] ,float angle,const GLfloat* color);
void drawSpriteF(const SPRITE* sprite,const glPoint* point,const GLfloat coord[8] ,float angle,const GLfloat* color);
/*二のべき乗で最も小さいのを探す*/
int getMinPowerOfTwo(int num);
void getSpriteFromOPS(SPRITE *sprite,SDL_RWops* data,int blending,int enable_compression);
void getSpriteFromArchive(SPRITE* sprite,ARCHIVE* archive,const char* filename,int blending,int enable_compression);
#endif
