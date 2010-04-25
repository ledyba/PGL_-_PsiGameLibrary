/*リソース定義ファイルの読み込み*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/basic/type_define.h"
#include "../include/system/error_system.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/animation.h"
#include "../include/data/resource_define.h"
/**
 * リソースデータを返す。
 */
void loadResourceDefine(RESOURCE_LIST* list,SDL_RWops* buffer){
	//先頭の文字列を飛ばす。
	SDL_RWseek(buffer,(long)strlen(RESOURCE_DEFINE_HEADER),SEEK_SET);
	//ファイルモード読み込み
	SDL_RWread(buffer,&list->mode,sizeof(list->mode),1);
	//最大ファイル数とかを読み込み。
	int max_file = 0;
	switch(list->mode){
		case RESOURCE_MODE_GRAHIC:
//			max_file = GRAPHIC_MAX;
			break;
		case RESOURCE_MODE_MOTION:
			break;
	}
	//ファイル数読み込み
	int file_num,i;
	SDL_RWread(buffer,&file_num,sizeof(file_num),1);
	list->file_num = file_num;
	if(file_num >= max_file)	raiseError("file reading error in loadResourceDefine.\n","->resource num is invalid.");
	//ファイル名読み込みのためのメモリ確保。
	list->item = malloc(sizeof(RESOURCE_LIST_ITEM) * file_num);
	for(i=0;i<file_num;i++){
		RESOURCE_LIST_ITEM* item = &list->item[i];
		//ID読み込み
		SDL_RWread(buffer,&item->num,sizeof(item->num),1);
		if(item->num >= max_file)	raiseError("file reading error in loadResourceDefine.\n","->item id is invalid.");
		//ファイル名読み込み
		int length;
		SDL_RWread(buffer,&length,sizeof(length),1);
		item->filename = malloc(length + 1);
		SDL_RWread(buffer,item->filename,length,1);
		//終端コード
		item->filename[length] = '\0';
	}
}
/**
 * 作成したリストを、破棄する。
 */
void closeResourceDefine(RESOURCE_LIST* list){
	int i=0,max=list->file_num;
	for(;i<max;i++){
		free(list->item[i].filename);
	}
	free(list->item);
}

