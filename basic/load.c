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
	/*���[�h��ʂ̔w�i�X�v���C�g*/
	static SPRITE LoadBGSprite;
	static SPRITE_AREA LoadBGSpriteArea;
void initLoaderSystem(void (*scene_change_func)(int),int loading_mode_num){
	/*�֐��ݒ�*/
	SceneChangeFunc = scene_change_func;
	LoadingModeNum = loading_mode_num;
	/*�t�@�C���I�[�v��*/
	ARCHIVE archive;
	openArchive(&archive,LOAD_ARCHIVE);
	/*�w�i�擾*/
	getSpriteFromArchive(&LoadBGSprite,&archive,LOAD_BG,FALSE,TRUE);
	makeDefaultSpriteArea(&LoadBGSpriteArea,&LoadBGSprite);
	closeArchive(&archive);
	
}
/*���[�h��ʂ̏����E�I��*/
LOADER* makeLoader(int funcs,char* filename,void (*init_func)(),void (*finish_func)(),LOAD_FUNCS* load_funcs, int next_mode, int close_at_end){
	LOADER* loader;
	loader = malloc(sizeof(*loader));
	loader->index = 0;
	/*�A�[�J�C�u���J��*/
	if(filename != NULL){
		openArchive(&loader->archive,filename);
		loader->close_at_end = close_at_end;
	}
	/*���[�h�p�֐�*/
	loader->func_num = funcs;
	loader->funcs = load_funcs;
	/*�I��������Ƃ̃��[�h*/
	loader->next_mode = next_mode;
	//�ŏ��̊֐��ǂݍ���
//	loader->init_func = init_func;
	if(init_func != NULL)	init_func();
	//�Ō�̊֐�
	loader->finish_func = finish_func;
	return loader;
}
void quitLoaderSystem(){
	/*�e�N�X�`���̍폜*/
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

		//���ꂾ���͎��s���Ă����B
		NowLoader->funcs[0].init();
		/*��ʐ؂�ւ�*/
		if(SceneChangeFunc != NULL){
			SceneChangeFunc(LoadingModeNum);
		}
		/*��񂾂��`��*/
		drawLoader();
		SDL_GL_SwapBuffers();

		return TRUE;
	}
	return FALSE;
}
/*������*/
void moveLoader(long next_tick){
	int isLoadFinished = NowLoader->funcs[NowLoader->index].load(next_tick,&NowLoader->archive);
	if(isLoadFinished == TRUE){
		NowLoader->funcs[NowLoader->index].finish();
		NowLoader->index++;
		if(NowLoader->index >= NowLoader->func_num){
			/*�Ō�̊֐��̎��s*/
			if(NowLoader->finish_func != NULL)	NowLoader->finish_func();
			/*�A�[�J�C�u�����*/
			if(NowLoader->close_at_end == FALSE){
				closeArchive(&NowLoader->archive);
			}
			/*���[�h���I�������V�[����ς���*/
			if(SceneChangeFunc != NULL){
				SceneChangeFunc(NowLoader->next_mode);
			}
			NowLoader = NULL;
		}else{
			NowLoader->funcs[NowLoader->index].init();
		}
	}
}
/*�`�ʂ���*/
void drawLoader(){
	drawSpriteArea(getBG_Area(),&LoadBGSpriteArea,0.0f);
}

