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
	int iOwnerNum;				//���� ����(1p, 2p, ��)
	int iBullet[4];				//���� �Ѿ� ����, źâũ��, �� �Ѿ˰���, �ִ� ����
	bool bReload;				//���� ������ Ȯ��
	TCHAR* szFrameKey;			//�� �������
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
	bool		roll;
	float		speed;
	DWORD		rollkey;
	
}SERVERPLAYER;