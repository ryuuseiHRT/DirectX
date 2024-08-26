#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP=0,	//十字キー(↑)
	JOYKEY_DOWN,	//十字キー(↓)
	JOYKEY_LEFT,	//十字キー(←)
	JOYKEY_RIGHT,	//十字キー(→)
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_LPUSH,
	JOYKEY_RPUSH,
	JOYKEY_LB,
	JOYKEY_RB,
	JOYKEY_LT,
	JOYKEY_RT,
	JOYKEY_A,		
	JOYKEY_B,		
	JOYKEY_X,		
	JOYKEY_Y,
	JOYKEY_MAX
}JOYKEY;

//==================
//プロトタイプ
//==================
//キーボード
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeybordTrigger(int nKey);
bool KeybordRelease(int nKey);
bool KeybordRepeat(int nKey);

//ジョイパッド
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoyPadTrigger(JOYKEY key);
bool JoyPadRelease(JOYKEY key);
bool JoyPadRepeat(JOYKEY key);

#endif