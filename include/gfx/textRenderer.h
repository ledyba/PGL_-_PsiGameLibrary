#ifndef TEXT_RENDERER_H_
#define TEXT_RENDERER_H_
/**
 * �e�L�X�g��`�悵�āA�X�v���C�g�ɕϊ����܂��B
 * ����́A
 * SDL_ttf�ŃT�[�t�F�C�X���쐬���X�v���C�g�Ɏg����`���ɕϊ�
 * ���X�v���C�g�i�e�N�X�`���j��
 * �e�N�X�`���͊�{�I�Ɉꖇ���g���܂킵
 */
 
 /**
  * ���������܂��B
  */
int initTextRenderer(SDL_RWops *src,int default_fontsize);
/**
 * �I�����܂��B
 */
void quitTextRenderer();
/*�h���[�֐�*/
void drawText(const glPoint* point,const char* text);
/*�X�v���C�g����֐�*/
void updateTextSprite(SPRITE* sprite,const char* text);
void makeTextSprite(SPRITE* sprite,const char* text);
#endif
