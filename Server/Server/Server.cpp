#pragma once

#pragma comment(lib, "ws2_32")
#pragma warning(disable : 4996)
#include <winsock2.h>

#include <stdio.h>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <list>
#include <random>
#include <time.h>

#include "define.h"
#include "protocol.h"

using namespace std;


int										g_iClientNumber = 0;
unordered_map<int, SERVERPLAYER*>		g_Clients;
list<BulletInfo*>						g_lstBulletInfo;
list<GunInfo*>							g_lstGunInfo;

float									g_fTimeDelta = 0.f;



DWORD WINAPI ProcessClient(LPVOID arg);
DWORD WINAPI WorkThread(LPVOID arg);

void Update(float fTimeDelta);
void RecvInputKey(int clientnum);
void SendPlayerInfo(int clientnum);

// ���� �Լ� ���� ���
void err_display(const char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int main()
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA	wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "���� �ʱ�ȭ �ȵ�" << endl;
		return 1;
	}

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
	{
		cout << "socket ����" << endl;
	}


	//Update Thread
	HANDLE hWorkThread;
	cout << "Create Update Thread" << endl;
	hWorkThread = CreateThread(NULL, 0, WorkThread, NULL, 0, NULL);

	if (hWorkThread != NULL)
	{
		CloseHandle(hWorkThread);
	}

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		cout << "bind ����" << endl;
	}

	// listen()
	retval = listen(listen_sock, SOMAXCONN);			// 2������� ���Ӱ���
	if (retval == SOCKET_ERROR)
	{
		cout << "listen ����" << endl;
	}

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;

	while (true)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET)
		{
			cout << "accept ����" << endl;
			break;
		}
		cout << "������ Ŭ���̾�Ʈ �� : " << g_iClientNumber + 1 << ", ������ Ŭ���̾�Ʈ ���� : " << client_sock << endl;

		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		g_Clients[g_iClientNumber] = new SERVERPLAYER;
		g_Clients[g_iClientNumber]->info.fX = 1000.f;
		g_Clients[g_iClientNumber]->info.fY = 800.f;
		g_Clients[g_iClientNumber]->socket = client_sock;

		hThread = CreateThread(NULL, 0, ProcessClient, NULL, 0, NULL);				// ������ ����

																					// closesocket() - client socket
		if (hThread == NULL)
		{
			closesocket(client_sock);
		}

		else
		{
			CloseHandle(hThread);
		}
	}
	closesocket(client_sock);

	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();

	return 0;
}

DWORD WINAPI ProcessClient(LPVOID arg)
{
	int clientnum = g_iClientNumber++;
	if (g_iClientNumber == 4)
	{
		//
	}

	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(g_Clients[clientnum]->socket, (SOCKADDR *)&clientaddr, &addrlen);

	ULONGLONG ullOldTime = GetTickCount64();

	float iTime = 0.f;

	DWORD dwTime = GetTickCount64();

	while (true)
	{
		RecvInputKey(clientnum);
		SendPlayerInfo(clientnum);
	}

	return 0;
}

DWORD WINAPI WorkThread(LPVOID arg)
{
	int clientnum = -1;
	ULONGLONG ullOldTime = GetTickCount64();

	int frame = 0;
	ULONGLONG ullOldTime2 = GetTickCount64();
	float fTimeDelta = 0.f;

	DWORD dwTime = GetTickCount64();

	while (true)
	{
		// �������� �����Ѵ� 1�ʿ� �� 60
		if (GetTickCount64() - ullOldTime >= 10.f)
		{
			fTimeDelta = GetTickCount64() - ullOldTime;
			fTimeDelta = fTimeDelta / 1000.0f;
			g_fTimeDelta = fTimeDelta;

			Update(fTimeDelta);

			frame++;
			ullOldTime = GetTickCount64();
		}
		// 1�ʿ� �ѹ��� FPS ���� �����Ͽ� ȭ�鿡 ����Ѵ�
		if (GetTickCount64() - ullOldTime2 >= 1000)
		{
			cout << "FPS : " << frame << endl;
			ullOldTime2 = GetTickCount64();
			frame = 0;
		}
	}

	return 0;
}

void RecvInputKey(int clientnum)
{
	int retval = recv(g_Clients[clientnum]->socket, (char *)&g_Clients[clientnum]->keys, sizeof(DWORD), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
}
void RecvPlayerInfo(int clientnum)
{
	int retval = recv(g_Clients[clientnum]->socket, (char *)&g_Clients[clientnum]->info, sizeof(PlayerInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
}
void RecvBulletInfo(int clientnum)
{
	BulletInfo* bulletInfo = new BulletInfo;
	int retval = recv(g_Clients[clientnum]->socket, (char *)&bulletInfo, sizeof(BulletInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
	g_lstBulletInfo.push_back(bulletInfo);
}
void RecvGunInfo(int clientnum)
{
	GunInfo* gunInfo = new GunInfo;
	int retval = recv(g_Clients[clientnum]->socket, (char *)&gunInfo, sizeof(GunInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
	g_lstGunInfo.push_back(gunInfo);
}

void SendPlayerInfo(int clientnum)
{
	cout << g_Clients[clientnum]->info.fX << ", " << g_Clients[clientnum]->info.fY << endl;
	int retval = send(g_Clients[clientnum]->socket, (char *)&g_Clients[clientnum]->info, sizeof(PlayerInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
}

void Update(float fTimeDelta)
{
	for (int i = 0; i < g_iClientNumber; ++i)
	{
		DWORD Key = g_Clients[i]->keys;

		if (Key & KEY_W)
		{
			cout << "W : ";
			g_Clients[i]->info.fY -= fTimeDelta * 30.f;
			cout << g_Clients[i]->info.fX << ", " << g_Clients[i]->info.fY << endl;
		}
		if (Key & KEY_A)
		{
			cout << "A : ";
			g_Clients[i]->info.fX -= fTimeDelta * 30.f;
			cout << g_Clients[i]->info.fX << ", " << g_Clients[i]->info.fY << endl;
		}
		if (Key & KEY_S)
		{
			cout << "S : ";
			g_Clients[i]->info.fY += fTimeDelta * 30.f;
			cout << g_Clients[i]->info.fX << ", " << g_Clients[i]->info.fY << endl;
		}
		if (Key & KEY_D)
		{
			cout << "D : ";
			g_Clients[i]->info.fX += fTimeDelta * 30.f;
			cout << g_Clients[i]->info.fX << ", " << g_Clients[i]->info.fY << endl;
		}
	}
}