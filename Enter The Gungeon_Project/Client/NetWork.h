#pragma once

#pragma comment(lib, "ws2_32")
#pragma warning(disable : 4996)
#include <winsock2.h>

#include <unordered_map>

#include "define.h"
#include "protocol.h"

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
	//char	m_cKey;
private:

	PlayerInfo			m_tPlayerInfo;

	// 플레이어의 조작키 프로토콜
	DWORD				m_dwPlayerKeyInfo;

	bool				m_bServerOn;

public:
	bool Init(const string& strServerIP = "127.0.0.1");
	void Update();


public:
	void SendInputKey();
};

