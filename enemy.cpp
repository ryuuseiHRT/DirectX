//-------------------------------------------------------
//敵
//-------------------------------------------------------
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "item.h"

//マクロ
#define NUM_ENEMY (4)		//敵の種類

//ぐろーばる
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = { NULL };		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										//敵
int g_NumEnemy = 0;

//------------------
//初期化
//-----------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイス取得
	pDevice = GetDevice();

	//てくすちゃ　４回
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\enemy001.png",
		&g_apTextureEnemy[ENEMYTYPE_ONE]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\tyuigt.jpeg",
		&g_apTextureEnemy[ENEMYTYPE_TWO]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\enemy001.png",
		&g_apTextureEnemy[ENEMYTYPE_THREE]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\enemy001.png",
		&g_apTextureEnemy[ENEMYTYPE_FOUR]);

	//敵の情報の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nTypr = ENEMYTYPE_ONE;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 10;
		g_aEnemy[nCntEnemy].nCntS = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].KillCounter = 0;
	}
	g_NumEnemy = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//座標
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//ｒｈｗ
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

		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffEnemy->Unlock();
}
//終了
void UninitEnemy(void)
{
	int nCntEnemy;
	//テクスチャの破棄 
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//更新
void UpdateEnemy(void)
{
	//なんでもいいエラー以外
	int nCntEnemy;
	VERTEX_2D* pVtx;
	// ロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	
			g_aEnemy[nCntEnemy].nCntS++;

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				if (g_aEnemy[nCntEnemy].nCntS > 60)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 10, BULLETTYPE_ENEMY);
					g_aEnemy[nCntEnemy].nCntS = 0;
				}
				break;
			case ENEMYSTATE_DAMEGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
					//頂点カラー
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				break;
			}
		}
		pVtx += 4;
	}
	// アンロック
	g_pVtxBuffEnemy->Unlock();

}
//描画
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイス取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].nTypr)
			{
			case ENEMYTYPE_ONE:
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureEnemy[ENEMYTYPE_ONE]);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
				break;
			case ENEMYTYPE_TWO:
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureEnemy[ENEMYTYPE_TWO]);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
				break;
			case ENEMYTYPE_THREE:
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureEnemy[ENEMYTYPE_THREE]);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
				break;
			case ENEMYTYPE_FOUR:
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureEnemy[ENEMYTYPE_FOUR]);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
				break;
			default:
				break;
			}
		}
	}
}
//敵の設定処理
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].nTypr == ENEMYTYPE_ONE)
		{
			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				//敵の情報設定（構造体
				g_aEnemy[nCntEnemy].pos = pos;
				g_aEnemy[nCntEnemy].nTypr = nType;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
				g_aEnemy[nCntEnemy].nCounterState = 0;
				g_aEnemy[nCntEnemy].nLife = 5;
				g_aEnemy[nCntEnemy].bUse = true;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

				//頂点カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				
			}
			pVtx += 4;
			g_NumEnemy++;	//敵の総数カウントアップ
			break;
		}
		else if (g_aEnemy[nCntEnemy].nTypr == ENEMYTYPE_TWO)
		{
			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				//敵の情報設定（構造体
				g_aEnemy[nCntEnemy].pos = pos;
				g_aEnemy[nCntEnemy].nTypr = nType;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
				g_aEnemy[nCntEnemy].nCounterState = 0;
				g_aEnemy[nCntEnemy].nLife = 5;
				g_aEnemy[nCntEnemy].bUse = true;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

				//頂点カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			pVtx += 4;
			g_NumEnemy++;	//敵の総数カウントアップ
			break;
		}
		else if (g_aEnemy[nCntEnemy].nTypr == ENEMYTYPE_THREE)
		{
			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				//敵の情報設定（構造体
				g_aEnemy[nCntEnemy].pos = pos;
				g_aEnemy[nCntEnemy].nTypr = nType;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
				g_aEnemy[nCntEnemy].nCounterState = 0;
				g_aEnemy[nCntEnemy].nLife = 5;
				g_aEnemy[nCntEnemy].bUse = true;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

				//頂点カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			pVtx += 4;
			g_NumEnemy++;	//敵の総数カウントアップ
			break;
		}
		else if (g_aEnemy[nCntEnemy].nTypr == ENEMYTYPE_FOUR)
		{
			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				//敵の情報設定（構造体
				g_aEnemy[nCntEnemy].pos = pos;
				g_aEnemy[nCntEnemy].nTypr = nType;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
				g_aEnemy[nCntEnemy].nCounterState = 0;
				g_aEnemy[nCntEnemy].nLife = 5;
				g_aEnemy[nCntEnemy].bUse = true;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

				//頂点カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			pVtx += 4;
			g_NumEnemy++;	//敵の総数カウントアップ
			break;
		}
	}
	//アンロック
	g_pVtxBuffEnemy->Unlock();
}
//
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx{};
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	//ロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy->KillCounter++;

		switch (g_aEnemy->KillCounter)
		{
		case 1:
		case 2:
		//case 3:
		//case 4:
		//case 5:
			SetItem(g_aEnemy[nCntEnemy].pos, ITEMTYPE_ONE);
			break;
		case 3:
		case 4:
		//case 8:
		//case 9:
		//case 10:
			SetItem(g_aEnemy[nCntEnemy].pos, ITEMTYPE_TWO);
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			SetItem(g_aEnemy[nCntEnemy].pos, ITEMTYPE_ONE);
			break;
		default:
			break;
		}
		// 敵を倒した時のスコア加算
		AddScore(50);
		g_NumEnemy--;	//敵の総数カウントダウン
	}
	else
	{
   		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;
		pVtx += 4 * nCntEnemy; //初期値がないのでエラーの危険性がある

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	}
	//アンロック
	g_pVtxBuffEnemy->Unlock();
}
int GeetNumEnemy()
{
	return g_NumEnemy;
}
//敵の取得
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];			//敵の情報の先頭アドレスを返す
}
