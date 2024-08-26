//=====================================================
//
//           �G�̃E�F�[�u����
// 
// Author : Ryuusei Hirata     [wave.cpp]
//
//=====================================================

#include "wave.h"
#include "enemy.h"
#include "game.h"

//========================
// �}�N����`
//========================
#define MAX_WAVE (3)

//========================
// �O���[�o���ϐ�
//========================
Wave g_aWave;

//***********************
// ����������
//***********************
void InitWave(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�擾
	pDevice = GetDevice();

	g_aWave.bUse = false;
	g_aWave.nCntWave = 0;
	g_aWave.WaveState = WAVE_NONE;

}
//***********************
// �I������
//***********************
void UninitWave(void)
{

}
//***********************
// �X�V����
//***********************
void UpdateWave(void)
{

}
//***********************
// �`�揈��
//***********************
void DrawWave(void)
{

}
//***********************
// wave�̃Z�b�g
//***********************
void SetWave(int nCntWave)
{
	int g_nNumEnemy = GeetNumEnemy();
	Enemy* pEnemy;
	pEnemy = GetEnemy();
	GAMESTATE g_gameState;

	switch (nCntWave)
	{
	case 0:
		SetEnemy(D3DXVECTOR3(200.0f, 500.0f, 0.0f), ENEMYTYPE_ONE);
		g_aWave.nCntWave++;
		break;
	case 1:
		SetEnemy(D3DXVECTOR3(500.0f, 500.0f, 0.0f), ENEMYTYPE_ONE);
		//SetEnemy(D3DXVECTOR3(500.0f, 500.0f, 0.0f), ENEMYTYPE_ONE);
		g_aWave.nCntWave++;
		break;
	case 2:
		SetEnemy(D3DXVECTOR3(800.0f, 500.0f, 0.0f), ENEMYTYPE_ONE);
		//SetEnemy(D3DXVECTOR3(500.0f, 500.0f, 0.0f), ENEMYTYPE_ONE);
		//SetEnemy(D3DXVECTOR3(700.0f, 500.0f, 0.0f), ENEMYTYPE_ONE);
		g_aWave.nCntWave++;
		break;
	case 3:
		SetEnemy(D3DXVECTOR3(200.0f, 200.0f, 0.0f), ENEMYTYPE_ONE);
		//SetEnemy(D3DXVECTOR3(500.0f, 500.0f, 0.0f), ENEMYTYPE_ONE);
		//SetEnemy(D3DXVECTOR3(700.0f, 500.0f, 0.0f), ENEMYTYPE_ONE);
		//SetEnemy(D3DXVECTOR3(200.0f, 300.0f, 0.0f), ENEMYTYPE_ONE);
		g_aWave.nCntWave++;
		break;
	default:
		break;
	}

	nCntWave++;
}
// ���݂̃E�F�[�u
Wave* GetWave(void)
{
	return &g_aWave;
}