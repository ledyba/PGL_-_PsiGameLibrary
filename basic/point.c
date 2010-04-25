#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>
#include <math.h>

#include "../include/basic/type_define.h"
#include "../include/basic/point.h"
#include "../include/system/screen.h"

/*�O�p�֐�*/
static uint rsin[360];
static uint rcos[360];
/*�p�x�����߂邽�߂̃A�[�N�^���W�F���g*/
static float racos[BIT_POINT<<1];

void initPoint(){
	/*�O�p�֐���O�̂����Ɍv�Z���Ă�������Ƃ�*/
	int i;
	for(i=0;i<360;i++){
		rsin[i] = (uint)(sin(M_PI*i/180)*BIT_POINT);
		rcos[i] = (uint)(cos(M_PI*i/180)*BIT_POINT);
	}
	
	/*�A�[�N�^���W�F���g�v�Z*/
	for(i=0;i<BIT_POINT<<1;i++){
		racos[i]=(float)(acos( ((float)i-BIT_POINT) / BIT_POINT) ) * 180 / M_PI;
	}
	
}
/*�l�p�`�œ����蔻��
 * �U���̎��͔͈͂��g�傷��*/
int isHitSquare(const Point* a,const Point* b,uint overplus){
	uint a_width = a->width + overplus;
	uint a_height = a->height + overplus;
	return (a->x + a_width > b->x - b->width) && (b->x + b->width > a->x - a_width )
	&& (a->y + a_height > b->y - b->height) && (b->y + b->height > a->y - a_height );
}
/*�Q�[���X�y�[�X���ɂ��邩*/
int isInGameSpace(const Point* a,int overplus){
return  a->x >= ((-overplus) << BIT) && 
		 a->x <= ((GAME_SCREEN_WIDTH + overplus) << BIT) && 
		 a->y >= ((-overplus) << BIT) && 
		 a->y <= ((GAME_SCREEN_HEIGHT + overplus) << BIT);
}
/*�����̎���𓾂�*/
/*���ۂ̋������Ԃ�܂��E�E�E*/
uint getDistance2(uint dx,uint dy){
	unsigned long x = abs(dx);
	unsigned long y = abs(dy);
	x *= (x >> BIT);
	y *= (y >> BIT);
	uint res = (uint)((x + y) >> BIT);
	return res;
}
/*
 * ���ۂɕ`�ʂ����|�C���g�̎擾
 */
void getPaintedPoint(glPoint *out,const Point *pt){
	out->x 		= (float)(pt->x)/BIT_POINT;
	out->y 		= (float)(pt->y)/BIT_POINT;
	out->width  = (float)(pt->width / BIT_POINT);
	out->height	= (float)(pt->height / BIT_POINT);
}
/*������*/
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
		/*������0�̏ꍇ�́A���ɔ�΂�*/
		out->speed = speed;
		out->x = 0;
		out->y = speed;
	}
}

void changeVectorSpeed(Vector* vec,uint speed){
	/*�v�Z����Ă��Ȃ�*/
	if(vec->speed == 0)	vec->speed = sqrti(getDistance2(vec->x,vec->y)) << BIT;
	/*�{����0�Ȃ��*/
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

/*���F�N�g���̉�]*/
void rotateVector(Vector* vec,uint theta){
	uint sin = usin(theta);
	uint cos = ucos(theta);
	uint x = (cos*vec->x) - (sin*vec->y);
	uint y = (sin*vec->x) + (cos*vec->y);
	vec->x = x>>BIT;
	vec->y = y>>BIT;
}
/*�O�p�֐�*/
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
/*�`��|�C���g��ݒ肷��B�ȉ��̕`��|�C���g�͂��ꂪ���ɂȂ�*/
void setDrawnPoint(const glPoint* point){
	GLfloat w = point->width*2;
	GLfloat h = point->height*2;
	GLfloat z = h ? w : w > h;
	//�r���[�|�[�g�ݒ�
	glViewport(point->x-point->width, point->y-point->height, w, h);
	/* �ϊ��s��̏����� */
	glLoadIdentity();
	/* �X�N���[����̕\���̈���r���[�|�[�g�̑傫���ɔ�Ⴓ���� */
	glOrtho( 0, w, h, 0, -z, z);
/*
	glFrustum( 0, w, h, 0, z, z*3);
	glTranslatef(0.0f, 0.0f, -z*2);
	glScalef(2.0f,2.0f, 1.0f);
*/
}
 
