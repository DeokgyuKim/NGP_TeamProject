#include "stdafx.h"
#include "NetWork.h"
#include "KeyMgr.h"

#include "Player.h"
#include "OtherPlayer.h"
#include "Bullet.h"
#include "AngleBullet.h"
#include "Gun.h"
#include "OtherGun.h"

#include "ObjMgr.h"

#include "AbstractFactory.h"

CNetwork* CNetwork::m_pInstance = NULL;

DWORD WINAPI RecvThread(LPVOID arg)
{
	while (true)
	{
		CNetwork::GetInstance()->RecvPlayerInfo(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player()));
		CNetwork::GetInstance()->RecvOtherPlayerInfo(static_cast<COtherPlayer*>(CObjMgr::Get_Instance()->Get_Other()->front()));

		//if (CNetwork::GetInstance()->RecvGameState() == 0)
		//{
		//	;
		//}

		CNetwork::GetInstance()->RecvOtherGunInfo(static_cast<COtherGun*>(CObjMgr::Get_Instance()->Get_OtherGun()->front()));
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

	int option = TRUE;
	setsockopt(m_Sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(option));

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

	retval = recvn(m_Sock, (char *)&m_iPlayerNum, sizeof(int), 0);


	hRecvThread = CreateThread(NULL, 0, RecvThread, NULL, 0, &dwThreadId);

	return true;
}

bool CNetwork::Release()
{
	return false;
}

void CNetwork::Update()
{
	if (m_bServerOn == false)
	{
		//ExitThread(dwThreadId);
	}
	SendInputKey();
	SendPlayerInfo(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player()));
	SendGunInfo(static_cast<CGun*>(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_GunNow()));
	//RecvPlayerInfo(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player()));
	//RecvOtherPlayerInfo(static_cast<COtherPlayer*>(CObjMgr::Get_Instance()->Get_Other()->front()));
	//RecvOtherGunInfo(static_cast<COtherGun*>(CObjMgr::Get_Instance()->Get_OtherGun()->front()));
	//RecvBulletsInfo(CObjMgr::Get_Instance()->Get_P_LstBullet());
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
		//cout << m_Sock << " recv fail!" << endl;
	}

	if (m_dwPlayerKeyInfo & KEY_LBUTTON)
	{
		int retval = send(m_Sock, (char *)&m_tBulletInfo, sizeof(BulletInfo), 0);
		if (retval == SOCKET_ERROR)
		{
			//cout << m_Sock << " recv fail!" << endl;
		}
	}

	m_dwPlayerKeyInfo = 0;
}

void CNetwork::SendPlayerInfo(CPlayer * pPlayer)
{
	PlayerInfo tInfo;
	tInfo.iPlayerNum = m_iPlayerNum;
	tInfo.fX = pPlayer->Get_Info()->fX;
	tInfo.fY = pPlayer->Get_Info()->fY;
	tInfo.iCX = pPlayer->Get_Info()->iCX;
	tInfo.iCY = pPlayer->Get_Info()->iCY;
	tInfo.iHP = pPlayer->Get_Hp();
	wcscpy_s(tInfo.szFrameKey, 30, pPlayer->Get_FrameKey());
	tInfo.iFrameStart = pPlayer->Get_Frame().iFrameStart;
	tInfo.iFrameVertical = pPlayer->Get_Frame().iFrameVetical;

	int retval = send(m_Sock, (char *)&tInfo, sizeof(PlayerInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		//cout << m_Sock << " recv fail!" << endl;
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
		//cout << m_Sock << " recv fail!" << endl;
	}
}

void CNetwork::SendGunInfo(CGun * pGun)
{
	GunInfo tInfo;

	tInfo.iOwnerNum = pGun->m_iPlayerNum;
	tInfo.fX = pGun->Get_Info()->fX;
	tInfo.fY = pGun->Get_Info()->fY;
	tInfo.bLeft = pGun->m_bLeft;
	tInfo.iRenderNum =pGun->GetRenderNum();

	int retval = send(m_Sock, (char *)&tInfo, sizeof(GunInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		//cout << m_Sock << " recv fail!" << endl;
	}
}

void CNetwork::RecvPlayerInfo(CPlayer * pPlayer)
{
	PlayerInfo tInfo;

	int retval = recvn(m_Sock, (char *)&tInfo, sizeof(PlayerInfo), 0);
	if (tInfo.iHP > 6 || tInfo.iHP < -1)
		return;
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		//cout << m_Sock << " recv fail!" << endl;
	}

	//cout << tInfo.fX << ", " << tInfo.fY << endl;
	//if(tInfo.fX > 1 && tInfo.fX < 3000 && tInfo.fY > 1 && tInfo.fY < 3000)
	pPlayer->Set_Hp(tInfo.iHP);
	pPlayer->Set_Pos(tInfo.fX, tInfo.fY);
}

void CNetwork::RecvOtherPlayerInfo(COtherPlayer * pPlayer)
{
	PlayerInfo tInfo;

	int retval = recvn(m_Sock, (char *)&tInfo, sizeof(PlayerInfo), 0);
	if (tInfo.iHP > 6 || tInfo.iHP < -1)
		return;
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		//cout << m_Sock << " recv fail!" << endl;
	}

	//cout << tInfo.fX << ", " << tInfo.fY << endl;
	//if(tInfo.fX > 1 && tInfo.fX < 3000 && tInfo.fY > 1 && tInfo.fY < 3000)
	pPlayer->Set_Pos(tInfo.fX, tInfo.fY);
	pPlayer->Set_Hp(tInfo.iHP);
	pPlayer->Set_FrameKeyCpy(tInfo.szFrameKey);
	pPlayer->Set_FrameStart(tInfo.iFrameStart);
	pPlayer->Set_FrameVertical(tInfo.iFrameVertical);
}

void CNetwork::RecvBulletsInfo(list<CObj*>* plstBullets)
{
	int BulletCnt = 0;
	int retval = recvn(m_Sock, (char *)&BulletCnt, sizeof(int), 0);
	if (BulletCnt >= 10000)
		return;
	//cout << BulletCnt << endl;
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		//cout << m_Sock << " recv fail!" << endl;
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
			//cout << "총알 삭제" << endl;
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
			//cout << m_Sock << " recv fail!" << endl;
		}
		(*iter)->Set_Pos(tBulletInfo.fX, tBulletInfo.fY);\
		++iter;
	}
}

void CNetwork::RecvOtherGunInfo(COtherGun * pPlayer)
{
	GunInfo tInfo;

	int retval = recvn(m_Sock, (char *)&tInfo, sizeof(GunInfo), 0);
	if (tInfo.iOwnerNum > 6 || tInfo.iOwnerNum < -1)
		return;
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		//cout << m_Sock << " recv fail!" << endl;
	}

	//cout << tInfo.fX << ", " << tInfo.fY << endl;
	//if(tInfo.fX > 1 && tInfo.fX < 3000 && tInfo.fY > 1 && tInfo.fY < 3000)
	pPlayer->m_iPlayerNum = tInfo.iOwnerNum;
	pPlayer->Set_Pos(tInfo.fX, tInfo.fY);
	pPlayer->m_bLeft = tInfo.bLeft;
	pPlayer->SetRenderCnt(tInfo.iRenderNum);
}

int CNetwork::RecvGameState()
{
	int Event;
	int retval = recvn(m_Sock, (char *)&Event, sizeof(int), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		//cout << m_Sock << " recv fail!" << endl;
	}
	if (Event != -1)
	{
		//m_bServerOn = false;
		if (Event == m_iPlayerNum)
			m_iWin = -1;
		else
			m_iWin = 1;
		return 0;
	}
	return -1;
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
