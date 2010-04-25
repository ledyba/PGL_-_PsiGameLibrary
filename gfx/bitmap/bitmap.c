#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../../include/basic/type_define.h"
#include "../../include/system/error_system.h"
#include "../../include/data/data.h"
#include "../../include/gfx/graphic.h"
#include "../../include/gfx/sprite.h"
#include "../../include/gfx/spriteArea.h"
#include "../../include/gfx/bitmap/bitmap.h"


//�X�v���C�g�̍쐬
void getSpriteFromBitmap(SPRITE* sprite,const PGL_BITMAP* bitmap,const PGL_PALETTE* palette){
	SDL_Surface* temp = getTextureSurface(NULL,bitmap->w,bitmap->h,palette->blending);
	//�萔�F�s�b�`
	int pitch = 3;
	if(palette->blending) pitch = 4;
	//�萔�F�T�C�Y
	int size = bitmap->size;
	//�萔�F�u�����f�B���O
	int blending = palette->blending;
	//�萔�F�F��
	int color_max = palette->num;
	//�ҏW�������m��
	SDL_LockSurface(temp);
	//�|�C���^�̐ݒ�
	char* pt = temp->pixels;
	PGL_BIT* bit = bitmap->bit;
	PGL_COLOR* pl_color = palette->color;
	//�f�[�^�̐���
	int i=0;
	for(;i<size;i++){
		int color = bit->color;
		switch(bit->type){
			//�p���b�g�����g��
			case BIT_TYPE_COLOR:
			{
				if(color < color_max){
					PGL_COLOR* c= &pl_color[color];
					*(pt+0) = c->r;
					*(pt+1) = c->g;
					*(pt+2) = c->b;
					if(blending)	*(pt+3) = c->a;
				}else{
					*(pt+0) = 0x00;
					*(pt+1) = 0x00;
					*(pt+2) = 0x00;
					if(blending)	*(pt+3) = 0xff;
				}
				break;
			}
			//�������͕ʈ���
			case BIT_TYPE_BLACK:
				*(pt+0) = color;
				*(pt+1) = color;
				*(pt+2) = color;
				if(blending)	*(pt+3) = 0xff;
		}
		pt += pitch;
		bit++;
	}
	//�T�[�t�F�C�X�̃A�����b�N
	SDL_UnlockSurface(temp);
	//�X�v���C�g�̐���
	getSpriteFromSurface(sprite,temp,palette->blending,FALSE);
}
//�r�b�g�}�b�v�̐���
PGL_BITMAP* getBitmapFromOps(SDL_RWops* data){
	PGL_BITMAP* bitmap = malloc(sizeof(*bitmap));
	//�w�b�_���΂�
	SDL_RWseek(data,strlen(BITMAP_DATA_HEADER),SEEK_SET);
	//�T�C�Y�擾
	SDL_RWread(data,&bitmap->w,sizeof(bitmap->w),1);
	SDL_RWread(data,&bitmap->h,sizeof(bitmap->h),1);
	int size = bitmap->w * bitmap->h;
	bitmap->size = size;
	//�r�b�g�p�f�[�^�擾
	PGL_BIT* bit = malloc(size * sizeof(*bit));
	bitmap->bit = bit;
	int i=0;
	for(;i<size;i++){
		SDL_RWread(data,&bit[i],sizeof(*bit),1);
	}
	//ops�폜
	SDL_RWclose(data);
	return bitmap;
}
PGL_BITMAP* getBitmapFromArchive(ARCHIVE* archive,const char* filename){
	return getBitmapFromOps(getFile(archive,filename));
}
void deleteBitmap(PGL_BITMAP* bitmap){
	free(bitmap->bit);
	free(bitmap);
}
//�p���b�g�̐���
PGL_PALETTE* getPaletteFromOps(SDL_RWops* data){
	PGL_PALETTE* palette = malloc(sizeof(palette));
	return palette;
}
PGL_PALETTE* getPaletteFromMem(int blending,unsigned char num,const unsigned int *color){
	PGL_PALETTE* palette = malloc(sizeof(palette));
	return palette;
}
void deletePalette(PGL_PALETTE* palette){
	free(palette->color);
	free(palette);
}

