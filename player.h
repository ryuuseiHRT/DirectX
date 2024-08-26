#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef enum
{
	PLAYERSTATE_APPER = 0,	// �o��
	PLAYERSTATE_NOMAL,		// �ʏ�
	PLAYERSTATE_DAMEGE,		// �_���[�W
	PLAYERSTATE_DETH,		// ���S
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	float fLength;
	float fAngle;
	PLAYERSTATE state;
	int nCounterState;
	int nLife;
	bool bDisp;	// �\�����邩
	int nCntLife;
}Player;

//�v���g�^�C�v
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);

#define PLAYER_HEIGHT (150)		//����
#define PLAYER_WIDTH (150)		//��

#endif