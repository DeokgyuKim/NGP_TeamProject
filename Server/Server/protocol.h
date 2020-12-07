#pragma once

struct PlayerInfo
{
	int iPlayerNum;				//플레이어 넘버(1p, 2p, …)
	float fX, fY;				//플레이어의 현재 위치(x, y 좌표)
	int iCX, iCY;				//플레이어 크기
	int iHP;					//플레이어 남은 체력
	TCHAR	szFrameKey[30];		//플레이어 출력 정보
	int		iFrameStart;		//플레이어 출력 정보 X
	int		iFrameVertical;		//플레이어 출력 정보 Y
	float fMouseX, fMouseY;		//마우스가 가리키는 위치
};


struct BulletInfo
{
	int iOwnerNum;				//총알의 주인(1p, 2p, …)
	float fX, fY;				//총알의 현재 위치
	int iCX, iCY;				//총알의 크기
	int iDamage;				//총알의 데미지
	float fTime;				//총알 생성후 시간
	float fAngle;				//총알의 방향
};


struct GunInfo
{
	int iOwnerNum;				//총의 주인(1p, 2p, …)
	int iBullet[4];				//현재 총알 개수, 탄창크기, 총 총알개수, 최대 개수
	bool bReload;				//장전 중인지 확인
	TCHAR* szFrameKey;			//총 출력정보
};

struct Message
{
	char id;					//클라이언트의 ID를 담는다. (1p, 2p, …)
	char type;					//보낸 데이터의 타입을 담는다.
	void* pData;				//데이터의 주소를 담는다.
};

typedef struct ServerPlayerInfo
{
	PlayerInfo	info;
	SOCKET		socket;
	DWORD		keys;
	bool		roll;
	float		speed;
	DWORD		rollkey;
	
}SERVERPLAYER;