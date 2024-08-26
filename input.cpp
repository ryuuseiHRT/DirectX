//================================================
//
// ���͏����@[input.cpp]
// Athor : HRT ryuusei
//
//================================================

#include "input.h"

//================================================
// �}�N��
//================================================
#define NUM_KEY_MAX (256)				//�L�[�̍ő吔

//================================================
// �O���[�o��
//================================================
XINPUT_STATE g_joyKeyState;					//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_OldKeyState;
LPDIRECTINPUT8 g_pInput = NULL;				//DeirectInput�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//���̓f�o�C�X�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aOldState[NUM_KEY_MAX];

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// Directinput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	// ���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// �������[�h
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}
void UninitKeyboard(void)
{
	// ���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	// DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];		//�L�[�{�[�h�v���X����ۑ�
	}

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];		//�L�[�{�[�h�v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
bool GetKeyboardPress(int nKey)
{// ������Ă�L�[
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
bool KeybordTrigger(int nKey)
{// �������
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeybordRelease(int nKey)
{// ������
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeybordRepeat(int nKey)
{// ������Ă��
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================================================
// �W���C�p�b�h�̏���
//================================================================
//===================
// ����������
//===================
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//xinput�̃X�e�[�g�̐ݒ�(�L���ɂ���
	XInputEnable(true);

	return S_OK;
}
//===================
// �I������
//===================
void UninitJoypad(void)
{
	//xinput�̃X�e�[�g�̐ݒ�(�����ɂ���
	XInputEnable(false);
}
//===================
// �X�V����
//===================
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState;		//���͏��

	g_OldKeyState = g_joyKeyState;		//�L�[�{�[�h�v���X����ۑ�

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joyKeyState = joyKeyState;		//�W���C�p�b�h�̃v���X����ۑ�
	}
}
//===================
// �v���X�����擾
//===================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//===================
// �g���K�[�����擾
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