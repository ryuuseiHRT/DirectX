#include "explosion.h"
#include "player.h"
#include "main.h"

//マクロ
#define MAX_EXPLOSION (1024)		//弾の最大数

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffExplosion = NULL;		// 頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];					// 爆発

//初期化
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\explosion001.png",
		&g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(255,255,255,255);
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
		g_aExplosion[nCntExplosion].nPttarnAnimExplosion = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffExplosion,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVteBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		//テクスチャ座標の設定　　
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;	//データ4つ進める
	}
	//アンロック
	g_pVteBuffExplosion->Unlock();
}
//終了
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	if (g_pVteBuffExplosion != NULL)
	{
		g_pVteBuffExplosion->Release();
		g_pVteBuffExplosion = NULL;
	}
}
//更新
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_2D* pVtx;
	//ロック
	g_pVteBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounterAnimExplosion++;

			if (g_aExplosion[nCntExplosion].nPttarnAnimExplosion >= 8)
			{
				g_aExplosion[nCntExplosion].nPttarnAnimExplosion = 0;
				g_aExplosion[nCntExplosion].bUse = false;
			}

			if ((g_aExplosion[nCntExplosion].nCounterAnimExplosion % 5) == 0)
			{
				g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
				//パターン更新
				g_aExplosion[nCntExplosion].nPttarnAnimExplosion = (g_aExplosion[nCntExplosion].nPttarnAnimExplosion + 1) % 10;

				//頂点座標更新
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPttarnAnimExplosion * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPttarnAnimExplosion * 0.125f) + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPttarnAnimExplosion * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPttarnAnimExplosion * 0.125f) + 0.125f, 1.0f);
			}
		}
		pVtx += 4;
	}
	//アンロック
	g_pVteBuffExplosion->Unlock();

}
//描画処理
void DrawExplosion(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVteBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{

		if (g_aExplosion[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D* pVtx;
	//ロック
	g_pVteBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].nCounterAnimExplosion = 0;
			g_aExplosion[nCntExplosion].nPttarnAnimExplosion = 0;
			g_aExplosion[nCntExplosion].bUse = true;

			//頂点座標更新
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);		
			
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャぁ票のお設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//アンロック
	g_pVteBuffExplosion->Unlock();

}