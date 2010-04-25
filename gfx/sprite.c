#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <windows.h>
#include "../include/basic/type_define.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/graphic.h"

void initSpriteSystem(){
	glHint(GL_TEXTURE_COMPRESSION_HINT_ARB, GL_NICEST);
}

void makeEmptySprite(SPRITE* sprite,int w, int h,int blending,int enable_compression){
	int rw = getMinPowerOfTwo(w);
	int rh = getMinPowerOfTwo(h);
	//テクスチャID作成
	sprite->TexID = genNewTextureID();
	sprite->blending = blending;
	sprite->Width = w;
	sprite->Height= h;
	sprite->RealWidth = rw;
	sprite->RealHeight = rh;
	//無地のサーフェイスを作ってくれる
	SDL_Surface* tmpImage = getTextureSurface(NULL,rw,rh,blending);
	//パラメータの指定
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //サーフェイスからテクスチャを製作
    int out_flag = GL_COMPRESSED_RGB_ARB;
    int in_flag = GL_RGB;
    if(blending){
    	out_flag = GL_COMPRESSED_RGBA_ARB;
    	in_flag = GL_RGBA;
    }
    if(!enable_compression){
    	out_flag = in_flag;
    }
    glTexImage2D( GL_TEXTURE_2D, 0, out_flag, rw, rh, 0,
								  in_flag, GL_UNSIGNED_BYTE, tmpImage->pixels );

	/*サーフェイスの開放*/
    SDL_FreeSurface( tmpImage );
}

void updateSpriteFromSurface(SPRITE* sprite,SDL_Surface* surface,int enable_compression){
	//テクスチャをバインド
    glBindTexture( GL_TEXTURE_2D, sprite->TexID );
	if(surface->w <= sprite->RealWidth && surface->h <= sprite->RealWidth){
		//リサイズ不要
		//何はともあれサイズ設定
		sprite->Width = surface->w;
		sprite->Height = surface->h;
		//パラメータの指定
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		//テクチャ上書き
	    int flag = GL_RGB;
	    if(sprite->blending){
	    	flag = GL_RGBA;
	    }
	    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, 
									  flag, GL_UNSIGNED_BYTE, surface->pixels );
	}else{
//		//リサイズ必要　作り直すしかない？
		deleteSprite(sprite);
		getSpriteFromSurface(sprite,surface,sprite->blending,enable_compression);
	}
}

/*スプライトの取得*/
void getSpriteFromSurface(SPRITE* sprite,SDL_Surface* surface,int blending,int enable_compression){
	//ブレンディング情報の設定
	sprite->blending = blending;
	//サイズ情報の設定
	setSpriteSizeInformation(sprite,surface->w,surface->h);
	//あたらしいテクスチャIDの作成
    sprite->TexID = genNewTextureID();
    //製作したテクスチャのバインド
    glBindTexture( GL_TEXTURE_2D, sprite->TexID );
    int out_flag = GL_COMPRESSED_RGB_ARB;
    int in_flag = GL_RGB;
    if(blending){
    	out_flag = GL_COMPRESSED_RGBA_ARB;
    	in_flag = GL_RGBA;
    }
    if(!enable_compression){
    	out_flag = in_flag;
    }
    //サーフェイスの変換
    int rw = sprite->RealWidth;
    int rh = sprite->RealHeight;
    SDL_Surface* tmpImage = getTextureSurface(surface,rw,rh,blending);
	//パラメータの指定
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    //サーフェイスからテクスチャを製作
    glTexImage2D( GL_TEXTURE_2D, 0, out_flag, rw, rh, 0,
								  in_flag, GL_UNSIGNED_BYTE, tmpImage->pixels );

	/*サーフェイスの開放*/
    SDL_FreeSurface( tmpImage );
}

/*サイズ情報を設定*/
void setSpriteSizeInformation(SPRITE* sprite,int w,int h){
	sprite->Width = w;
	sprite->Height = h;
	sprite->RealWidth = getMinPowerOfTwo(w);
	sprite->RealHeight = getMinPowerOfTwo(h);
}


/*スプライトの削除*/
void deleteSprite(SPRITE* sprite){
	glDeleteTextures(1,&sprite->TexID);
}

/*二のべき乗で最も小さいのを探す*/
int getMinPowerOfTwo(int num){
	int ret = 1;
	while(ret < num){
		ret = ret << 1;
	}
	return ret;
}

void getSpriteFromOPS(SPRITE *sprite,SDL_RWops* data,int blending,int enable_compression){
	SDL_Surface* surface = loadGraphix(data);
	getSpriteFromSurface(sprite,surface,blending,enable_compression);
	/*サーフェイスの開放*/
    SDL_FreeSurface( surface );
}

void getSpriteFromArchive(SPRITE* sprite,
							ARCHIVE* archive,
							const char* filename,int blending,int enable_compression){
		SDL_RWops* data = getFile(archive,filename);
		getSpriteFromOPS(sprite,data,blending,enable_compression);
		SDL_RWclose(data);
}
/*
void drawSprite(const SPRITE* sprite,const glPoint* point,int x,int y, int w, int h ,float angle){
	SPRITE_AREA area;
	makeSpriteArea(&area,sprite,x,y,w,h);
	drawSpriteArea(point,&area,0.0f);
}
*/
void drawSpriteA(const SPRITE* sprite,const glPoint* point,const GLfloat coord[8] ,float angle,const GLfloat* color){
	glPoint pt = *point;
	pt.width = sprite->Width;
	pt.height = sprite->Height;
	drawSpriteF(sprite,&pt,coord,angle,color);
}
void drawSpriteF(const SPRITE* sprite,const glPoint* point,const GLfloat coord[8] ,float angle,const GLfloat* color){
/*回転あり・なし共通処理*/
	int blending = sprite->blending;
	int rotation = angle != 0.0f;
	glEnable(GL_TEXTURE_2D);
	if(blending){
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		if(color == NULL)	glColor4f(1.0f,1.0f,1.0f,1.0f);
		else				glColor4fv(color);
	}else{
		glDisable( GL_BLEND );
		if(color == NULL)	glColor3f(1.0f,1.0f,1.0f);
		else				glColor3fv(color);
	}
	glBindTexture(GL_TEXTURE_2D , sprite->TexID);
	//変数
	GLfloat pw = point->width;
	GLfloat ph = point->height;
	//頂点変数
	GLfloat vertex[8];
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer( 2, GL_FLOAT, 0, coord );
	//回転
	if(rotation){
		glPushMatrix();
			glTranslatef(point->x, point->y, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			vertex[0] = pw;		vertex[1] = -ph;
			vertex[2] = pw;		vertex[3] = ph;
			vertex[4] = -pw;	vertex[5] = ph;
			vertex[6] = -pw;	vertex[7] = -ph;
			//描画
			glVertexPointer( 2, GL_FLOAT, 0, vertex );
			glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
		glPopMatrix();
	}else{
		//変数
		GLfloat px = point->x;
		GLfloat py = point->y;
		vertex[0] = px+pw;	vertex[1] = py-ph;
		vertex[2] = px+pw;	vertex[3] = py+ph;
		vertex[4] = px-pw;	vertex[5] = py+ph;
		vertex[6] = px-pw;	vertex[7] = py-ph;
		//描画
		glVertexPointer( 2, GL_FLOAT, 0, vertex );
		glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
	}

/*回転あり・なし共通処理*/
	if(blending){
	glDisable( GL_BLEND );
	}
	glDisable(GL_TEXTURE_2D);
}
