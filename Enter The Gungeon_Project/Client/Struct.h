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
	int iFrameStart; // 시작점. 
	int iFrameEnd;  // 끝점 
	int iFrameVetical; // y값. y 값이 변함에 따라 플레이어 혹은 몬스터의 상태가 변환.
	int iPlus;
	DWORD dwFrameSpeed; // 얼마만큼 빠르게 움지길 것인지 
	DWORD dwFrameTime; // 움직이는 시간값. 
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