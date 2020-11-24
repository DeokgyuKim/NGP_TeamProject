#include "stdafx.h"
#include "NetWork.h"
#include "KeyMgr.h"

CNetwork* CNetwork::m_pInstance = NULL;

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

	return true;
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
	int retval = send(m_Sock, (char *)&m_dwPlayerKeyInfo, sizeof(DWORD), 0);
	if (retval == SOCKET_ERROR)
	{
		//err_display("recv()");
		cout << m_Sock << " recv fail!" << endl;
	}
}
