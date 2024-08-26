#include "effect.h"
#include "player.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "item.h"

//�}�N��
#define MAX_EFFECT (8000)		//�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nLife;				//����
	float fRadius;			//�傫��
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Effect;

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];						//�G�t�F�N�g        a�͔z��

//������
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0, 0, 0, 0);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffEffect,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
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
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		//�e�N�X�`�����W�̐ݒ�@�@
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//�f�[�^4�i�߂�
	}

	//�A�����b�N
	g_pVteBuffEffect->Unlock();
}
//�I��
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	if (g_pVteBuffEffect != NULL)
	{
		g_pVteBuffEffect->Release();
		g_pVteBuffEffect = NULL;
	}
}
//�X�V
void UpdateEffect(void)
{
	int nCntEffect;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//���_���W�X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			////���_�J���[
			//pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
			//pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
			//pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
			//pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fRadius -= 1.5f;

			if (g_aEffect[nCntEffect].pos.x >= SCREEN_WIDTH - 20 || g_aEffect[nCntEffect].pos.x <= 20 || g_aEffect[nCntEffect].pos.y >= SCREEN_HEIGHT - 20 || g_aEffect[nCntEffect].pos.y <= 20)
			{
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(255, 255, 255, 255));
				g_aEffect[nCntEffect].bUse = false;
			}

			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(255,255,255,255));
				g_aEffect[nCntEffect].bUse = false;
			}
		}
		pVtx += 4;
	}
	//�A�����b�N
	g_pVteBuffEffect->Unlock();

}
//�`�揈��
void DrawEffect(void)
{
	int nCntEffect;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVteBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	// ���Z������߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fRadius)
{
	int nCntEffect;
	VERTEX_2D* pVtx;

	//���b�N
	g_pVteBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			//���_���W�X�V
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_aEffect[nCntEffect].col = col;
			//���_�J���[
			//pVtx[0].col = g_aEffect[nCntEffect].col;
			//pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			//pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			//pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}




	//�A�����b�N
	g_pVteBuffEffect->Unlock();
}