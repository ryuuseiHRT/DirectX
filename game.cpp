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

//グローバル
GAMESTATE g_gameState = GAMESTATE_NONE;		// ゲームの状態
int g_nCounterGameState = 0;				// 状態管理カウンター

void InitGame(void)
{
	InitBkg();			// 背景
	InitScore();		//スコア
	InitPlayer();		// プレイヤー
	// 敵の初期化
	InitEnemy();
	InitWave();
	SetWave(0);
	InitEffect();		// エフェクト
	InitBullet();		// 弾
	InitItem();			// アイテム
	InitExplosion();	// 爆発

	g_gameState = GAMESTATE_NOMALE;		// 通常状態に設定
	g_nCounterGameState = 0;
}
void UninitGame(void)
{
	UninitBkg();			// 背景
	UninitScore();			// スコア
	UninitPlayer();			// プレイヤー
	UninitEnemy();			// 敵
	UninitEffect();			// エフェクト
	UninitBullet();			// 弾
	UninitItem();			// アイテム
	UninitExplosion();		// 爆発
}
void UpdateGame(void)
{
	UpdateBkg();				// 背景
	UpdateScore();				// スコア
	UpdatePlayer();				// プレイヤー
	UpdateEnemy();				// 敵
	UpdateEffect();				// エフェクト
	UpdateBullet();				// 弾 
	UpdateItem();				// アイテム
	UpdateExplosion();			// 爆発

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
	case GAMESTATE_NOMALE:	// 通常
		break;

	case GAMESTATE_END:		// ゲームオーバー
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	// 何もしていない

			SetFade(MODE_RESULT);
		}
		break;

	case GAMESTATE_CLEAR:	// ゲームクリア
		g_nCounterGameState++;
		if (g_nCounterGameState >= 100)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	// 何もしていない

			SetFade(MODE_CLEAR);
		}
		break;

	case GAMESTATE_WAVE:		// ウェーブ
		g_nCounterGameState++;
		if (g_nCounterGameState >= 100)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	// 何もしていない

			SetWave(aWave->nCntWave);
		}
		break;

	case GAMESTATE_BOSS:	// ボス
		
		break;
	}
}
void DrawGame(void)
{						   
	DrawBkg();			// 背景
	DrawScore();		// スコア
	DrawPlayer();		// プレイヤー
	DrawEnemy();		// 
	DrawEffect();		// エフェクト
	DrawBullet();		// 弾
	DrawItem();			// アイテム
	DrawExplosion();	// 爆発

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