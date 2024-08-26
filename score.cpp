//========================================
//
// �X�R�A�v�Z���� [sore.cpp]
// Athor : ryuu HRT 
//
//========================================

#include "score.h"

//=====================
// �}�N����`
//====================
#define MAX_SCORE (8)
#define unti (10)

//=====================
// �O���[�o���ϐ�
//=====================
//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureScore = NULL;		
//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;

//�X�R�A�̈ʒu
D3DXVECTOR3 g_posScore;
//�X�R�A�̒l
int g_nScore;

//�X�R�A�^�̃O���[�o���ϐ�
Score g_aScore[MAX_SCORE];

//*********************
// ����������
//*********************
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �X�R�A�̈ʒu
	g_posScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�X�R�A�̒l
	g_nScore = 0;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\sucore000.png",
		&g_apTextureScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f + (nCnt * 50.0f), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + (nCnt * 50.0f), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + (nCnt * 50.0f), 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + (nCnt * 50.0f), 50.0f, 0.0f);

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

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		// �厖
		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffScore->Unlock();
}
//*********************
// �I������
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
// �X�V����
//*********************
void UpdateScore(void)
{
	int nData;//�����ۑ��p�̃��[�J���ϐ�
	int nData1 = 0;//���[�J���ϐ�

	//���߂��X�R�A�̌�����ۑ�
	nData = ScoreCounter(g_nScore);
	for (nData1 = 0; nData1 < MAX_SCORE; nData1++)
	{

		if (nData1 >= MAX_SCORE - nData)
		{
			//MAX_NUM_SCORE - nData��0���\������Ă��鎞(nData1��茅���̒l���������Ƃ�)
			g_aScore[nData1].bUse = true;//��̏�����L��������
		}
		else
		{
			//����ȊO�̏�Ԃ̎�
			g_aScore[nData1].bUse = false;
		}
	}
}
//*********************
// �`�揈��
//*********************
void DrawScore(void)
{
	//�f���@�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (g_aScore[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureScore);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
//*********************
// �X�R�A�ݒ菈��
//*********************
void SetScore(int nScore)
{
	//�e���̐������i�[
	int aPosTexU[8] = { NULL };
	g_nScore = nScore;
}
//*********************
// �X�R�A���Z����
//*********************
void AddScore(int nValue)
{
	//�e���̐������i�[
	int aPosTexU[8] = { NULL };

	int cData = 100000000;
	int bData = 10000000;

	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	g_nScore += nValue;

	for (int nCnt = 0; nCnt <MAX_SCORE; nCnt++)
	{
		aPosTexU[nCnt] = g_nScore % cData / bData;
		cData = cData / unti;
		bData = bData / unti;
		// �厖
	}
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{//�e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffScore->Unlock();
}
//=====================
//�X�R�A��0���J�E���g
//=====================
int  ScoreCounter(int nScore)
{
	int nNum = nScore;//�X�R�A�̂O�̕������J�E���g
	int nKeepNum = 0;//�X�R�A�̌���

	while (nNum != 0)//����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�(�O�܂�)
	{
		nNum /= 10;//nNum��10�Ŋ����Ă���
		nKeepNum++;//���������Z

	}
	if (nScore == 0)
	{
		//1���ڂ�0�������Ă���Ƃ�
		nKeepNum = 1;
	}
	return nKeepNum;//�X�R�A�̌�����Ԃ�
}
//=====================
// ���݂̃X�R�A
//=====================
Score* GetScore(void)
{
	return &g_aScore[0];
}