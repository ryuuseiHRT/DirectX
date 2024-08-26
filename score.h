#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//=====================
// �\����
//====================
//�X�R�A���̍\����
typedef struct
{
	bool bUse;				//�g�p���Ă��邩
	int nCountScoreCounter;	//0�̃J�E���g
	int SCORE;				//�ŏI�X�R�A
}Score;

//�v���g�^�C�v
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int  ScoreCounter(int nScore);
Score* GetScore(void);

#endif // !_SCORE_H_

