#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

// �}�N��
#define MAX_ENEMY (128)		// �G�̐�

// �G�̏��
typedef enum
{
	ENEMYSTATE_NOMAL = 0,
	ENEMYSTATE_DAMEGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

// �G�̎��
typedef enum
{
	ENEMYTYPE_ONE=0,
	ENEMYTYPE_TWO,
	ENEMYTYPE_THREE,
	ENEMYTYPE_FOUR,
	ENEMYTYPE_MAX,
}ENEMYTYPE;

//�G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nTypr;
	ENEMYSTATE state;
	int nCounterState;
	int nLife;
	int nCntS;
	int KillCounter;
	bool bUse;
}Enemy;

//�v���g�^�C�v
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GeetNumEnemy();

#endif