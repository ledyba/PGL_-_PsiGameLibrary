#include <stdio.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_rwops.h>
#include "../include/system/error_system.h"
#include "../include/data/PGL_SDL_RWops.h"
#include "../include/data/data.h"

/*アーカイバ*/

/* アーカイブファイルを展開する
 * arc	:アーカイブファイルの展開先
 * file	:アーカイブファイル
 * */
 const static ARCHIVE_HEADER_ITEM tmpItem;
int openArchive(ARCHIVE* arc,const char *filename){
	FILE* file = arc->file = fopen(filename, "rb");
	if(file == NULL){
		raiseError("failed to prepare Archive:",filename);
		return FALSE;
	}
	/*ArchiveHeaderの読み込み*/
	
	//"ARCHIVE"を飛ばす
	fseek(file,strlen(ARCHIVE_TITLE),SEEK_SET);
	//ファイル数の取得
	fread(&arc->fileNum, sizeof(arc->fileNum) ,1, file);
	//メモリ確保
	arc->item = malloc((arc->fileNum) * sizeof(tmpItem));

	/*ArchiveHeaderItemの読み込み*/
	ARCHIVE_HEADER_ITEM* it = arc->item;
	int i=0,fileNum = arc->fileNum,check;
	for(;i<fileNum;i++){
		check = 0;
		//文字数取得
		check += fread(&it->fileNameSize, sizeof(it->fileNameSize) ,1, file);
		//文字取得
		it->fileName = malloc(it->fileNameSize+1);
		check += fread(it->fileName, it->fileNameSize ,1, file); 
		//最後を0で閉めてちゃんと終端処理！
		it->fileName[it->fileNameSize] = '\0';
		//オフセット、サイズ。
		check += fread(&it->offset, sizeof(it->offset) ,1, file);
		check += fread(&it->size, sizeof(it->size) ,1, file);
		it++;
		if(check != 4){
			closeArchive(arc);
			raiseError("failed to get Header in Archive:",filename);
		}
	}
	return TRUE;
}
/* 
 * arc		:アーカイぶファイル
 * filename	:ファイル名
 * */
SDL_RWops* getFile(ARCHIVE* arc, const char* filename){
//	fprintf(stdout,"searching:%s	,",filename);
//	fprintf(stdout,"size:%d	,",arc->fileNum);
	ARCHIVE_HEADER_ITEM* it = arc->item;
	int i,file_num = arc->fileNum,check = FALSE;
	for(i=0;i<file_num;i++){
		//一致すれば出る
//		fprintf(stdout,"file:%s	,search:%s\n",filename,it->fileName);

		char* file_name = it->fileName;
		if(strcmp(file_name,filename) == 0){
			check = TRUE;
			break;
		}
		it++;
	}
	/*ファイルが見つからなかった*/
	if(check == FALSE){
		closeArchive(arc);
		raiseError("file not found:",filename);
	}
	void* data = malloc(it->size);
	fseek(arc->file,it->offset,SEEK_SET);
	fread(data, it->size, 1, arc->file);
	SDL_RWops* buf = PGL_SDL_RWFromMem(data, it->size);
	/*
	static int once = 4;
	if(once == 0){
		SDL_RWops* ops = SDL_RWFromFile("i.png","w");
		SDL_RWwrite(ops,data,it->size,1);
		SDL_RWclose(ops);
	}
	once--;
	*/
	return buf;
}

/* アーカイブファイルを閉じる
 * arc	:アーカイブファイル
 */
int closeArchive(ARCHIVE* arc){
	/*ともかく、メモリ開放！*/
	//まずは、文字
	ARCHIVE_HEADER_ITEM* it = arc->item;
	int i,num = arc->fileNum;
	for(i=0;i<num;i++){
		free(it->fileName);
		it++;
	}
	//そして、アイテムリスト全体
	free(arc->item);
	//ファイルを閉じる
	fclose(arc->file);
	return TRUE;
}
