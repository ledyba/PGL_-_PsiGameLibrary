#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <stdio.h> 
#include <windows.h>

#include "../include/data/data.h"
#include "../include/basic/type_define.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/basic/point.h"
#include "../include/system/screen.h"
#include "../include/basic/load.h"
	static void (*SceneChangeFunc)(int);
	static int LoadingModeNum;
	static LOADER* NowLoader;
	/*ロード画面の背景スプライト*/
	static SPRITE LoadBGSprite;
	static SPRITE_AREA LoadBGSpriteArea;
void initLoaderSystem(void (*scene_change_func)(int),int loading_mode_num){
	/*関数設定*/
	SceneChangeFunc = scene_change_func;
	LoadingModeNum = loading_mode_num;
	/*ファイルオープン*/
	ARCHIVE archive;
	openArchive(&archive,LOAD_ARCHIVE);
	/*背景取得*/
	getSpriteFromArchive(&LoadBGSprite,&archive,LOAD_BG,FALSE,TRUE);
	makeDefaultSpriteArea(&LoadBGSpriteArea,&LoadBGSprite);
	closeArchive(&archive);
	
}
/*ロード画面の準備・終了*/
LOADER* makeLoader(int funcs,char* filename,void (*init_func)(),void (*finish_func)(),LOAD_FUNCS* load_funcs, int next_mode, int close_at_end){
	LOADER* loader;
	loader = malloc(sizeof(*loader));
	loader->index = 0;
	/*アーカイブを開く*/
	if(filename != NULL){
		openArchive(&loader->archive,filename);
		loader->close_at_end = close_at_end;
	}
	/*ロード用関数*/
	loader->func_num = funcs;
	loader->funcs = load_funcs;
	/*終わったあとのモード*/
	loader->next_mode = next_mode;
	//最初の関数読み込み
//	loader->init_func = init_func;
	if(init_func != NULL)	init_func();
	//最後の関数
	loader->finish_func = finish_func;
	return loader;
}
void quitLoaderSystem(){
	/*テクスチャの削除*/
	deleteSprite(&LoadBGSprite);
}
void closeLoader(LOADER* loader){
	if(loader->close_at_end == TRUE){
		closeArchive(&NowLoader->archive);
	}
	int i=0;
	int max = loader->func_num;
	for(;i<max;i++){
		loader->funcs[i].quit();
	}
	free(loader);
}
int setLoader(LOADER* loader){
	if(NowLoader == NULL){
		NowLoader = loader;

		//これだけは実行しておく。
		NowLoader->funcs[0].init();
		/*場面切り替え*/
		if(SceneChangeFunc != NULL){
			SceneChangeFunc(LoadingModeNum);
		}
		/*一回だけ描画*/
		drawLoader();
		SDL_GL_SwapBuffers();

		return TRUE;
	}
	return FALSE;
}
/*動かす*/
void moveLoader(long next_tick){
	int isLoadFinished = NowLoader->funcs[NowLoader->index].load(next_tick,&NowLoader->archive);
	if(isLoadFinished == TRUE){
		NowLoader->funcs[NowLoader->index].finish();
		NowLoader->index++;
		if(NowLoader->index >= NowLoader->func_num){
			/*最後の関数の実行*/
			if(NowLoader->finish_func != NULL)	NowLoader->finish_func();
			/*アーカイブを閉じる*/
			if(NowLoader->close_at_end == FALSE){
				closeArchive(&NowLoader->archive);
			}
			/*ロードが終わったらシーンを変える*/
			if(SceneChangeFunc != NULL){
				SceneChangeFunc(NowLoader->next_mode);
			}
			NowLoader = NULL;
		}else{
			NowLoader->funcs[NowLoader->index].init();
		}
	}
}
/*描写する*/
void drawLoader(){
	drawSpriteArea(getBG_Area(),&LoadBGSpriteArea,0.0f);
}

