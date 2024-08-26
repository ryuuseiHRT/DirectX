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

//����[�΂�錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffPlayer = NULL;

int g_nCounterAnimPlayer;
int g_nPatternAnimPlayer;

Player g_player = {};
Bullet g_Bullet;
BULLETPOWER BulletPower;

//------------------------
//Player�̏���������
//------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\purhu.png",
		&g_pTexturePlayer);

	//������
	g_nCounterAnimPlayer = 0;
	g_nPatternAnimPlayer = 0;

	//������
	g_player.pos = D3DXVECTOR3(0.0f,500.0f,0.0f);	//�ʒu
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	g_player.bDisp = true;
	g_player.nLife = 5;
	g_player.state = PLAYERSTATE_APPER;
	g_player.nCounterState = 0;
	g_player.nCntLife = 1;

	///�Ίp���̒������Z�o
	g_player.fLength = sqrtf(PLAYER_HEIGHT * PLAYER_HEIGHT + PLAYER_WIDTH * PLAYER_WIDTH) / 2.0f;

	//�Ίp���̊p�x���Z�o
	g_player.fAngle = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//���_�o�b�t�@�̐���
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

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�@�@
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVteBuffPlayer->Unlock();
}
//---------------------
//Player�̏I������
//--------------------
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
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
//Player�̍X�V����
//-----------------------
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;
	static float fData = 0.2f;

	//A�L�[��������
	if (GetKeyboardPress(DIK_A)== true && g_player.pos.x >= 75)
	{
		fData = 0.2f;
		//W�L�[��������(����)
		if (GetKeyboardPress(DIK_W) == true&& g_player.pos.y>=75)
		{
			//�L�[�ړ�
			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 5.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 5.0f;
		}
		//S�L�[��������(����)
		else if (GetKeyboardPress(DIK_S) == true && g_player.pos.y <= 645)
		{
			//�L�[�ړ�
			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 5.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 5.0f;
		}
		//A�L�[��������(��)
		else
		{
			g_player.move.x -= 5.0f;

			//�L�[�ړ�
			//g_posPlayer.x -= g_player.move.x;
		}
	}
	//D�L�[��������
	else if (GetKeyboardPress(DIK_D) == true && g_player.pos.x <= 1205)
	{
		fData = -0.2f;
		//W�L�[��������(�E��)
		if (GetKeyboardPress(DIK_W) == true && g_player.pos.y >= 75)
		{
			//�L�[�ړ�
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 5.0f;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * 5.0f;
		}
		//S�L�[��������(�E��)
		else if (GetKeyboardPress(DIK_S) == true && g_player.pos.y <= 645)
		{
			//�L�[�ړ�
			g_player.move.x += sinf(D3DX_PI * 0.25f) * 5.0f;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * 5.0f;
		}
		//D�L�[��������(�E)
		else
		{
			g_player.move.x += 5.0f;

			//�L�[�ړ�
			//g_posPlayer.x += g_player.move.x;
		}
	}
	//W�L�[��������(��)
	else if (GetKeyboardPress(DIK_W) == true && g_player.pos.y >= 80)
	{
		g_player.move.y -= 5.0f;

		//�L�[�ړ�
		//g_posPlayer.y -= g_player.move.y;
	}
	//S�L�[��������(��)
	else if(GetKeyboardPress(DIK_S) == true && g_player.pos.y <= 640)
	{
		g_player.move.y += 5.0f;
	}
	else if (KeybordTrigger(DIK_Z) == true)
	{//��
		g_player.rot.z += 0.2f;
	}
	else if (GetKeyboardPress(DIK_X) == true)
	{//��
		g_player.rot.z -= 0.2f;
	}
	else if (KeybordTrigger(DIK_UP) == true && g_player.fLength <= 900.0f)
	{//�g��
		g_player.fLength += 150.0f;
	}
	else if (KeybordTrigger(DIK_DOWN) == true && g_player.fLength >= 160.0f)
	{//�g��
		g_player.fLength -= 150.0f;
	}
	else if (KeybordTrigger(DIK_RIGHT) == true)
	{//��90
		g_player.rot.z -= 1.57f;
	}
	else if (KeybordTrigger(DIK_LEFT) == true)
	{//��90
		g_player.rot.z += 1.57f;
	}
	else if (KeybordTrigger(DIK_N) == true)
	{//����
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
	// �W���C�p�b�h�̓��͏���
	//=============================================
	// ��
	if (GetJoypadPress(JOYKEY_RIGHT) == true && g_player.pos.x <= 1200)
	{
		// �E��
		if (GetJoypadPress(JOYKEY_UP) == true && g_player.pos.y >= 80)
		{
			g_player.move.x += sinf(D3DX_PI * 0.75f) * 5.0f;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * 5.0f;
		}
		// �E��
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
	// ��
	else if (GetJoypadPress(JOYKEY_LEFT) == true && g_player.pos.x >= 80)
	{
		//����
		if (GetJoypadPress(JOYKEY_UP) == true && g_player.pos.y >= 80)
		{
			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 5.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 5.0f;
		}
		// ����
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
	// ��
	else if (GetJoypadPress(JOYKEY_UP) == true && g_player.pos.y >= 80)
	{
		g_player.move.y -= 5.0f;
	}
	// ��
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

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//�ړ��ʂ��X�V(��������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.5f;

	//���b�N
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
			//���_�J���[
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

	//�A�����b�N
	g_pVteBuffPlayer->Unlock();
}
//--------------------
//Player�̕`�揈��
//--------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetStreamSource(0, g_pVteBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�|���S���̕`��
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
	//���b�N
	g_pVteBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.nLife <= 0)
	{
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		// �p�[�e�B�N���ɂ������I�I
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DETH;
		g_player.nCounterState = 60;
		SetFade(MODE_RESULT);
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMEGE;
		g_player.nCounterState = 10;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	}
	//�A�����b�N
	g_pVteBuffPlayer->Unlock();
}