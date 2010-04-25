#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/basic/type_define.h"
#include "../include/system/error_system.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/animation.h"

/**
 * アニメーションを読み込む
 */
void loadAnimation(ANIME_SET* graphic,ARCHIVE* archive,const char* file_name){
	SDL_RWops* gfx_file = getFile(archive,file_name);
	//ヘッダを飛ばす。
	SDL_RWseek(gfx_file,(long)strlen(ANIME_HEADER),SEEK_SET);
	//ファイル名取得
	int filename_size;
	SDL_RWread(gfx_file,&filename_size,sizeof(filename_size),1);
	graphic->filename_size = filename_size;
	graphic->filename = malloc(filename_size+1);
	SDL_RWread(gfx_file,graphic->filename,filename_size,1);
	graphic->filename[filename_size] = '\0';
	//モード、フラグ、アニメ数、アルファブレンディング
	SDL_RWread(gfx_file,&graphic->mode,sizeof(graphic->mode),1);
	SDL_RWread(gfx_file,&graphic->flag,sizeof(graphic->flag),1);
	SDL_RWread(gfx_file,&graphic->anime_num,sizeof(graphic->anime_num),1);
	SDL_RWread(gfx_file,&graphic->is_alpha_blending,sizeof(graphic->is_alpha_blending),1);
	//スプライト取得
	getSpriteFromArchive(&graphic->sprite,archive,graphic->filename,graphic->is_alpha_blending,TRUE);
	//スプライトエリア用スプライト
	SPRITE* anime_sprite = &graphic->sprite;
	int anime_num = graphic->anime_num;
	graphic->anime = malloc( sizeof(ANIMATION*) * anime_num );
	int i=0;
	for(;i<anime_num;i++){
		//アニメ番号
		int num = 0;
		SDL_RWread(gfx_file,&num,sizeof(num),1);
		if(anime_num < num) raiseError("invalid animation file:",file_name);
		//メモリ確保。
		graphic->anime[num] = malloc(sizeof(ANIMATION));
		ANIMATION* anime = graphic->anime[num];
		anime->num = num;
		//フレーム番号取得
		int frame_num;
		SDL_RWread(gfx_file,&frame_num,sizeof(frame_num),1);
		anime->frame_num = frame_num;
		anime->frame = malloc(sizeof(ANIMATION_FRAME)*frame_num);
		int j;
		for(j=0;i<frame_num;j++){
			//フレームへのポインタの設定
			ANIMATION_FRAME* frame = &anime->frame[j];
			//持続時間
			SDL_RWread(gfx_file,&frame->frame_time,sizeof(frame->frame_time),1);
			//スプライトの設定
			int x,y,w,h;
			SDL_RWread(gfx_file,&x,sizeof(x),1);
			SDL_RWread(gfx_file,&y,sizeof(y),1);
			SDL_RWread(gfx_file,&w,sizeof(w),1);
			SDL_RWread(gfx_file,&h,sizeof(h),1);
			makeSpriteArea(&frame->sprite_area,anime_sprite,x,y,w,h);
		}
	}
	SDL_RWclose(gfx_file);
}
/**
 * メモリを開放する。
 */
void deleteAnimation(ANIME_SET* graphic){
	int i=0,anime_num = graphic->anime_num;
	for(;i<anime_num;i++){
		ANIMATION* anime = graphic->anime[i];
		free(anime->frame);
		free(anime);
	}
	free(graphic->anime);
	deleteSprite(&graphic->sprite);
	free(graphic->filename);
	free(graphic);
}
/**
 * アニメーションを描画する。
 */
void drawAnimation(ANIME_RECORD* record,const glPoint* point){
	ANIMATION* anime = record->graphic->anime[record->anime];
	SPRITE_AREA* sprite_area = &anime->frame[record->frame].sprite_area;
	drawSpriteArea(point,sprite_area,record->angle);
	int* frame_left = &record->frame_left;
	*frame_left--;
	if(!(*frame_left > 0)){
		int* frame = &record->frame;
		*frame++;
		*frame %= anime->frame_num;
		*frame_left = anime->frame[*frame].frame_time;
	}
}
int changeAnimation(ANIME_RECORD* record,int anime){
	if(record->graphic->anime_num >= anime){
		return FALSE;
	}
	record->anime = anime;
	record->frame = 0;
	record->frame_left = record->graphic->anime[anime]->frame[0].frame_time;
	return TRUE;
}
int changeAnimeAngle(ANIME_RECORD* record,float angle){
	if((record->graphic->flag & ANIME_FLAG_RORATE) != 0){
		record->angle = angle;
		return TRUE;
	}else{
		return FALSE;
	}
}
