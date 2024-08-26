#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

// �}�N����`
#define MAX_ITEM (5)	//�ő吔

//�A�C�e���̗񋓌^
typedef enum
{
	ITEMTYPE_ONE=0,			// �R�C��
	ITEMTYPE_TWO,			// �h�N��
	ITEMTYPE_THREE,			// �H
	ITEMTYPE_FOUR,			// �l��
	ITEMTYPE_FIVE,			// �e
	ITEMTYPE_MAX
}ITEMTYPE;

typedef enum
{
	ITEMSTATE_NONE = 0,
	ITEMSTATE_NORMAL,
	ITEMSTATE_DAMEGE,
	ITEMSTATE_MAX
}ITEMSTATE;

// �A�C�e���̍\����
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXCOLOR col;					// �F
	D3DXVECTOR3 rot;				// �p�x
	ITEMSTATE state;				// �A�C�e���̏��
	int nCounterState;				// ��Ԃ̃J�E���g
	int nCounterAnimItem;			// �A�j���[�V�����J�E���^�[
	int nPttarnAnimItem;			// �A�j���[�V�����p�^�[��
	int nSoul;						// ��
	int nType;						// ���
	bool bUse;						// �g�p���Ă邩
}ITEM;

// �v���g�^�C�v
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, int nType);
void HitItem(int nCntItem,int nDamage);
ITEM * GetItem(void);

#endif // !_ITEM_H_
