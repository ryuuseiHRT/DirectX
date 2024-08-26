#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"main.h"

//�����̍\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXCOLOR col;					//�F
	int nCounterAnimExplosion;		//�A�j���[�V�����J�E���^�[
	int nPttarnAnimExplosion;		//�A�j���[�V�����p�^�[��
	bool bUse;						//�g�p���Ă邩
}Explosion;

void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);//�����ʒu�@�F

#endif