#include "game.h"
#include "main.h"
#include "player.h"
#include "bkg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include"fade.h"
#include"score.h"
#include "item.h"
#include "wave.h"
#include "effect.h"

//�O���[�o��
GAMESTATE g_gameState = GAMESTATE_NONE;		// �Q�[���̏��
int g_nCounterGameState = 0;				// ��ԊǗ��J�E���^�[

void InitGame(void)
{
	InitBkg();			// �w�i
	InitScore();		//�X�R�A
	InitPlayer();		// �v���C���[
	// �G�̏�����
	InitEnemy();
	InitWave();
	SetWave(0);
	InitEffect();		// �G�t�F�N�g
	InitBullet();		// �e
	InitItem();			// �A�C�e��
	InitExplosion();	// ����

	g_gameState = GAMESTATE_NOMALE;		// �ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
}
void UninitGame(void)
{
	UninitBkg();			// �w�i
	UninitScore();			// �X�R�A
	UninitPlayer();			// �v���C���[
	UninitEnemy();			// �G
	UninitEffect();			// �G�t�F�N�g
	UninitBullet();			// �e
	UninitItem();			// �A�C�e��
	UninitExplosion();		// ����
}
void UpdateGame(void)
{
	UpdateBkg();				// �w�i
	UpdateScore();				// �X�R�A
	UpdatePlayer();				// �v���C���[
	UpdateEnemy();				// �G
	UpdateEffect();				// �G�t�F�N�g
	UpdateBullet();				// �e 
	UpdateItem();				// �A�C�e��
	UpdateExplosion();			// ����

	int nNum;
	Enemy* pEnemy;
	pEnemy = GetEnemy();
	nNum = GeetNumEnemy();
	Wave* aWave;
	aWave = GetWave();
	Player* pPlayer;
	pPlayer = GetPlayer();

	if (nNum <= 0)
	{
		g_gameState = GAMESTATE_WAVE;

		if (aWave->nCntWave >= 4)
		{
			g_gameState = GAMESTATE_CLEAR;
		}
	}
	else if (pPlayer->bDisp == false)
	{
		g_gameState = GAMESTATE_END;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NOMALE:	// �ʏ�
		break;

	case GAMESTATE_END:		// �Q�[���I�[�o�[
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ�

			SetFade(MODE_RESULT);
		}
		break;

	case GAMESTATE_CLEAR:	// �Q�[���N���A
		g_nCounterGameState++;
		if (g_nCounterGameState >= 100)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ�

			SetFade(MODE_CLEAR);
		}
		break;

	case GAMESTATE_WAVE:		// �E�F�[�u
		g_nCounterGameState++;
		if (g_nCounterGameState >= 100)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ�

			SetWave(aWave->nCntWave);
		}
		break;

	case GAMESTATE_BOSS:	// �{�X
		
		break;
	}
}
void DrawGame(void)
{						   
	DrawBkg();			// �w�i
	DrawScore();		// �X�R�A
	DrawPlayer();		// �v���C���[
	DrawEnemy();		// 
	DrawEffect();		// �G�t�F�N�g
	DrawBullet();		// �e
	DrawItem();			// �A�C�e��
	DrawExplosion();	// ����

}
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	//g_nCounterGameState = 0;
}
GAMESTATE GetGameState(void)
{
	return g_gameState;
}