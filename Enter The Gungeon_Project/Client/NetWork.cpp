#include "stdafx.h"
#include "NetWork.h"
#include "KeyMgr.h"

#include "Player.h"
#include "Bullet.h"
#include "AngleBullet.h"
#include "Gun.h"

#include "ObjMgr.h"

#include "AbstractFactory.h"

CNetwork* CNetwork::m_pInstance = NULL;

DWORD WINAPI RecvThread(LPVOID arg)
{
	while (true)
	{
		CNetwork::GetInstance()->RecvPlayerInfo(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player()));
		CNetwork::GetInstance()->RecvBulletsInfo(CObjMgr::Get_Instance()->Get_P_LstBullet());
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
	SendInputKey();
}

void CNetwork::SendInputKey()
{

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
		cout << m_Sock << " recv fail!" << endl;
	}

	if (m_dwPlayerKeyInfo & KEY_LBUTTON)
	{
		int retval = send(m_Sock, (char *)&m_tBulletInfo, sizeof(BulletInfo), 0);
		if (retval == SOCKET_ERROR)
		{
			cout << m_Sock << " recv fail!" << endl;
		}
	}

	m_dwPlayerKeyInfo = 0;
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

	//cout << tInfo.fX << ", " << tInfo.fY << endl;
	//if(tInfo.fX > 1 && tInfo.fX < 3000 && tInfo.fY > 1 && tInfo.fY < 3000)
	pPlayer->Set_Pos(tInfo.fX, tInfo.fY);
}

void CNetwork::RecvBulletsInfo(list<CObj*>* plstBullets)
{
	int BulletCnt = 0;
	int retval = recvn(m_Sock, (char *)&BulletCnt, sizeof(int), 0);
	cout << BulletCnt << endl;
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		cout << m_Sock << " recv fail!" << endl;
	}

	//총알 갯수 연동
	int Temp = BulletCnt - plstBullets->size();
	if (Temp > 0)
	{
		for (int i = 0; i < Temp; ++i)
		{
			CObj* pObj = (CAbstractFactory<CAngleBullet>::Create(0.f, 0.f, 0.f, 0.f, 14, 14));
			plstBullets->push_back(pObj);
		}
	}
	else if (Temp < 0)
	{
		for (int i = 0; i < abs(Temp); ++i)
		{
			delete plstBullets->front();
			plstBullets->pop_front();
			cout << "총알 삭제" << endl;
		}
	}

	//총알 위치 받기
	BulletInfo tBulletInfo;
	auto& iter = plstBullets->begin();
	for (int i = 0; i < BulletCnt; ++i)
	{
		int retval = recvn(m_Sock, (char *)&tBulletInfo, sizeof(BulletInfo), 0);
		if (retval == SOCKET_ERROR)
		{
			//err_display("recv()");
			cout << m_Sock << " recv fail!" << endl;
		}
		(*iter)->Set_Pos(tBulletInfo.fX, tBulletInfo.fY);
		++iter;
	}
}

void CNetwork::SetBulletInfo(float fX, float fY, float fAngle)
{
	m_tBulletInfo.fX = fX;
	m_tBulletInfo.fY = fY;
	m_tBulletInfo.fAngle = fAngle;
	m_tBulletInfo.iDamage = 1;
	m_tBulletInfo.iCX = 14;
	m_tBulletInfo.iCY = 14;
	m_tBulletInfo.fTime = 0.f;
}

int CNetwork::recvn(SOCKET s, char * buf, int len, int flags)
{
	int received;		//recv()함수의 리턴 값 저장, 오류가 발생하지 않는다면 수신된 바이트 수를 리턴
	char *ptr = buf;	//buf의 시작 주소
	int left = len;		//수신해야할 데이터 크기, 아직 읽지 않은 데이터의 양

	while (left > 0)							//수신해야할 데이터가 남아있다면
	{
		received = recv(s, ptr, left, flags);	//recv()를 통해 데이터를 수신
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)					//연결 정상 종료
			break;
		left -= received;						//수신해야할 데이터 크기 - 현재 받은 데이터
		ptr += received;						//buf의 시작 주소 + 현재 받은 데이터
	}

	return (len - left);						//읽어야할 총 길이 - 수신해야할 데이터 양 = 읽은 데이터 양
}
