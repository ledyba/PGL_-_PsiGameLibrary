#ifndef SCREEN_H_
#define SCRREN_H_
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP    32

#define GAME_FRAME_RATE 60

int initSDL_2D(int window_mode,char* window_title);
int quitSDL_2D();
void drawBlackBackground();
void drawSideBar();
void drawSelectCursor(const glPoint* point,GLfloat  size,const GLfloat* color,int isRight);
void drawBox(const glPoint* point,int isFilled,float width,const GLfloat* color);
void drawCircle(const glPoint* point,GLfloat radius,const GLfloat* color,float width,int isFilled);
const glPoint* getBG_Area();

#endif
