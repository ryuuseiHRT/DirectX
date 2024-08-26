#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE = 0,	//何もしていない
	GAMESTATE_NOMALE,	//通常状態(進行中)
	GAMESTATE_WAVE,		//ウェーブ
	GAMESTATE_BOSS,		// ボス戦
	GAMESTATE_END,		//終了状態(全滅、タイムオーバー など)
	GAMESTATE_CLEAR,	//ゲームクリア
	GAMESTATE_MAX
}GAMESTATE;

//プロタイプ
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif // !_GAME_H_
