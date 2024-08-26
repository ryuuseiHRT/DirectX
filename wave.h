#pragma once
#ifndef _WAVE_H_
#define _WAVE_H_

#include "main.h"

// ウェーブの列挙型
typedef enum
{
	WAVE_NONE = 0,
	WAVE_ONE,
	WAVE_TWO,
	WAVE_THREE,
	WAVE_MAX
}WAVE;

typedef struct
{
	bool bUse;
	int nCntWave;
	WAVE WaveState;
}Wave;

// プロトタイプ宣言
void InitWave(void);
void UninitWave(void);
void UpdateWave(void);
void DrawWave(void);
void SetWave(int nCntWave);
Wave* GetWave(void);
#endif // !_WAVE_H_

