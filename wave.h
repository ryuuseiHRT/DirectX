#pragma once
#ifndef _WAVE_H_
#define _WAVE_H_

#include "main.h"

// �E�F�[�u�̗񋓌^
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

// �v���g�^�C�v�錾
void InitWave(void);
void UninitWave(void);
void UpdateWave(void);
void DrawWave(void);
void SetWave(int nCntWave);
Wave* GetWave(void);
#endif // !_WAVE_H_

