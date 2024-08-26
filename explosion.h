#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"main.h"

//爆発の構造体
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXCOLOR col;					//色
	int nCounterAnimExplosion;		//アニメーションカウンター
	int nPttarnAnimExplosion;		//アニメーションパターン
	bool bUse;						//使用してるか
}Explosion;

void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);//発生位置　色

#endif