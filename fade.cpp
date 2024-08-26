//--------------------------
// 
//�t�F�[�h�@�C���E�A�E�g
// 
//--------------------------

#include "fade.h"

//�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;					//���_�o�b�t�@�ւ̃|�C���^
FADE g_fade;
MODE g_modeNext;
D3DXCOLOR g_colorFade;

//---------
//������
//---------
void InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(g_colorFade);
	pVtx[1].col = D3DXCOLOR(g_colorFade);
	pVtx[2].col = D3DXCOLOR(g_colorFade);
	pVtx[3].col = D3DXCOLOR(g_colorFade);

	//�A�����b�N
	g_pVtxBuffFade->Unlock();

	//���[�h�ݒ�
	SetMode(g_modeNext);
}
//--------
//�I��
//--------
void UninitFade(void)
{
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

}
//--------
//�X�V
//--------
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			//�t�F�[�h�C��
			g_colorFade.a -= 0.01f;		//�|���S���������ɂȂ鑬��
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;		//�������Ă��Ȃ����
			}
		}
		else if (g_fade == FADE_OUT)
		{
			//�t�F�[�h�A�E�g
			g_colorFade.a += 0.02f;

			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;
				SetMode(g_modeNext);
			}
		}

		VERTEX_2D* pVtx;
		//���b�N
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);

		//�A�����b�N
		g_pVtxBuffFade->Unlock();
	}
}
//---------
//�`��
//---------
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//---------
//�ݒ�
//---------
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}
//----------
// �擾
//----------
FADE GetFade(void)
{
	return g_fade;
}