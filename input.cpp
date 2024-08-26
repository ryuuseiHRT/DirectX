//================================================
//
// 入力処理　[input.cpp]
// Athor : HRT ryuusei
//
//================================================

#include "input.h"

//================================================
// マクロ
//================================================
#define NUM_KEY_MAX (256)				//キーの最大数

//================================================
// グローバル
//================================================
XINPUT_STATE g_joyKeyState;					//ジョイパッドのプレス情報
XINPUT_STATE g_OldKeyState;
LPDIRECTINPUT8 g_pInput = NULL;				//DeirectInputへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//入力デバイスへのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aOldState[NUM_KEY_MAX];

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// Directinputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	// 入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットの設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// 協調モード
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	
	// キーボードへのアクセス剣を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
void UninitKeyboard(void)
{
	// 入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//キーボードへのアクセス権を破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	// DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//キーボードの入力情報
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];		//キーボードプレス情報を保存
	}

	// 入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];		//キーボードプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
bool GetKeyboardPress(int nKey)
{// 押されてるキー
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
bool KeybordTrigger(int nKey)
{// 一歩だけ
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeybordRelease(int nKey)
{// 長押し
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeybordRepeat(int nKey)
{// 押されてる間
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================================================
// ジョイパッドの処理
//================================================================
//===================
// 初期化処理
//===================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//xinputのステートの設定(有効にする
	XInputEnable(true);

	return S_OK;
}
//===================
// 終了処理
//===================
void UninitJoypad(void)
{
	//xinputのステートの設定(無効にする
	XInputEnable(false);
}
//===================
// 更新処理
//===================
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState;		//入力情報

	g_OldKeyState = g_joyKeyState;		//キーボードプレス情報を保存

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joyKeyState;		//ジョイパッドのプレス情報を保存
	}
}
//===================
// プレス情報を取得
//===================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//===================
// トリガー情報を取得
//===================
bool JoyPadTrigger(JOYKEY key)
{
	bool Trigger = false;

	if (g_joyKeyState.Gamepad.wButtons & (0x01 << key))
	{
		if (g_joyKeyState.Gamepad.wButtons != g_OldKeyState.Gamepad.wButtons && g_joyKeyState.Gamepad.bLeftTrigger == g_OldKeyState.Gamepad.wButtons)
		{
			Trigger = true;
		}
	}

	return Trigger;

}