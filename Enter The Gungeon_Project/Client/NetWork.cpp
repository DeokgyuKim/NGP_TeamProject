#include "stdafx.h"
#include "NetWork.h"
#include "KeyMgr.h"

#include "Player.h"
#include "Bullet.h"
#include "Gun.h"

#include "ObjMgr.h"

CNetwork* CNetwork::m_pInstance = NULL;

DWORD WINAPI RecvThread(LPVOID arg)
{
	while (true)
	{
		CNetwork::GetInstance()->RecvPlayerInfo(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player()));
	}
	return 0;
}

bool CNetwork::Init(const string & strServerIP)
{
	int retval;

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}

	// socket()
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Sock == INVALID_SOCKET)
	{
		return false;
	}

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(strServerIP.c_str());
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(m_Sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));

	if (retval == SOCKET_ERROR)
	{
		return false;
	}

	m_bServerOn = true;

	hRecvThread = CreateThread(NULL, 0, RecvThread, NULL, 0, NULL);

	return true;
}

bool CNetwork::Release()
{
	return false;
}

void CNetwork::Update()
{
	m_dwPlayerKeyInfo = 0;
	if (CKeyMgr::Get_Instance()->KeyPressing('W'))
	{
		m_dwPlayerKeyInfo |= KEY_W;
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		m_dwPlayerKeyInfo |= KEY_A;
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('S'))
	{
		m_dwPlayerKeyInfo |= KEY_S;
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('D'))
	{
		m_dwPlayerKeyInfo |= KEY_D;
	}
	SendInputKey();
}

void CNetwork::SendInputKey()
{
	m_dwPlayerKeyInfo = 0;
	if (CKeyMgr::Get_Instance()->KeyPressing('W'))
	{
		m_dwPlayerKeyInfo |= KEY_W;
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('A'))
	{
		m_dwPlayerKeyInfo |= KEY_A;
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('S'))
	{
		m_dwPlayerKeyInfo |= KEY_S;
	}
	if (CKeyMgr::Get_Instance()->KeyPressing('D'))
	{
		m_dwPlayerKeyInfo |= KEY_D;
	}
	int retval = send(m_Sock, (char *)&m_dwPlayerKeyInfo, sizeof(DWORD), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		cout << m_Sock << " recv fail!" << endl;
	}
}

void CNetwork::SendPlayerInfo(CPlayer * pPlayer)
{
	PlayerInfo tInfo;
	tInfo.fX = pPlayer->Get_Info()->fX;
	tInfo.fY = pPlayer->Get_Info()->fY;
	tInfo.iCX = pPlayer->Get_Info()->iCX;
	tInfo.iCY = pPlayer->Get_Info()->iCY;
	tInfo.iHP = pPlayer->Get_Hp();
	tInfo.szFrameKey = pPlayer->Get_FrameKey();

	int retval = send(m_Sock, (char *)&tInfo, sizeof(PlayerInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		cout << m_Sock << " recv fail!" << endl;
	}
}

void CNetwork::SendBulletInfo(CBullet * pBullet)
{
	BulletInfo tInfo;
	tInfo.fX = pBullet->Get_Info()->fX;
	tInfo.fY = pBullet->Get_Info()->fY;
	tInfo.iCX = pBullet->Get_Info()->iCX;
	tInfo.iCY = pBullet->Get_Info()->iCY;
	tInfo.fAngle = pBullet->Get_Angle();
	tInfo.iDamage = 1;

	int retval = send(m_Sock, (char *)&tInfo, sizeof(BulletInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		cout << m_Sock << " recv fail!" << endl;
	}
}

void CNetwork::SendGunInfo(CGun * pGun)
{
	GunInfo tInfo;
	tInfo.bReload = pGun->Get_Reload();
	for (int i = 0; i < 4; ++i)
		tInfo.iBullet[i] = pGun->Get_BulletState()[i];
	tInfo.szFrameKey = pGun->Get_FrameKey();

	int retval = send(m_Sock, (char *)&tInfo, sizeof(GunInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		cout << m_Sock << " recv fail!" << endl;
	}
}

void CNetwork::RecvPlayerInfo(CPlayer * pPlayer)
{
	PlayerInfo tInfo;

	int retval = recvn(m_Sock, (char *)&tInfo, sizeof(PlayerInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		cout << m_Sock << " recv fail!" << endl;
	}

	cout << tInfo.fX << ", " << tInfo.fY << endl;
	//if(tInfo.fX > 1 && tInfo.fX < 3000 && tInfo.fY > 1 && tInfo.fY < 3000)
	//	pPlayer->Set_Pos(tInfo.fX, tInfo.fY);
}

int CNetwork::recvn(SOCKET s, char * buf, int len, int flags)
{
	int received;		//recv()�Լ��� ���� �� ����, ������ �߻����� �ʴ´ٸ� ���ŵ� ����Ʈ ���� ����
	char *ptr = buf;	//buf�� ���� �ּ�
	int left = len;		//�����ؾ��� ������ ũ��, ���� ���� ���� �������� ��

	while (left > 0)							//�����ؾ��� �����Ͱ� �����ִٸ�
	{
		received = recv(s, ptr, left, flags);	//recv()�� ���� �����͸� ����
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)					//���� ���� ����
			break;
		left -= received;						//�����ؾ��� ������ ũ�� - ���� ���� ������
		ptr += received;						//buf�� ���� �ּ� + ���� ���� ������
	}

	return (len - left);						//�о���� �� ���� - �����ؾ��� ������ �� = ���� ������ ��
}