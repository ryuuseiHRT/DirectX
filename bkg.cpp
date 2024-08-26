//-------------------
//背景
//-------------------

#include "main.h"
#include "bkg.h"
#include "player.h"

//マクロ
#define NUM_BG (3)			//背景の数

//ぐろーばる宣言
LPDIRECT3DTEXTURE9 g_apTextureBkg[NUM_BG] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffBkg;
float g_aPosTexU[NUM_BG];		//テクスチャ座標の開始位置（U値）

//--------------
//初期化
//-------------
void InitBkg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBG;

	//テクスチャの読み込み  1
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bkg000.jpg",
		&g_apTextureBkg[0]);

	//
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bkg000.jpg",
		&g_apTextureBkg[1]);

	//
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bkg001.jpg",
		&g_apTextureBkg[2]);

	//テクスチャ座標の開始位置の初期化
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] = 0.0f;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffBkg,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVteBuffBkg->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
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
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;		//これ大事
	}
	g_pVteBuffBkg->Unlock();
}
//-----------
//終了
//-----------
void UninitBkg(void)
{
	int nCntBG;
	//テクスチャの破棄 
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_apTextureBkg[nCntBG] != NULL)
		{
			g_apTextureBkg[nCntBG]->Release();
			g_apTextureBkg[nCntBG] = NULL;
		}
	}

	if (g_pVteBuffBkg != NULL)
	{
		g_pVteBuffBkg->Release();
		g_pVteBuffBkg = NULL;
	}
}
//==============================
// 更新処理
//==============================
void UpdateBkg(void)
{
	int nCntBG;
	VERTEX_2D* pVtx;
	//ロック
	g_pVteBuffBkg->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] += 0.0005f * nCntBG+1;
		//テクスチャ座標の設定　　１２５
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		//テクスチャの座標更新
		//g_aPosTexU[nCntBG] = 0.0f;
		pVtx += 4;		//これ大事
	}
	//アンロック
	g_pVteBuffBkg->Unlock();
}
void DrawBkg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBG;

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVteBuffBkg, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBkg[nCntBG]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  nCntBG * 4, 2);
	}
}