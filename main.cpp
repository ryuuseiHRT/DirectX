//-----------------------------------------------------
//
//athor:H I R A T A DirectX基本 [main.cpp]
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

//グローバル宣言
LPDIRECT3D9 g_pD3D = NULL;	//Direct3Dへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDeviec = NULL;
MODE g_mode = MODE_TITLE;		//現在のモード
bool g_isFullscreen = false;// ウィンドウを切り替えるためのフラグ
RECT g_windowRect;// ウィンドウを切り替えるための変数

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDeviec;
}

//----------------
//メイン関数
//---------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//_In_(ASL:ソースコード注釈言語)
{
	DWORD dwCurrentTime;	//現在の時刻
	DWORD dwExeclastTime;	//最後に処理した時刻

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

	HWND hWnd;	//ウィンドウバンドル（識別子）
	MSG msg;	//メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//画面サイズの構造体

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウの生成
	hWnd = CreateWindowEx(0,	//拡張ウィンドウスタイル
		CLASS_NAME,				//ウィンドウクラスの名前
		WINDOW_NAME,			//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
		CW_USEDEFAULT,			//ウィンドウのｘ座標
		CW_USEDEFAULT,			//ウィンドウのｙ座標
		(rect.right-rect.left),			//ウィンドウの幅
		(rect.bottom-rect.top),			//ウィンドウの高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューウィンドウのハンドル（子ウィンドウ）
		hInstance,				//インスタンスハンドル
		NULL);					//ウィンドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//初期化
	dwExeclastTime = timeGetTime();		//現在時刻を取得(保存)

	//ウィンドウ表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受けっとったらループを抜ける
				break;
			}
			else
			{
				//メッセージ設定
				TranslateMessage(&msg);		//仮想キーメッセージを文字に変換
				DispatchMessage(&msg);		//ウィンドウプロシージャへ送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))		//60を変えればfps上がる
			{//60分の1秒経過
				dwExeclastTime = dwCurrentTime;	//処理開始の時刻[現在時刻]を保存

				//更新処理
				Update();

				//描画処理
				Draw();

			}
		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの解除
	UnregisterClass(CLASS_NAME, wcex. hInstance);
	return(int)msg.wParam;
}
//************************************************
// ウィンドウをフルスクリーンに変える処理
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}
//-----------------------
//ウィンドウプロシージャ
//----------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//ウィンドウの領域

	switch (uMsg)
	{
	case WM_DESTROY:				//ウィンドウズを破棄する
		//WM_QUITメッセージ
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:				//[ESC]キーが押された
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
// 初期化処理
// ----------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd,BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//オブジェクト生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//でぃすぷれいの取得
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

	//レンダーステートの設定
	g_pD3DDeviec->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDeviec->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDeviec->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDeviec->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステート
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期化
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//サウンド
	InitSound(hWnd);

	//モード
	SetMode(g_mode);
	InitFade(g_mode);

	return S_OK;
}
// 終了
void Uninit(void)
{
	//キーボード終了
	UninitKeyboard();
	//ジョイパッド終了
	UninitJoypad();
	//フェード終了
	UninitFade();
	//タイトル終了
	UninitTitle();
	//ゲーム終了
	UninitGame();
	//リザルト終了
	UninitResult();
	//サウンド
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
	//キーボード
	UpdateKeyboard();
	//ジョイパッド
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();	//タイトル画面
		break;
	case MODE_GAME:
		UpdateGame();	//ゲーム画面
		break;
	case MODE_RESULT:
		UpdateResult();	//リザルト画面
		break;
	case MODE_CLEAR:
		UpdateClear();	//リザルト画面
		break;
	}
	//フェード更新
	UpdateFade();
}
void Draw(void)
{
	//画面クリア
	g_pD3DDeviec->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDeviec->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
				DrawTitle();	//タイトル
				break;
		case MODE_GAME:
				DrawGame();		//ゲーム
				break;
		case MODE_RESULT:
				DrawResult();	//リザルト
				break;
		case MODE_CLEAR:
			DrawClear();	//くりあ
			break;
		}

		//フェード描画
		DrawFade();

		//終了
		g_pD3DDeviec->EndScene();
	}
	//入れ替え
	g_pD3DDeviec->Present(NULL, NULL, NULL, NULL);
}
//モードの設定
void SetMode(MODE mode)
{
	//現在のモードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();		//タイトル
		break;
	case MODE_GAME:
		UninitGame();		//ゲーム
		break;
	case MODE_RESULT:
		UninitResult();		//リザルト
		break;
	case MODE_CLEAR:
		UninitClear();		// クリア
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
			InitTitle();		//タイトル
			break;
	case MODE_GAME:
			InitGame();			//ゲーム
			break;
	case MODE_RESULT:
			InitResult();		//リザルト
			break;
	case MODE_CLEAR:
			InitClear();		// クリア
			break;
	}

	g_mode = mode;
}
//モードの取得
MODE GetMode(void)
{
	return g_mode;
}
