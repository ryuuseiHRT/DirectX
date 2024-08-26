#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef enum
{
	PLAYERSTATE_APPER = 0,	// 出現
	PLAYERSTATE_NOMAL,		// 通常
	PLAYERSTATE_DAMEGE,		// ダメージ
	PLAYERSTATE_DETH,		// 死亡
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	float fLength;
	float fAngle;
	PLAYERSTATE state;
	int nCounterState;
	int nLife;
	bool bDisp;	// 表示するか
	int nCntLife;
}Player;

//プロトタイプ
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);

#define PLAYER_HEIGHT (150)		//高さ
#define PLAYER_WIDTH (150)		//幅

#endif