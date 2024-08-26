#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_
//------------------------
//弾の処理
//------------------------
#include"main.h"

////弾の種類
//typedef enum
//{
//	BULLETTYPE_PLAYER = 0,
//	BULLETTYPE_ENEMY,
//	BULLETTYE_ITEM,
//	BULLETTYPE_MAX
//}BULLETTYPE;


void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fRadius);

#endif