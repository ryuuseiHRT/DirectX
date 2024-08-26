//========================================
//
// スコア計算処理 [sore.cpp]
// Athor : ryuu HRT 
//
//========================================

#include "score.h"

//=====================
// マクロ定義
//====================
#define MAX_SCORE (8)
#define unti (10)

//=====================
// グローバル変数
//=====================
//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureScore = NULL;		
//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;

//スコアの位置
D3DXVECTOR3 g_posScore;
//スコアの値
int g_nScore;

//スコア型のグローバル変数
Score g_aScore[MAX_SCORE];

//*********************
// 初期化処理
//*********************
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// スコアの位置
	g_posScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//スコアの値
	g_nScore = 0;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\sucore000.png",
		&g_apTextureScore);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f + (nCnt * 50.0f), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + (nCnt * 50.0f), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + (nCnt * 50.0f), 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + (nCnt * 50.0f), 50.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		// 大事
		pVtx += 4;
	}

	//アンロック
	g_pVtxBuffScore->Unlock();
}
//*********************
// 終了処理
//*********************
void UninitScore(void)
{
	if (g_apTextureScore != NULL)
	{
		g_apTextureScore->Release();
		g_apTextureScore = NULL;
	}

	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//*********************
// 更新処理
//*********************
void UpdateScore(void)
{
	int nData;//桁数保存用のローカル変数
	int nData1 = 0;//ローカル変数

	//求めたスコアの桁数を保存
	nData = ScoreCounter(g_nScore);
	for (nData1 = 0; nData1 < MAX_SCORE; nData1++)
	{

		if (nData1 >= MAX_SCORE - nData)
		{
			//MAX_NUM_SCORE - nDataで0が表示されている時(nData1より桁数の値が小さいとき)
			g_aScore[nData1].bUse = true;//上の条件を有効化する
		}
		else
		{
			//それ以外の状態の時
			g_aScore[nData1].bUse = false;
		}
	}
}
//*********************
// 描画処理
//*********************
void DrawScore(void)
{
	//デヴァイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (g_aScore[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureScore);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//*********************
// スコア設定処理
//*********************
void SetScore(int nScore)
{
	//各桁の数字を格納
	int aPosTexU[8] = { NULL };
	g_nScore = nScore;
}
//*********************
// スコア加算処理
//*********************
void AddScore(int nValue)
{
	//各桁の数字を格納
	int aPosTexU[8] = { NULL };

	int cData = 100000000;
	int bData = 10000000;

	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	g_nScore += nValue;

	for (int nCnt = 0; nCnt <MAX_SCORE; nCnt++)
	{
		aPosTexU[nCnt] = g_nScore % cData / bData;
		cData = cData / unti;
		bData = bData / unti;
		// 大事
	}
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{//テクスチャ座標の更新
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx += 4;
	}
	//アンロック
	g_pVtxBuffScore->Unlock();
}
//=====================
//スコアの0をカウント
//=====================
int  ScoreCounter(int nScore)
{
	int nNum = nScore;//スコアの０の部分をカウント
	int nKeepNum = 0;//スコアの桁数

	while (nNum != 0)//割り切れなくなるまで繰り返す(０まで)
	{
		nNum /= 10;//nNumを10で割っていく
		nKeepNum++;//桁数を加算

	}
	if (nScore == 0)
	{
		//1桁目に0が入っているとき
		nKeepNum = 1;
	}
	return nKeepNum;//スコアの桁数を返す
}
//=====================
// 現在のスコア
//=====================
Score* GetScore(void)
{
	return &g_aScore[0];
}