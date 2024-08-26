//-----------------
//�^�C�g��
//------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

// �}�O��
#define MAX_TITLE (2)

// �\����
//�^�C�g���\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���W
	D3DXVECTOR3 col;	// �J���[
	int nType;			// ���
	bool bUse;			// �g���Ă邩
	float fHeight;		// ����
	float fWidth;		// ��
	TITLEMODE state;	// ���
}Title;

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TITLE] = { NULL };			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
Title g_aTitle[MAX_TITLE];											// �^�C�g���\���̂̏��
TITLE g_Title;														// �^�C�g���񋓌^�̏��
int g_nCntTitleAnim;												// �^�C�g�����
int g_nPatternAnim;													// ��ԃp�^�[��

void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ��� 
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\grgdl.jpeg",
		&g_apTextureTitle[0]);

	//�e�N�X�`���̓ǂݍ���  2
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\title001.png",
		&g_apTextureTitle[1]);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].nType = 0;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].state = TITLEMODE_NONE;//�������Ă��Ȃ����
	}
	g_nCntTitleAnim = 0;
	g_nPatternAnim = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//���_���W�̐ݒ�
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

		//�e�N�X�`�����W�̐ݒ�@�@�P�Q�T
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		// �厖����������������������������
	}

	SetTitle(TITLE_ONE, D3DXVECTOR3(650.0f, 300.0f, 0.0f));//�^�C�g��1
	SetTitle(TITLE_TWO, D3DXVECTOR3(650.0f, 600.0f, 0.0f));//�^�C�g��2

	//�A�����b�N
	g_pVtxBuffTitle->Unlock();

	//�T�E���h�Đ�
	//PlaySound(///)
}
void UninitTitle(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
void UpdateTitle(void)
{
	GetFade();//�t�F�[�h�̎擾

	FADE g_fade = GetFade();//���݂̏��

	if (KeybordTrigger(DIK_RETURN) == true)
	{
		//Enter�L�[�������ꂽ
		for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
		{
			if (g_aTitle[nCntTitle].bUse == true && g_aTitle[nCntTitle].nType == TITLE_TWO)
			{
				g_aTitle[nCntTitle].state = TITLEMODE_FLASH;
			}
		}
		//���[�h�ݒ�(�`���[�g���A����ʂɈړ�)
		SetFade(MODE_GAME);
	}
	else if (JoyPadTrigger(JOYKEY_START) == true)
	{
		//start�������ꂽ
		//���[�h�ݒ�(�`���[�g���A����ʂɈړ�)
		for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
		{
			if (g_aTitle[nCntTitle].bUse == true && g_aTitle[nCntTitle].nType == TITLE_TWO)
			{
				g_aTitle[nCntTitle].state = TITLEMODE_FLASH;
			}
		}
		//���[�h�ݒ�(�`���[�g���A����ʂɈړ�)
		SetFade(MODE_GAME);
	}

	TitleFlash(TITLE_TWO);//�^�C�g���̓_��
}
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTitle[g_aTitle[nCnt].nType]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].nType = nType;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].bUse = true;

			//�ꍇ����
			switch (nType)
			{
			case TITLE_ONE:

				g_aTitle[nCntTitle].fHeight = 600.0f;//����
				g_aTitle[nCntTitle].fWidth = 700.0f;//����
				break;

			case TITLE_TWO:

				g_aTitle[nCntTitle].fHeight = 100.0f;//����
				g_aTitle[nCntTitle].fWidth = 870.0f; //����
				break;
			}

			//���_���W1�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);//4�ڂ̒��_���

			break;
		}
		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffTitle->Unlock();
}
void TitleFlash(int nType)
{
	VERTEX_2D* pVtx = 0;//���_���̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true && g_aTitle[nCntTitle].state == TITLEMODE_FLASH)
		{
			g_nCntTitleAnim++;//�J�E���^�[�����Z

			if (g_nCntTitleAnim == 5)//5�̎�
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

			}
			else if (g_nCntTitleAnim == 10)//10�̎�
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_nCntTitleAnim = 0;//�������ɖ߂�
			}
		}
		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffTitle->Unlock();

}