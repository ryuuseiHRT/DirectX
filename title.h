#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

// ��
typedef enum
{
	TITLE_ONE = 0,
	TITLE_TWO,
	TITLE_MAX
}TITLE;

// ��
typedef enum
{
	TITLEMODE_NONE = 0,
	TITLEMODE_FLASH,
	TITLEMODE_MAX
}TITLEMODE;

//�v���g�^�C�v
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(int nType, D3DXVECTOR3 pos);
void TitleFlash(int nType);

#endif // !_TITLE_H_
