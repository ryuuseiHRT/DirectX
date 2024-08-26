//=====================================================
//
// �A�C�e������  [item.cpp]
// Author : HRT ryu
//
//====================================================

#include "item.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "bullet.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureItem[MAX_ITEM] = { NULL };			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVteBuffItem = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
ITEM g_aItem[MAX_ITEM];					// �A�C�e��

//***********************
// ����������
//***********************
void InitItem(void)
{
	// ���݂̃f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nItem;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\ITEM001.png",
		&g_pTextureItem[ITEMTYPE_ONE]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\ITEM002.png",
		&g_pTextureItem[ITEMTYPE_TWO]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\rtge.jpg",
		&g_pTextureItem[ITEMTYPE_THREE]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\tyuigt.jpeg",
		&g_pTextureItem[ITEMTYPE_FOUR]);

	D3DXCreateTextureFromFile(pDevice,
		"date\\TEXTURE\\effect3.png",
		&g_pTextureItem[ITEMTYPE_FIVE]);

	// �A�C�e�����̏�����
	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		g_aItem[nItem].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
		g_aItem[nItem].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aItem[nItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
		g_aItem[nItem].state = ITEMSTATE_NONE;
		g_aItem[nItem].nCounterState = 0;
		g_aItem[nItem].nType = ITEMTYPE_ONE;
		g_aItem[nItem].nSoul = 10;
		g_aItem[nItem].bUse = false;
		g_aItem[nItem].nCounterAnimItem = 0;
		g_aItem[nItem].nPttarnAnimItem = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVteBuffItem,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		pVtx[0].pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(150.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(100.0f, 150.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(150.0f, 150.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.25f);

		pVtx += 4;	//�f�[�^4�i�߂�
	}

	//�A�����b�N
	g_pVteBuffItem->Unlock();
}
//***********************
//�I������
//***********************
void UninitItem(void)
{
	int nItem;
	//�e�N�X�`���̔j�� 
	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_pTextureItem[nItem] != NULL)
		{
			g_pTextureItem[nItem]->Release();
			g_pTextureItem[nItem] = NULL;
		}
	}

	if (g_pVteBuffItem != NULL)
	{
		g_pVteBuffItem->Release();
		g_pVteBuffItem = NULL;
	}

}
//***********************
// �X�V����
//***********************
void UpdateItem(void)
{
	int nItem;

	Player* pPlayer;
	pPlayer = GetPlayer();

	// ���݂̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_aItem[nItem].pos.x >= pPlayer->pos.x - 50
			&& g_aItem[nItem].pos.x <= pPlayer->pos.x + 50
			&& g_aItem[nItem].pos.y >= pPlayer->pos.y - 50
			&& g_aItem[nItem].pos.y <= pPlayer->pos.y + 50)
		{
			if (g_aItem[nItem].bUse == true && g_aItem[nItem].nType == ITEMTYPE_ONE)
			{
				AddScore(100);
			}
			
			if (g_aItem[nItem].bUse == true && g_aItem[nItem].nType == ITEMTYPE_TWO)
			{
				AddScore(200);
			}
			
			if (g_aItem[nItem].bUse == true && g_aItem[nItem].nType == ITEMTYPE_THREE)
			{
				AddScore(300);
			}
			
			if (g_aItem[nItem].bUse == true && g_aItem[nItem].nType == ITEMTYPE_FOUR)
			{
				AddScore(400);
			}
			
			if (g_aItem[nItem].bUse == true && g_aItem[nItem].nType == ITEMTYPE_FIVE)
			{
				AddScore(500);
			}

			g_aItem[nItem].bUse = false;
			break;
		}

		if (g_aItem[nItem].bUse == true)
		{
			switch (g_aItem[nItem].state)
			{
			case ITEMSTATE_NORMAL:
				g_aItem[nItem].nCounterAnimItem++;		// �J�E���^�[���Z
				switch (g_aItem[nItem].nType)
				{
				case ITEMTYPE_ONE:
					if ((g_aItem[ITEMTYPE_ONE].nCounterAnimItem % 5) == 0)
					{
						g_aItem[ITEMTYPE_ONE].nCounterAnimItem = 0;

						// �p�^�[���̍X�V
						g_aItem[ITEMTYPE_ONE].nPttarnAnimItem = (g_aItem[ITEMTYPE_ONE].nPttarnAnimItem + 1) % 20;	// �p�^�[���i���o�[���ɂ���

						// �e�N�X�`�����W�X�V
						pVtx[0].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_ONE].nPttarnAnimItem, 0.25f * (g_aItem[ITEMTYPE_ONE].nPttarnAnimItem / 5));
						pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_ONE].nPttarnAnimItem), 0.25f * (g_aItem[ITEMTYPE_ONE].nPttarnAnimItem / 5));
						pVtx[2].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_ONE].nPttarnAnimItem, 0.25f + 0.25f * (g_aItem[ITEMTYPE_ONE].nPttarnAnimItem / 5));
						pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_ONE].nPttarnAnimItem), 0.25f + 0.25f * (g_aItem[ITEMTYPE_ONE].nPttarnAnimItem / 5));
					}
					pVtx += 4;
					break;
				case ITEMTYPE_TWO:
					if ((g_aItem[ITEMTYPE_TWO].nCounterAnimItem % 5) == 0)
					{
						g_aItem[ITEMTYPE_TWO].nCounterAnimItem = 0;

						// �p�^�[���̍X�V
						g_aItem[ITEMTYPE_TWO].nPttarnAnimItem = (g_aItem[ITEMTYPE_TWO].nPttarnAnimItem + 1) % 20;	// �p�^�[���i���o�[���ɂ���

						// �e�N�X�`�����W�X�V
						pVtx[0].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_TWO].nPttarnAnimItem, 0.25f * (g_aItem[ITEMTYPE_TWO].nPttarnAnimItem / 5));
						pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_TWO].nPttarnAnimItem), 0.25f * (g_aItem[ITEMTYPE_TWO].nPttarnAnimItem / 5));
						pVtx[2].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_TWO].nPttarnAnimItem, 0.25f + 0.25f * (g_aItem[ITEMTYPE_TWO].nPttarnAnimItem / 5));
						pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_TWO].nPttarnAnimItem), 0.25f + 0.25f * (g_aItem[ITEMTYPE_TWO].nPttarnAnimItem / 5));
					}
					pVtx += 4;
					break;
				case ITEMTYPE_THREE:
					if ((g_aItem[ITEMTYPE_THREE].nCounterAnimItem % 5) == 0)
					{
						g_aItem[ITEMTYPE_THREE].nCounterAnimItem = 0;

						// �p�^�[���̍X�V
						g_aItem[ITEMTYPE_THREE].nPttarnAnimItem = (g_aItem[ITEMTYPE_THREE].nPttarnAnimItem + 1) % 20;	// �p�^�[���i���o�[���ɂ���

						// �e�N�X�`�����W�X�V
						pVtx[0].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_THREE].nPttarnAnimItem, 0.25f * (g_aItem[ITEMTYPE_THREE].nPttarnAnimItem / 5));
						pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_THREE].nPttarnAnimItem), 0.25f * (g_aItem[ITEMTYPE_THREE].nPttarnAnimItem / 5));
						pVtx[2].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_THREE].nPttarnAnimItem, 0.25f + 0.25f * (g_aItem[ITEMTYPE_THREE].nPttarnAnimItem / 5));
						pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_THREE].nPttarnAnimItem), 0.25f + 0.25f * (g_aItem[ITEMTYPE_THREE].nPttarnAnimItem / 5));
					}
					pVtx += 4;
					break;
				case ITEMTYPE_FOUR:
					if ((g_aItem[ITEMTYPE_FOUR].nCounterAnimItem % 5) == 0)
					{
						g_aItem[ITEMTYPE_FOUR].nCounterAnimItem = 0;

						// �p�^�[���̍X�V
						g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem = (g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem + 1) % 20;	// �p�^�[���i���o�[���ɂ���

						// �e�N�X�`�����W�X�V
						pVtx[0].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem, 0.25f * (g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem / 5));
						pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem), 0.25f * (g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem / 5));
						pVtx[2].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem, 0.25f + 0.25f * (g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem / 5));
						pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem), 0.25f + 0.25f * (g_aItem[ITEMTYPE_FOUR].nPttarnAnimItem / 5));
					}
					pVtx += 4;
					break;
				case ITEMTYPE_FIVE:
					if ((g_aItem[ITEMTYPE_FIVE].nCounterAnimItem % 5) == 0)
					{
						g_aItem[ITEMTYPE_FIVE].nCounterAnimItem = 0;

						// �p�^�[���̍X�V
						g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem = (g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem + 1) % 20;	// �p�^�[���i���o�[���ɂ���

						// �e�N�X�`�����W�X�V
						pVtx[0].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem, 0.25f * (g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem / 5));
						pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem), 0.25f * (g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem / 5));
						pVtx[2].tex = D3DXVECTOR2(0.2f * g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem, 0.25f + 0.25f * (g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem / 5));
						pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem), 0.25f + 0.25f * (g_aItem[ITEMTYPE_FIVE].nPttarnAnimItem / 5));
					}
					pVtx += 4;
					break;

				default:
					break;
				}

			case ITEMSTATE_DAMEGE:
				g_aItem[nItem].nCounterState--;
				if (g_aItem[nItem].nCounterState <= 0)
				{
					g_aItem[nItem].state = ITEMSTATE_NORMAL;

					//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				break;

			default:
				break;
			}
		}
	}
	//�A�����b�N
	g_pVteBuffItem->Unlock();
}
//***********************
// �`�揈��
//***********************
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nItem;
	//�f�o�C�X�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVteBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (g_aItem[nItem].bUse == true)
		{
			switch (g_aItem[nItem].nType)
			{
			case ITEMTYPE_ONE:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[ITEMTYPE_ONE]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nItem, 2);
				break;
			case ITEMTYPE_TWO:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[ITEMTYPE_TWO]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nItem, 2);
				break;
			case ITEMTYPE_THREE:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[ITEMTYPE_THREE]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nItem, 2);
				break;
			case ITEMTYPE_FOUR:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[ITEMTYPE_FOUR]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nItem, 2);
				break;
			case ITEMTYPE_FIVE:
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureItem[ITEMTYPE_FIVE]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nItem, 2);
				break;

			default:
				break;
			}
		}
	}
}
//***********************
// �A�C�e���̐ݒ�
//***********************
void SetItem(D3DXVECTOR3 pos, int nType)
{
	int nItem;

	VERTEX_2D* pVtx;
	//���b�N
	g_pVteBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nItem = 0; nItem < MAX_ITEM; nItem++)
	{
		if (nType == ITEMTYPE_ONE)
		{
			if (g_aItem[nItem].bUse == false)
			{
				//�A�C�e���̏��ݒ�i�\����
				g_aItem[nItem].pos = pos;
				g_aItem[nItem].nType = nType;
				g_aItem[nItem].state = ITEMSTATE_NORMAL;
				g_aItem[nItem].nCounterState = 0;
				g_aItem[nItem].nSoul = 10;
				g_aItem[nItem].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}
			pVtx += 4;
		}
		else if (nType == ITEMTYPE_TWO)
		{
			if (g_aItem[nItem].bUse == false)
			{
				//�A�C�e���̏��ݒ�i�\����
				g_aItem[nItem].pos = pos;
				g_aItem[nItem].nType = nType;
				g_aItem[nItem].state = ITEMSTATE_NORMAL;
				g_aItem[nItem].nCounterState = 0;
				g_aItem[nItem].nSoul = 10;
				g_aItem[nItem].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}
			pVtx += 4;
		}
		else if (nType == ITEMTYPE_THREE)
		{
			if (g_aItem[nItem].bUse == false)
			{
				//�A�C�e���̏��ݒ�i�\����
				g_aItem[nItem].pos = pos;
				g_aItem[nItem].nType = nType;
				g_aItem[nItem].state = ITEMSTATE_NORMAL;
				g_aItem[nItem].nCounterState = 0;
				g_aItem[nItem].nSoul = 10;
				g_aItem[nItem].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}
			pVtx += 4;
		}
		else if (nType == ITEMTYPE_FOUR)
		{
			if (g_aItem[nItem].bUse == false)
			{
				//�A�C�e���̏��ݒ�i�\����
				g_aItem[nItem].pos = pos;
				g_aItem[nItem].nType = nType;
				g_aItem[nItem].state = ITEMSTATE_NORMAL;
				g_aItem[nItem].nCounterState = 0;
				g_aItem[nItem].nSoul = 10;
				g_aItem[nItem].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}
			pVtx += 4;
		}
		else if (nType == ITEMTYPE_FIVE)
		{
			if (g_aItem[nItem].bUse == false)
			{
				//�A�C�e���̏��ݒ�i�\����
				g_aItem[nItem].pos = pos;
				g_aItem[nItem].nType = nType;
				g_aItem[nItem].state = ITEMSTATE_NORMAL;
				g_aItem[nItem].nCounterState = 0;
				g_aItem[nItem].nSoul = 10;
				g_aItem[nItem].bUse = true;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y - 50.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aItem[nItem].pos.x - 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aItem[nItem].pos.x + 50.0f, g_aItem[nItem].pos.y + 50.0f, 0.0f);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}
			pVtx += 4;
		}
	}
	//�A�����b�N
	g_pVteBuffItem->Unlock();
}
//***********************
// �A�C�e���̓����蔻��
//***********************
void HitItem(int nCntItem, int nDamage)
 {
	Player g_player;
	VERTEX_2D* pVtx{};
	//���b�N
	g_pVteBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	g_aItem[nCntItem].nSoul -= nDamage;

  	if (g_aItem[nCntItem].nSoul <= 0)
	{
		//SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_aItem[nCntItem].bUse = false;
	}
	else
	{
		for (int nItem = 0; nItem < MAX_ITEM; nItem++)
		{
			if (g_aItem[nItem].bUse == true)
			{
				if (g_aItem[nItem].nType == ITEMTYPE_ONE)
				{
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					break;
				}

				if (g_aItem[nItem].nType == ITEMTYPE_TWO)
				{
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					break;
				}

				if (g_aItem[nItem].nType == ITEMTYPE_THREE)
				{
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					break;
				}

				if (g_aItem[nItem].nType == ITEMTYPE_FOUR)
				{
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					break;
				}

				if (g_aItem[nItem].nType == ITEMTYPE_FIVE)
				{
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.25f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					SetBullet(g_aItem[nItem].pos, D3DXVECTOR3(sinf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 20.0f, cosf(g_aItem[nItem].rot.z + D3DX_PI * 0.75f) * 10.0f, 0.0f), 100, BULLETTYE_ITEM);
					break;
				}
			}
		}

		g_aItem[nCntItem].state = ITEMSTATE_DAMEGE;
		g_aItem[nCntItem].nCounterState = 5;
		pVtx += 4 * nCntItem; //�����l���Ȃ��̂ŃG���[�̊댯��������

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	}

	//�A�����b�N
	g_pVteBuffItem->Unlock();
}
//***********************
// �A�C�e���̎擾
//***********************
ITEM* GetItem(void)
{
	return g_aItem;
}