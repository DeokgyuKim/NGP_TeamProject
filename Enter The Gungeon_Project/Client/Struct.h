#pragma once
typedef struct tagInfo
{
	float fX; 
	float fY; 
	int iCX; 
	int iCY; 
}INFO;
typedef struct tagPos
{
	float fX;
	float fY;
}POS;

typedef struct tagFrame
{
	int iFrameStart; // ������. 
	int iFrameEnd;  // ���� 
	int iFrameVetical; // y��. y ���� ���Կ� ���� �÷��̾� Ȥ�� ������ ���°� ��ȯ.
	int iPlus;
	DWORD dwFrameSpeed; // �󸶸�ŭ ������ ������ ������ 
	DWORD dwFrameTime; // �����̴� �ð���. 
	tagFrame() {}
	tagFrame(int i1, int i2, int i3, int i4, DWORD dw1, DWORD dw2)
	{
		iFrameStart = i1;
		iFrameEnd = i2;
		iFrameVetical = i3;
		iPlus = i4;
		dwFrameSpeed = dw1;
		dwFrameTime = dw2;
	}
}FRAME;