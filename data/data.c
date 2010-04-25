#include <stdio.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_rwops.h>
#include "../include/system/error_system.h"
#include "../include/data/PGL_SDL_RWops.h"
#include "../include/data/data.h"

/*�A�[�J�C�o*/

/* �A�[�J�C�u�t�@�C����W�J����
 * arc	:�A�[�J�C�u�t�@�C���̓W�J��
 * file	:�A�[�J�C�u�t�@�C��
 * */
 const static ARCHIVE_HEADER_ITEM tmpItem;
int openArchive(ARCHIVE* arc,const char *filename){
	FILE* file = arc->file = fopen(filename, "rb");
	if(file == NULL){
		raiseError("failed to prepare Archive:",filename);
		return FALSE;
	}
	/*ArchiveHeader�̓ǂݍ���*/
	
	//"ARCHIVE"���΂�
	fseek(file,strlen(ARCHIVE_TITLE),SEEK_SET);
	//�t�@�C�����̎擾
	fread(&arc->fileNum, sizeof(arc->fileNum) ,1, file);
	//�������m��
	arc->item = malloc((arc->fileNum) * sizeof(tmpItem));

	/*ArchiveHeaderItem�̓ǂݍ���*/
	ARCHIVE_HEADER_ITEM* it = arc->item;
	int i=0,fileNum = arc->fileNum,check;
	for(;i<fileNum;i++){
		check = 0;
		//�������擾
		check += fread(&it->fileNameSize, sizeof(it->fileNameSize) ,1, file);
		//�����擾
		it->fileName = malloc(it->fileNameSize+1);
		check += fread(it->fileName, it->fileNameSize ,1, file); 
		//�Ō��0�ŕ߂Ă����ƏI�[�����I
		it->fileName[it->fileNameSize] = '\0';
		//�I�t�Z�b�g�A�T�C�Y�B
		check += fread(&it->offset, sizeof(it->offset) ,1, file);
		check += fread(&it->size, sizeof(it->size) ,1, file);
		it++;
		if(check != 4){
			closeArchive(arc);
			raiseError("failed to get Header in Archive:",filename);
		}
	}
	return TRUE;
}
/* 
 * arc		:�A�[�J�C�ԃt�@�C��
 * filename	:�t�@�C����
 * */
SDL_RWops* getFile(ARCHIVE* arc, const char* filename){
//	fprintf(stdout,"searching:%s	,",filename);
//	fprintf(stdout,"size:%d	,",arc->fileNum);
	ARCHIVE_HEADER_ITEM* it = arc->item;
	int i,file_num = arc->fileNum,check = FALSE;
	for(i=0;i<file_num;i++){
		//��v����Ώo��
//		fprintf(stdout,"file:%s	,search:%s\n",filename,it->fileName);

		char* file_name = it->fileName;
		if(strcmp(file_name,filename) == 0){
			check = TRUE;
			break;
		}
		it++;
	}
	/*�t�@�C����������Ȃ�����*/
	if(check == FALSE){
		closeArchive(arc);
		raiseError("file not found:",filename);
	}
	void* data = malloc(it->size);
	fseek(arc->file,it->offset,SEEK_SET);
	fread(data, it->size, 1, arc->file);
	SDL_RWops* buf = PGL_SDL_RWFromMem(data, it->size);
	/*
	static int once = 4;
	if(once == 0){
		SDL_RWops* ops = SDL_RWFromFile("i.png","w");
		SDL_RWwrite(ops,data,it->size,1);
		SDL_RWclose(ops);
	}
	once--;
	*/
	return buf;
}

/* �A�[�J�C�u�t�@�C�������
 * arc	:�A�[�J�C�u�t�@�C��
 */
int closeArchive(ARCHIVE* arc){
	/*�Ƃ������A�������J���I*/
	//�܂��́A����
	ARCHIVE_HEADER_ITEM* it = arc->item;
	int i,num = arc->fileNum;
	for(i=0;i<num;i++){
		free(it->fileName);
		it++;
	}
	//�����āA�A�C�e�����X�g�S��
	free(arc->item);
	//�t�@�C�������
	fclose(arc->file);
	return TRUE;
}
