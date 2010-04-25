#ifndef SPRITE_H_
#define SPRITE_H_
/*�e�N�X�`�����Ǘ�����A�X�v���C�g*/

typedef struct{
	GLuint TexID;		//�e�N�X�`��ID
	int blending;
	int	Width;		//�h�b�g��
	int RealWidth;
	int	Height;		//�h�b�g��
	int RealHeight;
}SPRITE;
/*������*/
void initSpriteSystem();
/*��̃X�v���C�g���쐬*/
void makeEmptySprite(SPRITE* sprite,int w, int h,int blending,int enable_compression);
/*�㏑�����邩�A�V�K�쐬��*/
void updateSpriteFromSurface(SPRITE* sprite,SDL_Surface* surface,int enable_compression);
void getSpriteFromSurface(SPRITE* sprite,SDL_Surface* surface,int blending,int enable_compression);
/*�T�C�Y����ݒ�*/
void setSpriteSizeInformation(SPRITE* sprite,int w,int h);
/*�X�v���C�g���폜*/
void deleteSprite(SPRITE* sprite);
void drawSpriteA(const SPRITE* sprite,const glPoint* point,const GLfloat coord[8] ,float angle,const GLfloat* color);
void drawSpriteF(const SPRITE* sprite,const glPoint* point,const GLfloat coord[8] ,float angle,const GLfloat* color);
/*��ׂ̂���ōł��������̂�T��*/
int getMinPowerOfTwo(int num);
void getSpriteFromOPS(SPRITE *sprite,SDL_RWops* data,int blending,int enable_compression);
void getSpriteFromArchive(SPRITE* sprite,ARCHIVE* archive,const char* filename,int blending,int enable_compression);
#endif
