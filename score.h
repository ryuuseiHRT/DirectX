#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//=====================
// 構造体
//====================
//スコア情報の構造体
typedef struct
{
	bool bUse;				//使用しているか
	int nCountScoreCounter;	//0のカウント
	int SCORE;				//最終スコア
}Score;

//プロトタイプ
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int  ScoreCounter(int nScore);
Score* GetScore(void);

#endif // !_SCORE_H_

