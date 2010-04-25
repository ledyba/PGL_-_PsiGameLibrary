#ifndef LOAD_H_
#define LOAD_H_
/*ロード画面の管理を行う*/

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

/*ロードの準備*/
void initLoaderSystem(void (*scene_change_func)(int),int loading_mode_num);
void quitLoaderSystem();
/*ロード画面の準備・終了*/
LOADER* makeLoader(int funcs,char* filename,void (*init_func)(),void (*finish_func)(),LOAD_FUNCS* load_funcs, int next_mode, int close_at_end);
int setLoader(LOADER* loader);
void startLoader(LOADER* loader);
void closeLoader(LOADER* loader);
/*動かす*/
void moveLoader(long next_tick);
/*描写する*/
void drawLoader();

#endif 
