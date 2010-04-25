#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <SDL.h>
#include <SDL_rwops.h>
#include "../include/basic/type_define.h"
#include "../include/system/error_system.h"
#include "../include/system/screen.h"
#include "../include/basic/point.h"
#include "../include/data/data.h"
#include "../include/basic/load.h"
#include "../include/gfx/sprite.h"
#include "../include/system/system.h"

void initPGL_Video2D(
	void (*quit)(),
	int WindowMode,
	char* window_title,
	void (*scene_change_func)(int),
	int loading_mode_num
){
	initErrorSystem(quit);
	if(!initSDL_2D(WindowMode,window_title)){
		raiseError("failed to prepare SDL libs.","\n");
	}
	initPoint();				//座標変換ライブラリ
	initLoaderSystem(scene_change_func,loading_mode_num);	//ロードライブラリ
	initSpriteSystem();	//スプライトシステム
}

void quitPGL_Video2D(){
	quitSDL_2D();
}
