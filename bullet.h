#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
//------------------------
//�e�̏���
//------------------------
#include"main.h"

#define BULLET_SPEED (10)

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER=0,
	BULLETTYPE_ENEMY,
	BULLETTYE_ITEM,
	BULLETTYPE_MAX
}BULLETTYPE;

// �e�̈З�
typedef enum
{
	BULLETPOWER_ONE,
	BULLETPOWER_TWO,
	BULLETPOWER_THREE,
	BULLETPOWER_MAX,
}BULLETPOWER;

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nLife;				//����
	BULLETTYPE type;		//�e�̎��
	bool bUse;				//�g�p���Ă��邩�ǂ���
	int nCntBullet;			//�g���e�̎��
}Bullet;

void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife,BULLETTYPE nType);

#endif