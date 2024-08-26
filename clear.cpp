//-----------------
//ゲームクリア
//------------------
#include "clear.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "score.h"

//グローバル
LPDIRECT3DTEXTURE9 g_apTextureClear = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;		//頂点バッファへのポインタ

void InitClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\clear000.png",
		&g_apTextureClear);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffClear,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定　　１２５
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//アンロック
	g_pVtxBuffClear->Unlock();

	//サウンド再生
	//PlaySound(///)
}
void UninitClear(void)
{
	if (g_apTextureClear != NULL)
	{
		g_apTextureClear->Release();
		g_apTextureClear = NULL;
	}

	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}
}
void UpdateClear(void)
{
	FADE g_fade;
	g_fade = GetFade();

	if (KeybordTrigger(DIK_RETURN) == true && g_fade == FADE_NONE)
	{//エンターが押されたら
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_TITLE);
		//DestroyWindow(hWnd);
	}
	else if (GetJoypadPress(JOYKEY_START) == true && g_fade == FADE_NONE)
	{
		SetFade(MODE_TITLE);
	}
}
void DrawClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureClear);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}