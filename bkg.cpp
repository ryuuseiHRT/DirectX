//-------------------
//�w�i
//-------------------

#include "main.h"
#include "bkg.h"
#include "player.h"

//�}�N��
#define NUM_BG (3)			//�w�i�̐�

//����[�΂�錾
LPDIRECT3DTEXTURE9 g_apTextureBkg[NUM_BG] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffBkg;
float g_aPosTexU[NUM_BG];		//�e�N�X�`�����W�̊J�n�ʒu�iU�l�j

//--------------
//������
//-------------
void InitBkg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBG;

	//�e�N�X�`���̓ǂݍ���  1
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bkg000.jpg",
		&g_apTextureBkg[0]);

	//
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bkg000.jpg",
		&g_apTextureBkg[1]);

	//
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\bkg001.jpg",
		&g_apTextureBkg[2]);

	//�e�N�X�`�����W�̊J�n�ʒu�̏�����
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] = 0.0f;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffBkg,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffBkg->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�@�@�P�Q�T
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;		//����厖
	}
	g_pVteBuffBkg->Unlock();
}
//-----------
//�I��
//-----------
void UninitBkg(void)
{
	int nCntBG;
	//�e�N�X�`���̔j�� 
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_apTextureBkg[nCntBG] != NULL)
		{
			g_apTextureBkg[nCntBG]->Release();
			g_apTextureBkg[nCntBG] = NULL;
		}
	}

	if (g_pVteBuffBkg != NULL)
	{
		g_pVteBuffBkg->Release();
		g_pVteBuffBkg = NULL;
	}
}
//==============================
// �X�V����
//==============================
void UpdateBkg(void)
{
	int nCntBG;
	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffBkg->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] += 0.0005f * nCntBG+1;
		//�e�N�X�`�����W�̐ݒ�@�@�P�Q�T
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		//�e�N�X�`���̍��W�X�V
		//g_aPosTexU[nCntBG] = 0.0f;
		pVtx += 4;		//����厖
	}
	//�A�����b�N
	g_pVteBuffBkg->Unlock();
}
void DrawBkg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBG;

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVteBuffBkg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBkg[nCntBG]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  nCntBG * 4, 2);
	}
}