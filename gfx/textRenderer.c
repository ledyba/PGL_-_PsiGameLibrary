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
 * テキストを描画して、スプライトに変換します。
 * 流れは、
 * SDL_ttfでサーフェイスを作成→スプライトに使える形式に変換
 * →スプライト（テクスチャ）化
 * テクスチャは基本的に一枚を使いまわし
 */
 
 static TTF_Font* Font;			//フォント格納
 static SPRITE RenderingSprite;	//レンダリング用。他のスプライトに書くこともできる。
 /**
  * 初期化します。
  */
int initTextRenderer(SDL_RWops *src,int default_fontsize){
	Font = TTF_OpenFontRW(src,1,default_fontsize);
	//十分に大きな領域を確保
	makeEmptySprite(&RenderingSprite,default_fontsize<<3,default_fontsize<<4,TRUE,TRUE);
	if(Font != NULL) return TRUE;
	return FALSE;
}
/**
 * 終了します。
 */
void quitTextRenderer(){
	TTF_CloseFont(Font);
	Font = NULL;
}
//RenderingSpriteを使って描画
void drawText(const glPoint* point,const char* text){
}
//指定されたスプライトに描画、新規作成
void updateTextSprite(SPRITE* sprite,const char* text){
}
//指定されたスプライトに描画、アップデート
void makeTextSprite(SPRITE* sprite,const char* text){
}
