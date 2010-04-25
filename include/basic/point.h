#ifndef POINT_H_
#define POINT_H_
/*画面比率　今回は4:3*/
#define GAME_SCREEN_WIDTH  ((SCREEN_HEIGHT >> 2)*3)
#define GAME_SCREEN_HEIGHT SCREEN_HEIGHT
#define GAME_SCREEN_X_START ((SCREEN_WIDTH-GAME_SCREEN_WIDTH) >> 1)
#define GAME_SCREEN_Y_START 0

/*固定小数点のケタ数　ちょっと小さめ*/
#define BIT 8
/*小数点用*/
#define BIT_POINT 256

/*POINT構造体の定義*/
typedef struct{
	uint x;				//x座標
	uint y;				//y座標
	uint radius;		//半径
	uint width;			//実際の半分
	uint height;		//同上
}Point;

typedef struct{
	uint x;		//x方向
	uint y;		//y方向
	uint speed;	//スピード
}Vector;

/*画面幅*/
int isInGameSpace(const Point* a,int overplus);

/*初期化*/
void initPoint();
/*四角形で当たり判定*/
int isHitSquare(const Point* a,const Point* b,uint overplus);
/*距離の自乗を得る*/
uint getDistance2(uint dx,uint dy);
/*
 * 実際に描写されるポイントの取得
 */
void getPaintedPoint(glPoint *out,const Point *pt);

/*平方根*/
uint sqrti(uint d);

/*ベクトルの取得*/
void getVector(Vector* out,const Point* a,const Point* b,uint speed);
/*スピードの変更*/
void changeVectorSpeed(Vector* vec,uint speed);
/*ヴェクトルの回転*/
void rotateVector(Vector* vec,uint theta);

/*三角関数*/
uint usin(uint theta);
uint ucos(uint theta);
float getTheta(const Vector* vec);
/*描画ポイントを設定する。以下の描画ポイントはこれが元になる*/
void setDrawnPoint(const glPoint* point);

#endif
