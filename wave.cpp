//=====================================================
//
//           敵のウェーブ処理
// 
// Author : Ryuusei Hirata     [wave.cpp]
//
//=====================================================

#include "wave.h"
#include "enemy.h"
#include "game.h"

//========================
// マクロ定義
//========================
#define MAX_WAVE (3)

//========================
// グローバル変数
//========================
Wave g_aWave;

//***********************
// 初期化処理
//***********************
void InitWave(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイス取得
	pDevice = GetDevice();

	g_aWave.bUse = false;
	g_aWave.nCntWave = 0;
	g_aWave.WaveState = WAVE_NONE;

}
//***********************
// 終了処理
//***********************
void UninitWave(void)
{

}
//***********************
// 更新処理
//***********************
void UpdateWave(void)
{

}
//***********************
// 描画処理
//***********************
void DrawWave(void)
{

}
//***********************
// waveのセット
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
// 現在のウェーブ
Wave* GetWave(void)
{
	return &g_aWave;
}