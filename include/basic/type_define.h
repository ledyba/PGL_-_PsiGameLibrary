#ifndef TYPE_DEFINE_H_
#define TYPE_DEFINE_H_
/*�t���[������*/
#define FRAME_LIMIT 16
/*�e��G�̏�*/
#define NOT_EXIST 0
#define EXIST 1
/*���W�Ɏg���^*/
typedef signed long uint;
/*OpenGL��p*/
typedef float ufloat;
/*glPoint�\����*/
typedef struct{
	ufloat x;		//x���W
	ufloat y;		//y���W
	ufloat width;	//���ۂ̔���
	ufloat height;	//����
}glPoint;

#endif
