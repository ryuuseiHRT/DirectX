#include "main.h"
#include "bkg.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "explosion.h"
#include "effect.h"
#include "game.h"

//ぐろーばる宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffPlayer = NULL;

int g_nCounterAnimPlayer;
int g_nPatternAnimPlayer;

Player g_player = {};
Bullet g_Bullet;
BULLETPOWER BulletPower;

//------------------------
//Playerの初期化処理
//------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\purhu.png",
		&g_pTexturePlayer);

	//初期化
	g_nCounterAnimPlayer = 0;
	g_nPatternAnimPlayer = 0;

	//初期化
	g_player.pos = D3DXVECTOR3(0.0f,500.0f,0.0f);	//位置
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	g_player.bDisp = true;
	g_player.nLife = 5;
	g_player.state = PLAYERSTATE_APPER;
	g_player.nCounterState = 0;
	g_player.nCntLife = 1;

	///対角線の長さを算出
	g_player.fLength = sqrtf(PLAYER_HEIGHT * PLAYER_HEIGHT + PLAYER_WIDTH * PLAYER_WIDTH) / 2.0f;

	//対角線の角度を算出
	g_player.fAngle = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;
	g_pVteBuffPlayer->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;

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

	g_pVteBuffPlayer->Unlock();
}
//---------------------
//Playerの終了処理
//--------------------
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	if (g_pVteBuffPlayer != NULL)
	{
		g_pVteBuffPlayer->Release();
		g_pVteBuffPlayer = NULL;
	}
}
//----------------------
//Playerの更新処理
//-----------------------
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;
	static float fData = 0.2f;

	//Aキーを押した
	if (GetKeyboardPress(DIK_A)== true && g_player.pos.x >= 75)
	{
		fData = 0.2f;
		//Wキーを押した(左上)
		if (GetKeyboardPress(DIK_W) == true&& g_player.pos.y>=75)
		{
			//キー移動
			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 5.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 5.0f;
		}
		//Sキーを押した(左下)
		else if (GetKeyboardPress(DIK_S) == true && g_player.pos.y <= 645)
		{
			//キー移動
			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 5.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 5.0f;
		}
		//Aキーを押した(左)
		else
		{
			g_player.move.x -= 5.0f;

			//キー移動
			//g_posPlayer.x -= g_player.move.x;
		}
	}
	//Dキーを押した
	else if (GetKeyboardPress(DIK_D) == true && g_player.pos.x <= 1205)
	{
		fData = -0.2f;
		//Wキーを押した(右上)
		if (GetKeyboardPress(DIK_W) == true && g_player.pos.y >= 75)
		{
			//キー移動
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 5.0f;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * 5.0f;
		}
		//Sキーを押した(右下)
		else if (GetKeyboardPress(DIK_S) == true && g_player.pos.y <= 645)
		{
			//キー移動
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 5.0f;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 5.0f;
		}
		//Dキーを押した(右)
		else
		{
			g_player.move.x += 5.0f;

			//キー移動
			//g_posPlayer.x += g_player.move.x;
		}
	}
	//Wキーを押した(上)
	else if (GetKeyboardPress(DIK_W) == true && g_player.pos.y >= 80)
	{
		g_player.move.y -= 5.0f;

		//キー移動
		//g_posPlayer.y -= g_player.move.y;
	}
	//Sキーを押した(下)
	else if(GetKeyboardPress(DIK_S) == true && g_player.pos.y <= 640)
	{
		g_player.move.y += 5.0f;
	}
	else if (KeybordTrigger(DIK_Z) == true)
	{//←
		g_player.rot.z += 0.2f;
	}
	else if (GetKeyboardPress(DIK_X) == true)
	{//→
		g_player.rot.z -= 0.2f;
	}
	else if (KeybordTrigger(DIK_UP) == true && g_player.fLength <= 900.0f)
	{//拡大
		g_player.fLength += 150.0f;
	}
	else if (KeybordTrigger(DIK_DOWN) == true && g_player.fLength >= 160.0f)
	{//拡小
		g_player.fLength -= 150.0f;
	}
	else if (KeybordTrigger(DIK_RIGHT) == true)
	{//→90
		g_player.rot.z -= 1.57f;
	}
	else if (KeybordTrigger(DIK_LEFT) == true)
	{//←90
		g_player.rot.z += 1.57f;
	}
	else if (KeybordTrigger(DIK_N) == true)
	{//初期
		g_player.rot.z = 0.0f;
		g_player.fLength = 100.0f;
		g_player.pos.x = 500.0f;
		g_player.pos.y = 500.0f;
	}
	else if (KeybordTrigger(DIK_1) == true)
	{
		g_Bullet.nCntBullet += 1;
		if (g_Bullet.nCntBullet >= 2)
		{
			g_Bullet.nCntBullet = 0;
		}
	}
	else if (KeybordTrigger(DIK_2) == true)
	{
		g_Bullet.nCntBullet -= 1;
		if (g_Bullet.nCntBullet <= 1)
		{
			g_Bullet.nCntBullet = 2;
		}
	}

	
	switch (g_Bullet.nCntBullet)
	{
	case 0:
		if (KeybordTrigger(DIK_SPACE) == true)
		{
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5f) * BULLET_SPEED, cosf(g_player.rot.z + D3DX_PI * 0.5f) * BULLET_SPEED, 0.0f), 100, BULLETTYPE_PLAYER);
		}
		break;
	case 1:
		if (KeybordTrigger(DIK_SPACE) == true)
		{
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5f) * BULLET_SPEED, cosf(g_player.rot.z + D3DX_PI * 0.5f) * BULLET_SPEED, 0.0f), 100, BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.4f) * BULLET_SPEED, cosf(g_player.rot.z + D3DX_PI * 0.4f) * BULLET_SPEED, 0.0f), 100, BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.6f) * BULLET_SPEED, cosf(g_player.rot.z + D3DX_PI * 0.6f) * BULLET_SPEED, 0.0f), 100, BULLETTYPE_PLAYER);
		}
		break;
	default:
		break;
	}

	//=============================================
	// ジョイパッドの入力処理
	//=============================================
	// →
	if (GetJoypadPress(JOYKEY_RIGHT) == true && g_player.pos.x <= 1200)
	{
		// 右上
		if (GetJoypadPress(JOYKEY_UP) == true && g_player.pos.y >= 80)
		{
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 5.0f;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * 5.0f;
		}
		// 右下
		else if (GetJoypadPress(JOYKEY_DOWN) == true && g_player.pos.y <= 640)
		{
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 5.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 5.0f;
		}
		else
		{
			g_player.move.x += 5.0f;
		}
	}
	// ←
	else if (GetJoypadPress(JOYKEY_LEFT) == true && g_player.pos.x >= 80)
	{
		//左上
		if (GetJoypadPress(JOYKEY_UP) == true && g_player.pos.y >= 80)
		{
			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 5.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 5.0f;
		}
		// 左下
		else if (GetJoypadPress(JOYKEY_DOWN) == true && g_player.pos.y <= 640)
		{
			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 5.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 5.0f;

		}
		else
		{
			g_player.move.x -= 5.0f;
		}
	}
	// ↑
	else if (GetJoypadPress(JOYKEY_UP) == true && g_player.pos.y >= 80)
	{
		g_player.move.y -= 5.0f;
	}
	// ↓
	else if (GetJoypadPress(JOYKEY_DOWN) == true && g_player.pos.y <= 640)
	{
		g_player.move.y += 5.0f;
	}
	else if (GetJoypadPress(JOYKEY_BACK) == true)
	{
		SetFade(MODE_GAME);
	}
	else if (JoyPadTrigger(JOYKEY_LB) == true)
	{
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5f) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5f) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
	}
	else if (GetJoypadPress(JOYKEY_RB) == true)
	{
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5f) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5f) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.25f) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.25f) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.75f) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.75f) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
	}

	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//移動量を更新(減衰する)
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.5f;

	//ロック
	g_pVteBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.fAngle)) * g_player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.fAngle)) * g_player.fLength;
	pVtx[3].pos.z = 0.0f;

	int nCntPlayer;
	switch (g_player.state)
	{
	case PLAYERSTATE_NOMAL:
		break;
	case PLAYERSTATE_DAMEGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NOMAL;
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_DETH:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			return;
		}
		break;
	}
	
	pVtx += 4;

	//アンロック
	g_pVteBuffPlayer->Unlock();
}
//--------------------
//Playerの描画処理
//--------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//頂点フォーマットの設定
		pDevice->SetStreamSource(0, g_pVteBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマット設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//
Player* GetPlayer(void)
{
	return &g_player;
}
//
void HitPlayer(int nDamage)
{
	VERTEX_2D* pVtx{};
	g_player.nLife -= nDamage;
	//ロック
	g_pVteBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.nLife <= 0)
	{
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		// パーティクルにしたい！！
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DETH;
		g_player.nCounterState = 60;
		SetFade(MODE_RESULT);
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMEGE;
		g_player.nCounterState = 10;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	}
	//アンロック
	g_pVteBuffPlayer->Unlock();
}