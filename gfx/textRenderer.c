#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_ttf.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/basic/type_define.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/textRenderer.h"
/**
 * �e�L�X�g��`�悵�āA�X�v���C�g�ɕϊ����܂��B
 * ����́A
 * SDL_ttf�ŃT�[�t�F�C�X���쐬���X�v���C�g�Ɏg����`���ɕϊ�
 * ���X�v���C�g�i�e�N�X�`���j��
 * �e�N�X�`���͊�{�I�Ɉꖇ���g���܂킵
 */
 
 static TTF_Font* Font;			//�t�H���g�i�[
 static SPRITE RenderingSprite;	//�����_�����O�p�B���̃X�v���C�g�ɏ������Ƃ��ł���B
 /**
  * ���������܂��B
  */
int initTextRenderer(SDL_RWops *src,int default_fontsize){
	Font = TTF_OpenFontRW(src,1,default_fontsize);
	//�\���ɑ傫�ȗ̈���m��
	makeEmptySprite(&RenderingSprite,default_fontsize<<3,default_fontsize<<4,TRUE,TRUE);
	if(Font != NULL) return TRUE;
	return FALSE;
}
/**
 * �I�����܂��B
 */
void quitTextRenderer(){
	TTF_CloseFont(Font);
	Font = NULL;
}
//RenderingSprite���g���ĕ`��
void drawText(const glPoint* point,const char* text){
}
//�w�肳�ꂽ�X�v���C�g�ɕ`��A�V�K�쐬
void updateTextSprite(SPRITE* sprite,const char* text){
}
//�w�肳�ꂽ�X�v���C�g�ɕ`��A�A�b�v�f�[�g
void makeTextSprite(SPRITE* sprite,const char* text){
}
