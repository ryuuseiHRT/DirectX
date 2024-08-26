//-----------------------------------------------------
//
//athor:H I R A T A DirectX��{ [main.cpp]
//
//---------------------------------------------------
#include "main.h"
#include "player.h"
#include "bkg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include"clear.h"

//�O���[�o���錾
LPDIRECT3D9 g_pD3D = NULL;	//Direct3D�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDeviec = NULL;
MODE g_mode = MODE_TITLE;		//���݂̃��[�h
bool g_isFullscreen = false;// �E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;// �E�B���h�E��؂�ւ��邽�߂̕ϐ�

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDeviec;
}

//----------------
//���C���֐�
//---------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//_In_(ASL:�\�[�X�R�[�h���ߌ���)
{
	DWORD dwCurrentTime;	//���݂̎���
	DWORD dwExeclastTime;	//�Ō�ɏ�����������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,

		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION),
	};

	HWND hWnd;	//�E�B���h�E�o���h���i���ʎq�j
	MSG msg;	//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//��ʃT�C�Y�̍\����

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�̐���
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME,				//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,			//�E�B���h�E�̂����W
		CW_USEDEFAULT,			//�E�B���h�E�̂����W
		(rect.right-rect.left),			//�E�B���h�E�̕�
		(rect.bottom-rect.top),			//�E�B���h�E�̍���
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�E�B���h�E�̃n���h���i�q�E�B���h�E�j
		hInstance,				//�C���X�^���X�n���h��
		NULL);					//�E�B���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//������
	dwExeclastTime = timeGetTime();		//���ݎ������擾(�ۑ�)

	//�E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//window�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯂��Ƃ����烋�[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�ݒ�
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎��ɕϊ�
				DispatchMessage(&msg);		//�E�B���h�E�v���V�[�W���֑��o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))		//60��ς����fps�オ��
			{//60����1�b�o��
				dwExeclastTime = dwCurrentTime;	//�����J�n�̎���[���ݎ���]��ۑ�

				//�X�V����
				Update();

				//�`�揈��
				Draw();

			}
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̉���
	UnregisterClass(CLASS_NAME, wcex. hInstance);
	return(int)msg.wParam;
}
//************************************************
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}
//-----------------------
//�E�B���h�E�v���V�[�W��
//----------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//�E�B���h�E�̗̈�

	switch (uMsg)
	{
	case WM_DESTROY:				//�E�B���h�E�Y��j������
		//WM_QUIT���b�Z�[�W
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:				//[ESC]�L�[�������ꂽ
		switch (wParam)
		{
		case VK_ESCAPE:
			//int nID;
				DestroyWindow(hWnd);
				break;
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//----------------------------
// ����������
// ----------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd,BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//�I�u�W�F�N�g����
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�ł����Ղꂢ�̎擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDeviec)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDeviec)))

		{
			return E_FAIL;
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDeviec->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDeviec->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDeviec->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDeviec->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏�����
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//�W���C�p�b�h�̏�����
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//�T�E���h
	InitSound(hWnd);

	//���[�h
	SetMode(g_mode);
	InitFade(g_mode);

	return S_OK;
}
// �I��
void Uninit(void)
{
	//�L�[�{�[�h�I��
	UninitKeyboard();
	//�W���C�p�b�h�I��
	UninitJoypad();
	//�t�F�[�h�I��
	UninitFade();
	//�^�C�g���I��
	UninitTitle();
	//�Q�[���I��
	UninitGame();
	//���U���g�I��
	UninitResult();
	//�T�E���h
	UninitSound();

	if (g_pD3DDeviec != NULL)
	{
		g_pD3DDeviec->Release();
		g_pD3DDeviec = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;

	}
}
void Update(void)
{
	//�L�[�{�[�h
	UpdateKeyboard();
	//�W���C�p�b�h
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();	//�^�C�g�����
		break;
	case MODE_GAME:
		UpdateGame();	//�Q�[�����
		break;
	case MODE_RESULT:
		UpdateResult();	//���U���g���
		break;
	case MODE_CLEAR:
		UpdateClear();	//���U���g���
		break;
	}
	//�t�F�[�h�X�V
	UpdateFade();
}
void Draw(void)
{
	//��ʃN���A
	g_pD3DDeviec->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDeviec->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
				DrawTitle();	//�^�C�g��
				break;
		case MODE_GAME:
				DrawGame();		//�Q�[��
				break;
		case MODE_RESULT:
				DrawResult();	//���U���g
				break;
		case MODE_CLEAR:
			DrawClear();	//���肠
			break;
		}

		//�t�F�[�h�`��
		DrawFade();

		//�I��
		g_pD3DDeviec->EndScene();
	}
	//����ւ�
	g_pD3DDeviec->Present(NULL, NULL, NULL, NULL);
}
//���[�h�̐ݒ�
void SetMode(MODE mode)
{
	//���݂̃��[�h�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();		//�^�C�g��
		break;
	case MODE_GAME:
		UninitGame();		//�Q�[��
		break;
	case MODE_RESULT:
		UninitResult();		//���U���g
		break;
	case MODE_CLEAR:
		UninitClear();		// �N���A
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
			InitTitle();		//�^�C�g��
			break;
	case MODE_GAME:
			InitGame();			//�Q�[��
			break;
	case MODE_RESULT:
			InitResult();		//���U���g
			break;
	case MODE_CLEAR:
			InitClear();		// �N���A
			break;
	}

	g_mode = mode;
}
//���[�h�̎擾
MODE GetMode(void)
{
	return g_mode;
}
