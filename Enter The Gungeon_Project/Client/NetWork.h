#pragma once

#pragma comment(lib, "ws2_32")
#pragma warning(disable : 4996)
#include <winsock2.h>

#include <unordered_map>

#include "define.h"
#include "protocol.h"

class CPlayer;
class COtherPlayer;
class CBullet;
class CGun;
class CObj;

using namespace std;

class CNetwork
{
private:
	CNetwork() {}
	~CNetwork() {}
private:
	static CNetwork* m_pInstance;
public:
	static CNetwork*	GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CNetwork;
		return m_pInstance;
	}
	static void			DestroyInstance()
	{
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = NULL;
	}
private:
	SOCKET m_Sock;
	HANDLE hRecvThread;
	//char	m_cKey;
private:

	PlayerInfo			m_tPlayerInfo;
	BulletInfo			m_tBulletInfo;
	bool				m_bOldRB = false;
	// 플레이어의 조작키 프로토콜
	DWORD				m_dwPlayerKeyInfo;

	bool				m_bServerOn;
public:
	int					m_iPlayerNum;
public:
	bool Init(const string& strServerIP = "127.0.0.1");
	bool Release();
public:
	void Update();


public:
	void SendInputKey();
	void SendPlayerInfo(CPlayer* pPlayer);
	void SendBulletInfo(CBullet* pBullet);
	void SendGunInfo(CGun* pGun);
public:
	void RecvPlayerInfo(CPlayer* pPlayer);
	void RecvOtherPlayerInfo(COtherPlayer* pPlayer);
	void RecvBulletsInfo(list<CObj*>* plstBullets);
public:
	void SetInputKey(DWORD dwKey) { m_dwPlayerKeyInfo |= dwKey; }
	void SetBulletInfo(float fX, float fY, float fAngle);
public:
	int recvn(SOCKET s, char *buf, int len, int flags);
private:
};

