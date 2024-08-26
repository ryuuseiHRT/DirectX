#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

// マクロ定義
#define MAX_ITEM (5)	//最大数

//アイテムの列挙型
typedef enum
{
	ITEMTYPE_ONE=0,			// コイン
	ITEMTYPE_TWO,			// ドクロ
	ITEMTYPE_THREE,			// ？
	ITEMTYPE_FOUR,			// 人間
	ITEMTYPE_FIVE,			// 弾
	ITEMTYPE_MAX
}ITEMTYPE;

typedef enum
{
	ITEMSTATE_NONE = 0,
	ITEMSTATE_NORMAL,
	ITEMSTATE_DAMEGE,
	ITEMSTATE_MAX
}ITEMSTATE;

// アイテムの構造体
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXCOLOR col;					// 色
	D3DXVECTOR3 rot;				// 角度
	ITEMSTATE state;				// アイテムの状態
	int nCounterState;				// 状態のカウント
	int nCounterAnimItem;			// アニメーションカウンター
	int nPttarnAnimItem;			// アニメーションパターン
	int nSoul;						// 魂
	int nType;						// 種類
	bool bUse;						// 使用してるか
}ITEM;

// プロトタイプ
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, int nType);
void HitItem(int nCntItem,int nDamage);
ITEM * GetItem(void);

#endif // !_ITEM_H_
