#ifndef _MAIN_H_		//���̒�`������Ȃ�������
#define _MAIN_H_		//��d�C���N���[�h�h�~�̃}�N����`

#include<windows.h>
#include"d3dx9.h"							//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)		//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"							//�L�[�{�[�h�̓��͏����ɕK�v
#include "Xinput.h"							//�W���C�p�b�g�̓��͏���
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")				//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")			//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")			//DirectX�̃R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")			//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")			//�L�[�{�[�h�����ɕK�v
#pragma comment(lib,"xinput.lib")			//�W���C�p�b�g�����ɕK�v

//�}�N����`
#define CLASS_NAME "WindowsClass"			//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "2D�V���[�e�B���O"	//�E�B���h�E�̖��O
#define SCREEN_WIDTH (1280)					//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)					//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//��ʂ̎��
typedef enum
{
	MODE_TITLE=0,		//�^�C�g�����
	MODE_GAME,			//�Q�[�����
	MODE_RESULT,		//���U���g���
	MODE_CLEAR,			//�N���A���
	MODE_MAX
}MODE;

//���_���u�QD�v�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
}VERTEX_2D;

//�v���g�^�C�v
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd,BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void ToggleFullscreen(HWND hWnd);				// �E�B���h�E���t���X�N���[���ɂ�����@


#endif