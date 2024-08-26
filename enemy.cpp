//-------------------------------------------------------
//�G
//-------------------------------------------------------
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "item.h"

//�}�N��
#define NUM_ENEMY (4)		//�G�̎��

//����[�΂�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = { NULL };		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										//�G
int g_NumEnemy = 0;

//------------------
//������
//-----------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�擾
	pDevice = GetDevice();

	//�Ă�������@�S��
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\enemy001.png",
		&g_apTextureEnemy[ENEMYTYPE_ONE]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\tyuigt.jpeg",
		&g_apTextureEnemy[ENEMYTYPE_TWO]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\enemy001.png",
		&g_apTextureEnemy[ENEMYTYPE_THREE]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\enemy001.png",
		&g_apTextureEnemy[ENEMYTYPE_FOUR]);

	//�G�̏��̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nTypr = ENEMYTYPE_ONE;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 10;
		g_aEnemy[nCntEnemy].nCntS = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].KillCounter = 0;
	}
	g_NumEnemy = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���W
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//�I��
void UninitEnemy(void)
{
	int nCntEnemy;
	//�e�N�X�`���̔j�� 
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//�X�V
void UpdateEnemy(void)
{
	//�Ȃ�ł������G���[�ȊO
	int nCntEnemy;
	VERTEX_2D* pVtx;
	// ���b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	
			g_aEnemy[nCntEnemy].nCntS++;

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				if (g_aEnemy[nCntEnemy].nCntS > 60)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 10, BULLETTYPE_ENEMY);
					g_aEnemy[nCntEnemy].nCntS = 0;
				}
				break;
			case ENEMYSTATE_DAMEGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
					//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				break;
			}
		}
		pVtx += 4;
	}
	// �A�����b�N
	g_pVtxBuffEnemy->Unlock();

}
//�`��
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].nTypr)
			{
			case ENEMYTYPE_ONE:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureEnemy[ENEMYTYPE_ONE]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
				break;
			case ENEMYTYPE_TWO:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureEnemy[ENEMYTYPE_TWO]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
				break;
			case ENEMYTYPE_THREE:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureEnemy[ENEMYTYPE_THREE]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
				break;
			case ENEMYTYPE_FOUR:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureEnemy[ENEMYTYPE_FOUR]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
				break;
			default:
				break;
			}
		}
	}
}
//�G�̐ݒ菈��
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].nTypr == ENEMYTYPE_ONE)
		{
			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				//�G�̏��ݒ�i�\����
				g_aEnemy[nCntEnemy].pos = pos;
				g_aEnemy[nCntEnemy].nTypr = nType;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
				g_aEnemy[nCntEnemy].nCounterState = 0;
				g_aEnemy[nCntEnemy].nLife = 5;
				g_aEnemy[nCntEnemy].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				
			}
			pVtx += 4;
			g_NumEnemy++;	//�G�̑����J�E���g�A�b�v
			break;
		}
		else if (g_aEnemy[nCntEnemy].nTypr == ENEMYTYPE_TWO)
		{
			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				//�G�̏��ݒ�i�\����
				g_aEnemy[nCntEnemy].pos = pos;
				g_aEnemy[nCntEnemy].nTypr = nType;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
				g_aEnemy[nCntEnemy].nCounterState = 0;
				g_aEnemy[nCntEnemy].nLife = 5;
				g_aEnemy[nCntEnemy].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			pVtx += 4;
			g_NumEnemy++;	//�G�̑����J�E���g�A�b�v
			break;
		}
		else if (g_aEnemy[nCntEnemy].nTypr == ENEMYTYPE_THREE)
		{
			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				//�G�̏��ݒ�i�\����
				g_aEnemy[nCntEnemy].pos = pos;
				g_aEnemy[nCntEnemy].nTypr = nType;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
				g_aEnemy[nCntEnemy].nCounterState = 0;
				g_aEnemy[nCntEnemy].nLife = 5;
				g_aEnemy[nCntEnemy].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			pVtx += 4;
			g_NumEnemy++;	//�G�̑����J�E���g�A�b�v
			break;
		}
		else if (g_aEnemy[nCntEnemy].nTypr == ENEMYTYPE_FOUR)
		{
			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				//�G�̏��ݒ�i�\����
				g_aEnemy[nCntEnemy].pos = pos;
				g_aEnemy[nCntEnemy].nTypr = nType;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
				g_aEnemy[nCntEnemy].nCounterState = 0;
				g_aEnemy[nCntEnemy].nLife = 5;
				g_aEnemy[nCntEnemy].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 50.0f, g_aEnemy[nCntEnemy].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			pVtx += 4;
			g_NumEnemy++;	//�G�̑����J�E���g�A�b�v
			break;
		}
	}
	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx{};
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	//���b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy->KillCounter++;

		switch (g_aEnemy->KillCounter)
		{
		case 1:
		case 2:
		//case 3:
		//case 4:
		//case 5:
			SetItem(g_aEnemy[nCntEnemy].pos, ITEMTYPE_ONE);
			break;
		case 3:
		case 4:
		//case 8:
		//case 9:
		//case 10:
			SetItem(g_aEnemy[nCntEnemy].pos, ITEMTYPE_TWO);
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			SetItem(g_aEnemy[nCntEnemy].pos, ITEMTYPE_ONE);
			break;
		default:
			break;
		}
		// �G��|�������̃X�R�A���Z
		AddScore(50);
		g_NumEnemy--;	//�G�̑����J�E���g�_�E��
	}
	else
	{
   		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;
		pVtx += 4 * nCntEnemy; //�����l���Ȃ��̂ŃG���[�̊댯��������

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	}
	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
int GeetNumEnemy()
{
	return g_NumEnemy;
}
//�G�̎擾
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];			//�G�̏��̐擪�A�h���X��Ԃ�
}
