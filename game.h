#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0,	//�������Ă��Ȃ�
	GAMESTATE_NOMALE,	//�ʏ���(�i�s��)
	GAMESTATE_WAVE,		//�E�F�[�u
	GAMESTATE_BOSS,		// �{�X��
	GAMESTATE_END,		//�I�����(�S�ŁA�^�C���I�[�o�[ �Ȃ�)
	GAMESTATE_CLEAR,	//�Q�[���N���A
	GAMESTATE_MAX
}GAMESTATE;

//�v���^�C�v
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif // !_GAME_H_
