#ifndef TYPE_DEFINE_H_
#define TYPE_DEFINE_H_
/*フレーム制御*/
#define FRAME_LIMIT 16
/*弾や敵の状況*/
#define NOT_EXIST 0
#define EXIST 1
/*座標に使う型*/
typedef signed long uint;
/*OpenGL専用*/
typedef float ufloat;
/*glPoint構造体*/
typedef struct{
	ufloat x;		//x座標
	ufloat y;		//y座標
	ufloat width;	//実際の半分
	ufloat height;	//同上
}glPoint;

#endif
