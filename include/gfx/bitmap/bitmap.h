#ifndef BITMAP_H_
#define BITMAP_H_

#define BIT_TYPE_COLOR	0x01
#define BIT_TYPE_BLACK	0x02

#define  BITMAP_DATA_HEADER "PGL BITMAP"
#define PALETTE_DATA_HEADER "PGL PALETTE"

typedef struct {
	unsigned char type;	//�^�C�v
	unsigned char color;	//�F
}PGL_BIT;

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}PGL_COLOR;

typedef struct {
	int blending;			//�A���t�@�u�����f�B���O��p����ꍇ�ɂ͎g�p���邱��
	unsigned char num;		//��
	PGL_COLOR *color;	//�F�̔z��
}PGL_PALETTE;

typedef struct {
	int w;			//��
	int h;			//����
	int size;		//���~����
	PGL_BIT* bit;		//�r�b�g��
}PGL_BITMAP;

//�X�v���C�g�̍쐬
void getSpriteFromBitmap(SPRITE* sprite,const PGL_BITMAP* bitmap,const PGL_PALETTE* palette);
//�r�b�g�}�b�v�̐���
PGL_BITMAP* getBitmapFromOps(SDL_RWops* data);
PGL_BITMAP* getBitmapFromArchive(ARCHIVE* archive,const char* filename);
void deleteBitmap(PGL_BITMAP* bitmap);
//�p���b�g�̐���
PGL_PALETTE* getPaletteFromOps(SDL_RWops* data);
PGL_PALETTE* getPaletteFromMem(int blending,unsigned char num,const unsigned int *color);
void deletePalette(PGL_PALETTE* palette);

#endif
