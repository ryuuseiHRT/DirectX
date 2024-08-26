#ifndef _MAIN_H_		//この定義がされなかったら
#define _MAIN_H_		//二重インクルード防止のマクロ定義

#include<windows.h>
#include"d3dx9.h"							//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)		//ビルド時の警告対処用マクロ
#include "dinput.h"							//キーボードの入力処理に必要
#include "Xinput.h"							//ジョイパットの入力処理
#include "xaudio2.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")				//描画処理に必要
#pragma comment(lib,"d3dx9.lib")			//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")			//DirectXのコンポーネント(部品)使用に必要
#pragma comment(lib,"winmm.lib")			//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")			//キーボード処理に必要
#pragma comment(lib,"xinput.lib")			//ジョイパット処理に必要

//マクロ定義
#define CLASS_NAME "WindowsClass"			//ウィンドウクラスの名前
#define WINDOW_NAME "2Dシユーティング"	//ウィンドウの名前
#define SCREEN_WIDTH (1280)					//ウィンドウの幅
#define SCREEN_HEIGHT (720)					//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//画面の種類
typedef enum
{
	MODE_TITLE=0,		//タイトル画面
	MODE_GAME,			//ゲーム画面
	MODE_RESULT,		//リザルト画面
	MODE_CLEAR,			//クリア画面
	MODE_MAX
}MODE;

//頂点情報「２D」の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//座標変換用係数(1.0fで固定)
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
}VERTEX_2D;

//プロトタイプ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd,BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void ToggleFullscreen(HWND hWnd);				// ウィンドウをフルスクリーンにする方法


#endif