//--------------------------
// 
//フェード　イン・アウト
// 
//--------------------------

#include "fade.h"

//グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;					//頂点バッファへのポインタ
FADE g_fade;
MODE g_modeNext;
D3DXCOLOR g_colorFade;

//---------
//初期化
//---------
void InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(g_colorFade);
	pVtx[1].col = D3DXCOLOR(g_colorFade);
	pVtx[2].col = D3DXCOLOR(g_colorFade);
	pVtx[3].col = D3DXCOLOR(g_colorFade);

	//アンロック
	g_pVtxBuffFade->Unlock();

	//モード設定
	SetMode(g_modeNext);
}
//--------
//終了
//--------
void UninitFade(void)
{
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

}
//--------
//更新
//--------
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			//フェードイン
			g_colorFade.a -= 0.01f;		//ポリゴンが透明になる速さ
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;		//何もしていない状態
			}
		}
		else if (g_fade == FADE_OUT)
		{
			//フェードアウト
			g_colorFade.a += 0.02f;

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;
				SetMode(g_modeNext);
			}
		}

		VERTEX_2D* pVtx;
		//ロック
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);

		//アンロック
		g_pVtxBuffFade->Unlock();
	}
}
//---------
//描画
//---------
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//---------
//設定
//---------
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//----------
// 取得
//----------
FADE GetFade(void)
{
	return g_fade;
}