#ifndef SYSTEM_H_
#define SYSTEM_H_
void initPGL_Video2D(
	void (*quit)(),
	int WindowMode,
	char* window_title,
	void (*scene_change_func)(int),
	int loading_mode_num
);
void quitPGL_Video2D();

#endif
