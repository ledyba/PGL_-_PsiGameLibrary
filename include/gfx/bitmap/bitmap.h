#ifndef BITMAP_H_
#define BITMAP_H_

#define BIT_TYPE_COLOR	0x01
#define BIT_TYPE_BLACK	0x02

#define  BITMAP_DATA_HEADER "PGL BITMAP"
#define PALETTE_DATA_HEADER "PGL PALETTE"

typedef struct {
	unsigned char type;	//タイプ
	unsigned char color;	//色
}PGL_BIT;

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}PGL_COLOR;

typedef struct {
	int blending;			//アルファブレンディングを用いる場合には使用すること
	unsigned char num;		//個数
	PGL_COLOR *color;	//色の配列
}PGL_PALETTE;

typedef struct {
	int w;			//横
	int h;			//高さ
	int size;		//横×高さ
	PGL_BIT* bit;		//ビット数
}PGL_BITMAP;

//スプライトの作成
void getSpriteFromBitmap(SPRITE* sprite,const PGL_BITMAP* bitmap,const PGL_PALETTE* palette);
//ビットマップの生成
PGL_BITMAP* getBitmapFromOps(SDL_RWops* data);
PGL_BITMAP* getBitmapFromArchive(ARCHIVE* archive,const char* filename);
void deleteBitmap(PGL_BITMAP* bitmap);
//パレットの生成
PGL_PALETTE* getPaletteFromOps(SDL_RWops* data);
PGL_PALETTE* getPaletteFromMem(int blending,unsigned char num,const unsigned int *color);
void deletePalette(PGL_PALETTE* palette);

#endif
