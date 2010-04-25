#ifndef POINT_H_
#define POINT_H_
/*��ʔ䗦�@�����4:3*/
#define GAME_SCREEN_WIDTH  ((SCREEN_HEIGHT >> 2)*3)
#define GAME_SCREEN_HEIGHT SCREEN_HEIGHT
#define GAME_SCREEN_X_START ((SCREEN_WIDTH-GAME_SCREEN_WIDTH) >> 1)
#define GAME_SCREEN_Y_START 0

/*�Œ菬���_�̃P�^���@������Ə�����*/
#define BIT 8
/*�����_�p*/
#define BIT_POINT 256

/*POINT�\���̂̒�`*/
typedef struct{
	uint x;				//x���W
	uint y;				//y���W
	uint radius;		//���a
	uint width;			//���ۂ̔���
	uint height;		//����
}Point;

typedef struct{
	uint x;		//x����
	uint y;		//y����
	uint speed;	//�X�s�[�h
}Vector;

/*��ʕ�*/
int isInGameSpace(const Point* a,int overplus);

/*������*/
void initPoint();
/*�l�p�`�œ����蔻��*/
int isHitSquare(const Point* a,const Point* b,uint overplus);
/*�����̎���𓾂�*/
uint getDistance2(uint dx,uint dy);
/*
 * ���ۂɕ`�ʂ����|�C���g�̎擾
 */
void getPaintedPoint(glPoint *out,const Point *pt);

/*������*/
uint sqrti(uint d);

/*�x�N�g���̎擾*/
void getVector(Vector* out,const Point* a,const Point* b,uint speed);
/*�X�s�[�h�̕ύX*/
void changeVectorSpeed(Vector* vec,uint speed);
/*���F�N�g���̉�]*/
void rotateVector(Vector* vec,uint theta);

/*�O�p�֐�*/
uint usin(uint theta);
uint ucos(uint theta);
float getTheta(const Vector* vec);
/*�`��|�C���g��ݒ肷��B�ȉ��̕`��|�C���g�͂��ꂪ���ɂȂ�*/
void setDrawnPoint(const glPoint* point);

#endif
