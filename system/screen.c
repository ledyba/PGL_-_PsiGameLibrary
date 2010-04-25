#include <SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>

#include "../include/basic/type_define.h"
#include "../include/system/error_system.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/basic/point.h"
#include "../include/system/screen.h"

/*背景描写用ポイント*/
static glPoint BG_AREA;


int initSDL_2D(int window_mode,char* window_title){
    /* 初期化 */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)<0) {
        raiseError("failed to initialize SDL.","\n");
        return 0;
    }

	/*OpenGL関連*/
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );//ダブルバッファ
	SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 1 );//VSync
	SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );//ハードウェア
	// キャプションの設定
	SDL_WM_SetCaption( window_title , NULL );
	
	int VideoFlag = SDL_OPENGL;//SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_OPENGL;
	if(window_mode) VideoFlag |= SDL_FULLSCREEN;

	// ウィンドウの初期化
	SDL_SetVideoMode(
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SCREEN_BPP,
		VideoFlag
		);

	/*背景の場所の定義*/
	BG_AREA.x = 		SCREEN_WIDTH>>1;
	BG_AREA.y = 		SCREEN_HEIGHT>>1;
	BG_AREA.width  = 	SCREEN_WIDTH>>1;
	BG_AREA.height = 	SCREEN_HEIGHT>>1;

	// マウスカーソルを消す場合は
	//SDL_ShowCursor(SDL_DISABLE);
	glDisable(GL_DEPTH_TEST);
	/*
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	*/
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);

	/*座標系の変換*/
	glMatrixMode(GL_PROJECTION);
	setDrawnPoint(getBG_Area());

	//バッファを初期化する色を設定。：黒
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//初期化しておきます。
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();

    /* 終了 */
    return 1;
}
int quitSDL_2D(){
    SDL_Quit();
    return 1;
}
/**
 * 背景を黒く塗りつぶします．
 * 
 */
void drawBlackBackground(){
	glClear(GL_COLOR_BUFFER_BIT);
}
/**
 * カーソルを描画します
 * 
 */
const static GLfloat DEFAULT_CURSOR_COLOR[4]= {0.0f,0.0f,0.0f,1.0f};
void drawSelectCursor(const glPoint* point,GLfloat  size,const GLfloat* color,int isRight){
	size /= 2;
	GLfloat x = point->x;
	GLfloat y = point->y;
	GLfloat h = size;
	GLfloat w = size * 0.86602540378443864676372317075294f;
	GLfloat vertex[6];
	int is_blend = (color[3] != 1.0);
	if(is_blend){
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}else{
		glDisable( GL_BLEND );
	}

	if(isRight){
		vertex[0] = x-w;	vertex[1] = y-h;
		vertex[2] = x-w;	vertex[3] = y+h;
		vertex[4] = x+w;	vertex[5] = y;
	}else{
		vertex[0] = x+w;	vertex[1] = y-h;
		vertex[2] = x+w;	vertex[3] = y+h;
		vertex[4] = x-w;	vertex[5] = y;
	}

	glEnableClientState( GL_VERTEX_ARRAY );
	glColor4fv(color != NULL ? color : DEFAULT_CURSOR_COLOR);
	glVertexPointer( 2, GL_FLOAT, 0, vertex );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 3 );

	if(is_blend){
		glDisable( GL_BLEND );
	}
}
/**
 * 四角形を描画します。
 * 
 */
void drawBox(const glPoint* point,int isFilled,float width,const GLfloat* color){
	GLfloat x = point->x;
	GLfloat y = point->y;
	GLfloat w = point->width;
	GLfloat h = point->height;
	/*ブレンド設定*/
	int is_blend = (color[3] != 1.0);
	if(is_blend){
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}else{
		glDisable( GL_BLEND );
	}
	GLfloat vertex[8] = {
		x+w,y-h,
		x+w,y+h,
		x-w,y+h,
		x-w,y-h,
	};
	glEnableClientState( GL_VERTEX_ARRAY );
	glColor4fv(color);
	glLineWidth(width);
	glVertexPointer( 2, GL_FLOAT, 0, vertex );
	glDrawArrays(isFilled ? GL_TRIANGLE_FAN : GL_LINE_LOOP, 0, 4 );

	if(is_blend){
		glDisable( GL_BLEND );
	}
}

void drawCircle(const glPoint* point,GLfloat radius,const GLfloat* color,float width,int isFilled){
	/*座標設定*/
	glPushMatrix();
	glTranslatef(point->x,point->y,0.0);
	/*太さ設定*/
	glLineWidth(width);
	/*ブレンド設定*/
	int is_blend = (color[3] != 1.0);
	if(is_blend){
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}else{
		glDisable( GL_BLEND );
	}
	/*カラー設定*/
	glColor4fv(color);
	/*頂点設定*/
	GLfloat vertex[724];
	int idx;
	if(isFilled){
		vertex[0] = vertex[1] = 0.0f;
		vertex[722] = radius;
		vertex[723] = 0.0f;
		idx = 1;
	}else{
		idx = 0;
	}
	int i=0;
	int arr_idx = 0;
	for(;i<360;i++){
		arr_idx = (idx+i)<<1;
		vertex[arr_idx] = (radius*ucos(i)) / BIT_POINT;
		vertex[arr_idx+1] = (radius*usin(i)) / BIT_POINT;
	}
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 2, GL_FLOAT, 0, vertex );

	if(isFilled){
		glDrawArrays( GL_TRIANGLE_FAN, 0, 362 );
	}else{
		glDrawArrays( GL_LINE_LOOP, 0, 360 );
	}
	if(is_blend){
		glDisable( GL_BLEND );
	}
	glPopMatrix();
}

const glPoint* getBG_Area(){
	return &BG_AREA;
}
