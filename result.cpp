//-----------------
//リザルト
//------------------
#include "result.h"
#include "input.h"
#include "fade.h"
#include "score.h"

//グローバル
LPDIRECT3DTEXTURE9 g_apTextureResult = 0;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffresult = NULL;		//頂点バッファへのポインタ

void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\result000.png",
		&g_apTextureResult);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffresult,
		NULL);


	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffresult->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定　　１２５
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

}
void UninitResult(void)
{
	if (g_apTextureResult != NULL)
	{
		g_apTextureResult->Release();
		g_apTextureResult = NULL;
	}

	if (g_pVtxBuffresult != NULL)
	{
		g_pVtxBuffresult->Release();
		g_pVtxBuffresult = NULL;
	}
}
void UpdateResult(void)
{
	FADE g_fade;
	g_fade = GetFade();

	if (KeybordTrigger(DIK_RETURN) == true && g_fade == FADE_NONE)
	{//エンターが押されたら
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_TITLE);
	}
	else if (GetJoypadPress(JOYKEY_START) == true && g_fade == FADE_NONE)
	{
		SetFade(MODE_GAME);
	}

}
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffresult, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureResult);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}