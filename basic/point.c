#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>
#include <math.h>

#include "../include/basic/type_define.h"
#include "../include/basic/point.h"
#include "../include/system/screen.h"

/*三角関数*/
static uint rsin[360];
static uint rcos[360];
/*角度を求めるためのアークタンジェント*/
static float racos[BIT_POINT<<1];

void initPoint(){
	/*三角関数を前のうちに計算しておいたりとか*/
	int i;
	for(i=0;i<360;i++){
		rsin[i] = (uint)(sin(M_PI*i/180)*BIT_POINT);
		rcos[i] = (uint)(cos(M_PI*i/180)*BIT_POINT);
	}
	
	/*アークタンジェント計算*/
	for(i=0;i<BIT_POINT<<1;i++){
		racos[i]=(float)(acos( ((float)i-BIT_POINT) / BIT_POINT) ) * 180 / M_PI;
	}
	
}
/*四角形で当たり判定
 * 誘爆の時は範囲が拡大する*/
int isHitSquare(const Point* a,const Point* b,uint overplus){
	uint a_width = a->width + overplus;
	uint a_height = a->height + overplus;
	return (a->x + a_width > b->x - b->width) && (b->x + b->width > a->x - a_width )
	&& (a->y + a_height > b->y - b->height) && (b->y + b->height > a->y - a_height );
}
/*ゲームスペース内にいるか*/
int isInGameSpace(const Point* a,int overplus){
return  a->x >= ((-overplus) << BIT) && 
		 a->x <= ((GAME_SCREEN_WIDTH + overplus) << BIT) && 
		 a->y >= ((-overplus) << BIT) && 
		 a->y <= ((GAME_SCREEN_HEIGHT + overplus) << BIT);
}
/*距離の自乗を得る*/
/*実際の距離が返ります・・・*/
uint getDistance2(uint dx,uint dy){
	unsigned long x = abs(dx);
	unsigned long y = abs(dy);
	x *= (x >> BIT);
	y *= (y >> BIT);
	uint res = (uint)((x + y) >> BIT);
	return res;
}
/*
 * 実際に描写されるポイントの取得
 */
void getPaintedPoint(glPoint *out,const Point *pt){
	out->x 		= (float)(pt->x)/BIT_POINT;
	out->y 		= (float)(pt->y)/BIT_POINT;
	out->width  = (float)(pt->width / BIT_POINT);
	out->height	= (float)(pt->height / BIT_POINT);
}
/*平方根*/
uint sqrti(uint d){
	return (uint)(sqrt(d));
}

void getVector(Vector* out,const Point* a,const Point* b,uint speed){
	uint x = (b->x)-(a->x);
	uint y = (b->y)-(a->y);
	uint dis = sqrti(getDistance2(x,y)) << BIT;
	if(speed != 0){
		out->speed = speed;
		out->x = (x * speed) / dis;
		out->y = (y * speed) / dis;
	}else{
		/*距離が0の場合は、下に飛ばす*/
		out->speed = speed;
		out->x = 0;
		out->y = speed;
	}
}

void changeVectorSpeed(Vector* vec,uint speed){
	/*計算されていない*/
	if(vec->speed == 0)	vec->speed = sqrti(getDistance2(vec->x,vec->y)) << BIT;
	/*本当に0ならば*/
	if(vec->speed == 0){
		vec->x = 0;
		vec->y = 0;
		vec->speed = 0;
	}else{
		vec->x = (vec->x * speed) / vec->speed;
		vec->y = (vec->y * speed) / vec->speed;
		vec->speed = speed;
	}
}

/*ヴェクトルの回転*/
void rotateVector(Vector* vec,uint theta){
	uint sin = usin(theta);
	uint cos = ucos(theta);
	uint x = (cos*vec->x) - (sin*vec->y);
	uint y = (sin*vec->x) + (cos*vec->y);
	vec->x = x>>BIT;
	vec->y = y>>BIT;
}
/*三角関数*/
uint usin(uint theta){
	if(theta < 0)
		return -rsin[-theta % 360];
	else
		return rsin[theta % 360];
}

uint ucos(uint theta){
	if(theta < 0)
		return rcos[-theta % 360];
	else
		return rcos[theta % 360];
}
float getTheta(const Vector* vec){
	return (float)((atan2((float)(vec->y),(float)vec->x)) * 180 / M_PI)+90.0f;
}
/*描画ポイントを設定する。以下の描画ポイントはこれが元になる*/
void setDrawnPoint(const glPoint* point){
	GLfloat w = point->width*2;
	GLfloat h = point->height*2;
	GLfloat z = h ? w : w > h;
	//ビューポート設定
	glViewport(point->x-point->width, point->y-point->height, w, h);
	/* 変換行列の初期化 */
	glLoadIdentity();
	/* スクリーン上の表示領域をビューポートの大きさに比例させる */
	glOrtho( 0, w, h, 0, -z, z);
/*
	glFrustum( 0, w, h, 0, z, z*3);
	glTranslatef(0.0f, 0.0f, -z*2);
	glScalef(2.0f,2.0f, 1.0f);
*/
}
 
