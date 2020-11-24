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

float									g_fTimeDelta = 0.f;



DWORD WINAPI ProcessClient(LPVOID arg);


// 소켓 함수 오류 출력
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

	// 윈속 초기화
	WSADATA	wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "윈속 초기화 안됨" << endl;
		return 1;
	}

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
	{
		cout << "socket 에러" << endl;
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
		cout << "bind 에러" << endl;
	}

	// listen()
	retval = listen(listen_sock, SOMAXCONN);			// 2명까지만 접속가능
	if (retval == SOCKET_ERROR)
	{
		cout << "listen 에러" << endl;
	}

	// 데이터 통신에 사용할 변수
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
			cout << "accept 에러" << endl;
			break;
		}
		cout << "접속한 클라이언트 수 : " << g_iClientNumber + 1 << ", 접속한 클라이언트 소켓 : " << client_sock << endl;

		// 접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		g_Clients[g_iClientNumber]->socket = client_sock;

		hThread = CreateThread(NULL, 0, ProcessClient, NULL, 0, NULL);				// 스레드 생성

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

	// 윈속 종료
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
		// 프레임을 고정한다 1초에 약 60
		if (GetTickCount64() - ullOldTime >= 10.f)
		{
			fTimeDelta = GetTickCount64() - ullOldTime;
			fTimeDelta = fTimeDelta / 1000.0f;
			g_fTimeDelta = fTimeDelta;

			Update(fTimeDelta);

			frame++;
			ullOldTime = GetTickCount64();
		}
		// 1초에 한번씩 FPS 값을 산출하여 화면에 출력한다
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

void Update(float fTimeDelta)
{
	for (int i = 0; i < g_iClientNumber; ++i)
	{
		DWORD Key = g_Clients[i]->keys;

		if (Key & KEY_W)
		{
			cout << "W" << endl;
		}
		if (Key & KEY_A)
		{
			cout << "A" << endl;
		}
		if (Key & KEY_S)
		{
			cout << "S" << endl;
		}
		if (Key & KEY_D)
		{
			cout << "D" << endl;
		}
	}
}