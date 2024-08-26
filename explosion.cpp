#include "explosion.h"
#include "player.h"
#include "main.h"

//�}�N��
#define MAX_EXPLOSION (1024)		//�e�̍ő吔

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffExplosion = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];					// ����

//������
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
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

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffExplosion,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;	//�f�[�^4�i�߂�
	}
	//�A�����b�N
	g_pVteBuffExplosion->Unlock();
}
//�I��
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
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
//�X�V
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_2D* pVtx;
	//���b�N
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
				//�p�^�[���X�V
				g_aExplosion[nCntExplosion].nPttarnAnimExplosion = (g_aExplosion[nCntExplosion].nPttarnAnimExplosion + 1) % 10;

				//���_���W�X�V
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPttarnAnimExplosion * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPttarnAnimExplosion * 0.125f) + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPttarnAnimExplosion * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPttarnAnimExplosion * 0.125f) + 0.125f, 1.0f);
			}
		}
		pVtx += 4;
	}
	//�A�����b�N
	g_pVteBuffExplosion->Unlock();

}
//�`�揈��
void DrawExplosion(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVteBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{

		if (g_aExplosion[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D* pVtx;
	//���b�N
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

			//���_���W�X�V
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50.0f, g_aExplosion[nCntExplosion].pos.y + 50.0f, 0.0f);		
			
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����[�̂��ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	//�A�����b�N
	g_pVteBuffExplosion->Unlock();

}