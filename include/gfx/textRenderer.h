#ifndef TEXT_RENDERER_H_
#define TEXT_RENDERER_H_
/**
 * テキストを描画して、スプライトに変換します。
 * 流れは、
 * SDL_ttfでサーフェイスを作成→スプライトに使える形式に変換
 * →スプライト（テクスチャ）化
 * テクスチャは基本的に一枚を使いまわし
 */
 
 /**
  * 初期化します。
  */
int initTextRenderer(SDL_RWops *src,int default_fontsize);
/**
 * 終了します。
 */
void quitTextRenderer();
/*ドロー関数*/
void drawText(const glPoint* point,const char* text);
/*スプライト操作関数*/
void updateTextSprite(SPRITE* sprite,const char* text);
void makeTextSprite(SPRITE* sprite,const char* text);
#endif
