#include "bullet.h"
#include "player.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "item.h"
#include "effect.h"

//�}�N��
#define MAX_BULLET (1024)		//�e�̍ő吔

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e

//������
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
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

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffBullet,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;	//�f�[�^4�i�߂�
	}

	//�A�����b�N
	g_pVteBuffBullet->Unlock();
}
//�I��
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
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
//�X�V
void UpdateBullet(void)
{
	int nCntBullet;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	VERTEX_2D* pVtx;
	//���b�N
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

			//�ʒu���X�V
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			//���_���W�X�V
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
	//�A�����b�N
	g_pVteBuffBullet->Unlock();

}
//�`�揈��
void DrawBullet(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVteBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife,BULLETTYPE nType)
{
	int nCntBullet;
	VERTEX_2D* pVtx;

	//���b�N
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

			//���_���W�X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 70.0f, g_aBullet[nCntBullet].pos.y - 70.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 70.0f, g_aBullet[nCntBullet].pos.y - 70.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 70.0f, g_aBullet[nCntBullet].pos.y + 70.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 70.0f, g_aBullet[nCntBullet].pos.y + 70.0f, 0.0f);
			break;
		}
		pVtx += 4;
	}

	//�A�����b�N
	g_pVteBuffBullet->Unlock();
}