#include "bullet.h"
#include "player.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "item.h"
#include "effect.h"

//マクロ
#define MAX_BULLET (1024)		//弾の最大数

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffBullet = NULL;	//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾

//初期化
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\effect3.png",
		&g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffBullet,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVteBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//データ4つ進める
	}

	//アンロック
	g_pVteBuffBullet->Unlock();
}
//終了
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	if (g_pVteBuffBullet != NULL)
	{
		g_pVteBuffBullet->Release();
		g_pVteBuffBullet = NULL;
	}
}
//更新
void UpdateBullet(void)
{
	int nCntBullet;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	VERTEX_2D* pVtx;
	//ロック
	g_pVteBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER || g_aBullet[nCntBullet].type == BULLETTYE_ITEM)
			{
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f,1.0f,0.0f,1.0f), 15, 30);
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f,1.0f,0.0f,1.0f), 10, 10);
			}
			int nCntEnemy;

 			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER || g_aBullet[nCntBullet].type == BULLETTYE_ITEM)
			{
				Enemy* pEnemy;
				pEnemy = GetEnemy();
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - 50
							&& g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - 50
							&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + 50)
						{
							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
					pEnemy++;
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				int nCntPlayer;
				Player* pPlayer;
				pPlayer = GetPlayer();
				for (nCntPlayer = 0; nCntPlayer < 1; nCntPlayer++)
				{
					if (pPlayer->bDisp == true)
					{
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - 50
							&& g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - 50
							&& g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + 50)
						{
							HitPlayer(1);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				ITEM* pItem;
				pItem = GetItem();
				int nItem;
				for (nItem = 0; nItem < MAX_ITEM; nItem++)
				{
					if (pItem->bUse == true)
					{
						if (g_aBullet[nCntBullet].pos.x >= pItem->pos.x - 50
							&& g_aBullet[nCntBullet].pos.x <= pItem->pos.x + 50
							&& g_aBullet[nCntBullet].pos.y >= pItem->pos.y - 50
							&& g_aBullet[nCntBullet].pos.y <= pItem->pos.y + 50)
						{
							HitItem(nItem, 1);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}

			//位置を更新
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			//頂点座標更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 70.0f, g_aBullet[nCntBullet].pos.y - 70.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 70.0f, g_aBullet[nCntBullet].pos.y - 70.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 70.0f, g_aBullet[nCntBullet].pos.y + 70.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 70.0f, g_aBullet[nCntBullet].pos.y + 70.0f, 0.0f);
			g_aBullet[nCntBullet].nLife--;

			if (g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH - 20 || g_aBullet[nCntBullet].pos.x <= 20|| g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT - 20 || g_aBullet[nCntBullet].pos.y <= 20)
			{
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(255, 255, 255, 255));
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(255,255,255,255));
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		pVtx += 4;
	}
	//アンロック
	g_pVteBuffBullet->Unlock();

}
//描画処理
void DrawBullet(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVteBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife,BULLETTYPE nType)
{
	int nCntBullet;
	VERTEX_2D* pVtx;

	//ロック
	g_pVteBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = nType;
			g_aBullet[nCntBullet].nLife = 2000;
			g_aBullet[nCntBullet].bUse = true;

			//頂点座標更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 70.0f, g_aBullet[nCntBullet].pos.y - 70.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 70.0f, g_aBullet[nCntBullet].pos.y - 70.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 70.0f, g_aBullet[nCntBullet].pos.y + 70.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 70.0f, g_aBullet[nCntBullet].pos.y + 70.0f, 0.0f);
			break;
		}
		pVtx += 4;
	}

	//アンロック
	g_pVteBuffBullet->Unlock();
}