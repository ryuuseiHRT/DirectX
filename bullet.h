#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
//------------------------
//弾の処理
//------------------------
#include"main.h"

#define BULLET_SPEED (10)

//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER=0,
	BULLETTYPE_ENEMY,
	BULLETTYE_ITEM,
	BULLETTYPE_MAX
}BULLETTYPE;

// 弾の威力
typedef enum
{
	BULLETPOWER_ONE,
	BULLETPOWER_TWO,
	BULLETPOWER_THREE,
	BULLETPOWER_MAX,
}BULLETPOWER;

//弾の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nLife;				//寿命
	BULLETTYPE type;		//弾の種類
	bool bUse;				//使用しているかどうか
	int nCntBullet;			//使う弾の種類
}Bullet;

void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife,BULLETTYPE nType);

#endif