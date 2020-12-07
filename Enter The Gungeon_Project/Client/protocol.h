#pragma once

struct PlayerInfo
{
	int iPlayerNum;				//�÷��̾� �ѹ�(1p, 2p, ��)
	float fX, fY;				//�÷��̾��� ���� ��ġ(x, y ��ǥ)
	int iCX, iCY;				//�÷��̾� ũ��
	int iHP;					//�÷��̾� ���� ü��
	TCHAR	szFrameKey[30];		//�÷��̾� ��� ����
	int		iFrameStart;		//�÷��̾� ��� ���� X
	int		iFrameVertical;		//�÷��̾� ��� ���� Y
	float fMouseX, fMouseY;		//���콺�� ����Ű�� ��ġ
};


struct BulletInfo
{
	int iOwnerNum;				//�Ѿ��� ����(1p, 2p, ��)
	float fX, fY;				//�Ѿ��� ���� ��ġ
	int iCX, iCY;				//�Ѿ��� ũ��
	int iDamage;				//�Ѿ��� ������
	float fTime;				//�Ѿ� ������ �ð�
	float fAngle;				//�Ѿ��� ����
};


struct GunInfo
{
	float fX, fY;
	int iOwnerNum;				//���� ����(1p, 2p, ��)
	int iBullet[4];				//���� �Ѿ� ����, źâũ��, �� �Ѿ˰���, �ִ� ����
	int iRenderNum;
	bool bReload;				//���� ������ Ȯ��
	bool bLeft;
};

struct Message
{
	char id;					//Ŭ���̾�Ʈ�� ID�� ��´�. (1p, 2p, ��)
	char type;					//���� �������� Ÿ���� ��´�.
	void* pData;				//�������� �ּҸ� ��´�.
};

typedef struct ServerPlayerInfo
{
	PlayerInfo	info;
	SOCKET		socket;
	DWORD		keys;
}SERVERPLAYER;


//void err_display(const char *msg)
//{
//	LPVOID lpMsgBuf;
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&lpMsgBuf, 0, NULL);
//	printf("[%s] %s", msg, (char *)lpMsgBuf);
//	LocalFree(lpMsgBuf);
//}