#ifndef LOAD_H_
#define LOAD_H_
/*���[�h��ʂ̊Ǘ����s��*/

#define LOAD_ARCHIVE "load.arc"
#define LOAD_BG "LoadBG.png"

 typedef struct{
 	void (*init)();
 	int (*load)(long,ARCHIVE*);
 	int (*finish)();
 	void (*quit)();
 }LOAD_FUNCS;

typedef struct{
	int close_at_end;
	ARCHIVE archive;
//	void (*init_func)();
	void (*finish_func)();
	int index;
	int next_mode;
	int func_num;
	LOAD_FUNCS* funcs;
}LOADER; 

/*���[�h�̏���*/
void initLoaderSystem(void (*scene_change_func)(int),int loading_mode_num);
void quitLoaderSystem();
/*���[�h��ʂ̏����E�I��*/
LOADER* makeLoader(int funcs,char* filename,void (*init_func)(),void (*finish_func)(),LOAD_FUNCS* load_funcs, int next_mode, int close_at_end);
int setLoader(LOADER* loader);
void startLoader(LOADER* loader);
void closeLoader(LOADER* loader);
/*������*/
void moveLoader(long next_tick);
/*�`�ʂ���*/
void drawLoader();

#endif 
