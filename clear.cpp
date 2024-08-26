//-----------------
//�Q�[���N���A
//------------------
#include "clear.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "score.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureClear = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffClear = NULL;		//���_�o�b�t�@�ւ̃|�C���^

void InitClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\clear000.png",
		&g_apTextureClear);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffClear,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffClear->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVtxBuffClear->Unlock();

	//�T�E���h�Đ�
	//PlaySound(///)
}
void UninitClear(void)
{
	if (g_apTextureClear != NULL)
	{
		g_apTextureClear->Release();
		g_apTextureClear = NULL;
	}

	if (g_pVtxBuffClear != NULL)
	{
		g_pVtxBuffClear->Release();
		g_pVtxBuffClear = NULL;
	}
}
void UpdateClear(void)
{
	FADE g_fade;
	g_fade = GetFade();

	if (KeybordTrigger(DIK_RETURN) == true && g_fade == FADE_NONE)
	{//�G���^�[�������ꂽ��
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_TITLE);
		//DestroyWindow(hWnd);
	}
	else if (GetJoypadPress(JOYKEY_START) == true && g_fade == FADE_NONE)
	{
		SetFade(MODE_TITLE);
	}
}
void DrawClear(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffClear, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureClear);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}