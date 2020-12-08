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

#include "TileMgr.h"
#include "COllisionMgr.h"

using namespace std;


int										g_iClientNumber = 0;
unordered_map<int, SERVERPLAYER*>		g_Clients;
list<BulletInfo*>						g_lstBulletInfo;
unordered_map<int, GunInfo*>			g_GunInfo;

float									g_fTimeDelta = 0.f;

CRITICAL_SECTION						g_csInputKey;
CRITICAL_SECTION						g_csBulletInfo;
CRITICAL_SECTION						g_csPlayerInfo;
CRITICAL_SECTION						g_csGunInfo;


DWORD WINAPI ProcessClient(LPVOID arg);
DWORD WINAPI WorkThread(LPVOID arg);

int Update(float fTimeDelta);
void RecvInputKey(int clientnum);
void RecvPlayerInfo(int clientnum);
void RecvGunInfo(int clientnum);

void SendPlayerInfo(int clientnum);
void SendOtherPlayerInfo(int clientnum);
void SendBulletsInfo(int clientnum);
void SendOtherGunInfo(int clientnum);

// ���� �Լ� ���� ���
void err_display(const char *msg)
{
	return;
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}


int recvn(SOCKET s, char * buf, int len, int flags)
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


int main()
{
	CTileMgr::Get_Instance()->LoadData(L"../Data/NgpTile.dat");

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


	InitializeCriticalSection(&g_csInputKey);
	InitializeCriticalSection(&g_csBulletInfo);
	InitializeCriticalSection(&g_csPlayerInfo);
	InitializeCriticalSection(&g_csGunInfo);
	
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
		int option = TRUE;
		setsockopt(listen_sock, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(option));

		if (client_sock == INVALID_SOCKET)
		{
			cout << "accept ����" << endl;
			break;
		}
		cout << "������ Ŭ���̾�Ʈ �� : " << g_iClientNumber + 1 << ", ������ Ŭ���̾�Ʈ ���� : " << client_sock << endl;

		// ������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		g_Clients[g_iClientNumber] = new SERVERPLAYER;
		g_Clients[g_iClientNumber]->info.iPlayerNum = g_iClientNumber;
		if (g_iClientNumber == 0)
		{
			g_Clients[g_iClientNumber]->info.fX = 930.f;
			g_Clients[g_iClientNumber]->info.fY = 672.f;
		}
		else
		{
			g_Clients[g_iClientNumber]->info.fX = 1697.f;
			g_Clients[g_iClientNumber]->info.fY = 1375.f;
		}
		g_Clients[g_iClientNumber]->info.iCX = 60;
		g_Clients[g_iClientNumber]->info.iCY = 60;
		g_Clients[g_iClientNumber]->info.iHP = 6;
		g_Clients[g_iClientNumber]->speed = PLAYER_SPEED;
		g_Clients[g_iClientNumber]->socket = client_sock;
		g_Clients[g_iClientNumber]->roll = false;
		g_Clients[g_iClientNumber]->rollkey = 0;
		
		g_GunInfo[g_iClientNumber] = new GunInfo;
		g_GunInfo[g_iClientNumber]->iOwnerNum = g_iClientNumber;
		g_GunInfo[g_iClientNumber]->fX = 0.f;
		g_GunInfo[g_iClientNumber]->fY = 0.f;
		g_GunInfo[g_iClientNumber]->bReload = false;
		g_GunInfo[g_iClientNumber]->bLeft = false;
		g_GunInfo[g_iClientNumber]->iRenderNum = 0;

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

	DeleteCriticalSection(&g_csInputKey);
	DeleteCriticalSection(&g_csBulletInfo);
	DeleteCriticalSection(&g_csPlayerInfo);
	DeleteCriticalSection(&g_csGunInfo);

	return 0;
}

DWORD WINAPI ProcessClient(LPVOID arg)
{
	int clientnum = g_iClientNumber++;
	while (g_iClientNumber < 2)
	{
	}
	int retval = send(g_Clients[clientnum]->socket, (char *)&clientnum, sizeof(int), 0);

	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(g_Clients[clientnum]->socket, (SOCKADDR *)&clientaddr, &addrlen);


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

			EnterCriticalSection(&g_csInputKey);
			RecvInputKey(clientnum);
			LeaveCriticalSection(&g_csInputKey);

			EnterCriticalSection(&g_csPlayerInfo);
			RecvPlayerInfo(clientnum);
			LeaveCriticalSection(&g_csPlayerInfo);

			EnterCriticalSection(&g_csGunInfo);
			RecvGunInfo(clientnum);
			LeaveCriticalSection(&g_csGunInfo);

			int iEndNum = Update(fTimeDelta);

			EnterCriticalSection(&g_csPlayerInfo);
			SendPlayerInfo(clientnum);
			SendOtherPlayerInfo(clientnum);
			LeaveCriticalSection(&g_csPlayerInfo);

			//retval = send(g_Clients[clientnum]->socket, (char *)&iEndNum, sizeof(int), 0);
			//if (iEndNum != -1)
			//{
			//	int Temp;
			//	if (clientnum == 0)
			//		Temp = 1;
			//	else
			//		Temp = 0;
			//	while (true)
			//	{
			//		retval = send(g_Clients[Temp]->socket, (char *)&iEndNum, sizeof(int), 0);
			//	}
			//	return 0;
			//}

			if (iEndNum != -1)
				exit(0);

			EnterCriticalSection(&g_csGunInfo);
			SendOtherGunInfo(clientnum);
			LeaveCriticalSection(&g_csGunInfo);

			EnterCriticalSection(&g_csBulletInfo);
			SendBulletsInfo(clientnum);
			LeaveCriticalSection(&g_csBulletInfo);

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

DWORD WINAPI WorkThread(LPVOID arg)
{
	int clientnum = -1;
	ULONGLONG ullOldTime = GetTickCount64();

	int frame = 0;
	ULONGLONG ullOldTime2 = GetTickCount64();
	float fTimeDelta = 0.f;

	DWORD dwTime = GetTickCount64();

	//while (true)
	//{
	//	// �������� �����Ѵ� 1�ʿ� �� 60
	//	if (GetTickCount64() - ullOldTime >= 0.2f)
	//	{
	//		fTimeDelta = GetTickCount64() - ullOldTime;
	//		fTimeDelta = fTimeDelta / 1000.0f;
	//		g_fTimeDelta = fTimeDelta;
	//
	//		Update(fTimeDelta);
	//
	//		frame++;
	//		ullOldTime = GetTickCount64();
	//	}
	//	// 1�ʿ� �ѹ��� FPS ���� �����Ͽ� ȭ�鿡 ����Ѵ�
	//	if (GetTickCount64() - ullOldTime2 >= 1000)
	//	{
	//		cout << "FPS : " << frame << endl;
	//		ullOldTime2 = GetTickCount64();
	//		frame = 0;
	//	}
	//}

	return 0;
}

void RecvInputKey(int clientnum)
{
	int retval = recvn(g_Clients[clientnum]->socket, (char *)&g_Clients[clientnum]->keys, sizeof(DWORD), 0);
	if (g_Clients[clientnum]->keys < 0)
		return;
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
	if (g_Clients[clientnum]->keys & KEY_LBUTTON && g_Clients[clientnum]->roll == false)
	{
		BulletInfo* pBulletInfo = new BulletInfo();
		int retval = recvn(g_Clients[clientnum]->socket, (char *)pBulletInfo, sizeof(BulletInfo), 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
		}
		pBulletInfo->iOwnerNum = clientnum;

		EnterCriticalSection(&g_csBulletInfo);
		g_lstBulletInfo.push_back(pBulletInfo);
		LeaveCriticalSection(&g_csBulletInfo);
	}
}
void RecvPlayerInfo(int clientnum)
{
	PlayerInfo tInfo;
	int retval = recvn(g_Clients[clientnum]->socket, (char *)&tInfo, sizeof(PlayerInfo), 0);
	if (tInfo.iFrameStart < 0 || tInfo.iFrameStart > 20)
		return;
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
	wcscpy_s(g_Clients[clientnum]->info.szFrameKey, 30, tInfo.szFrameKey);
	g_Clients[clientnum]->info.iFrameStart = tInfo.iFrameStart;
	g_Clients[clientnum]->info.iFrameVertical = tInfo.iFrameVertical;
}
void RecvBulletInfo(int clientnum)
{
	BulletInfo* bulletInfo = new BulletInfo;
	int retval = recvn(g_Clients[clientnum]->socket, (char *)&bulletInfo, sizeof(BulletInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
	g_lstBulletInfo.push_back(bulletInfo);
}
void RecvGunInfo(int clientnum)
{
	GunInfo gunInfo;
	int retval = recvn(g_Clients[clientnum]->socket, (char *)&gunInfo, sizeof(GunInfo), 0);
	if (gunInfo.iOwnerNum < 0 || gunInfo.iOwnerNum > 2)
		return;
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
	g_GunInfo[clientnum]->fX = gunInfo.fX;
	g_GunInfo[clientnum]->fY = gunInfo.fY;
	g_GunInfo[clientnum]->iOwnerNum = gunInfo.iOwnerNum;
	g_GunInfo[clientnum]->bLeft = gunInfo.bLeft;
	g_GunInfo[clientnum]->iRenderNum = gunInfo.iRenderNum;
	
}

void SendPlayerInfo(int clientnum)
{
	//cout << g_Clients[clientnum]->info.fX << ", " << g_Clients[clientnum]->info.fY << endl;
	int retval = send(g_Clients[clientnum]->socket, (char *)&g_Clients[clientnum]->info, sizeof(PlayerInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
}

void SendOtherPlayerInfo(int clientnum)
{
	int Num = 0;
	if (clientnum == 0)
		Num = 1;
	else
		Num = 0;
	//cout << g_Clients[clientnum]->info.fX << ", " << g_Clients[clientnum]->info.fY << endl;
	int retval = send(g_Clients[clientnum]->socket, (char *)&g_Clients[Num]->info, sizeof(PlayerInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
}

void SendBulletsInfo(int clientnum)
{
	//�Ѿ� ���� �۽�
	int BulletCnt = g_lstBulletInfo.size();
	//cout << BulletCnt << endl;
	int retval = send(g_Clients[clientnum]->socket, (char *)&BulletCnt, sizeof(int), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}

	//�Ѿ� ������ŭ ���� �۽�
	BulletInfo tSendBulletInfo;
	for (auto& iter = g_lstBulletInfo.begin(); iter != g_lstBulletInfo.end(); ++iter)
	{
		tSendBulletInfo = *(*iter);
		retval = send(g_Clients[clientnum]->socket, (char *)&tSendBulletInfo, sizeof(BulletInfo), 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
		}
	}
}

void SendOtherGunInfo(int clientnum)
{
	int Num = 0;
	if (clientnum == 0)
		Num = 1;
	else
		Num = 0;
	//cout << g_Clients[clientnum]->info.fX << ", " << g_Clients[clientnum]->info.fY << endl;
	int retval = send(g_Clients[clientnum]->socket, (char *)g_GunInfo[Num], sizeof(GunInfo), 0);
	if (retval == SOCKET_ERROR)
	{
		err_display("recv()");
		//cout << g_Clients[clientnum]->socket << " recv fail!" << endl;
	}
}

int Update(float fTimeDelta)
{
	for (int i = 0; i < g_iClientNumber; ++i)
	{
		EnterCriticalSection(&g_csInputKey);
		DWORD Key;
		if (g_Clients[i]->roll)
			Key = g_Clients[i]->rollkey;
		else
			Key = g_Clients[i]->keys;
		LeaveCriticalSection(&g_csInputKey);

		//Key �Է� ó��
		EnterCriticalSection(&g_csPlayerInfo);
		if (g_Clients[i]->roll)		//�������ִ���
		{
			float fX = g_Clients[i]->info.fX;
			float fY = g_Clients[i]->info.fY;

			if (Key & KEY_W)
			{
				if (Key & KEY_A)
				{
					g_Clients[i]->info.fX -= fTimeDelta * g_Clients[i]->speed / sqrtf(2);
					g_Clients[i]->info.fY -= fTimeDelta * g_Clients[i]->speed / sqrtf(2);
				}
				else if (Key & KEY_D)
				{
					g_Clients[i]->info.fX += fTimeDelta * g_Clients[i]->speed / sqrtf(2);
					g_Clients[i]->info.fY -= fTimeDelta * g_Clients[i]->speed / sqrtf(2);
				}
				else
				{
					g_Clients[i]->info.fY -= fTimeDelta * g_Clients[i]->speed;
				}
			}
			else if (Key & KEY_S)
			{
				if (Key & KEY_A)
				{
					g_Clients[i]->info.fX -= fTimeDelta * g_Clients[i]->speed / sqrtf(2);
					g_Clients[i]->info.fY += fTimeDelta * g_Clients[i]->speed / sqrtf(2);
				}
				else if (Key & KEY_D)
				{
					g_Clients[i]->info.fX += fTimeDelta * g_Clients[i]->speed / sqrtf(2);
					g_Clients[i]->info.fY += fTimeDelta * g_Clients[i]->speed / sqrtf(2);
				}
				else
				{
					g_Clients[i]->info.fY += fTimeDelta * g_Clients[i]->speed;
				}
			}
			else if (Key & KEY_A)
			{
				g_Clients[i]->info.fX -= fTimeDelta * g_Clients[i]->speed;
			}
			else if (Key & KEY_D)
			{
				g_Clients[i]->info.fX += fTimeDelta * g_Clients[i]->speed;
			}

			g_Clients[i]->speed -= PLAYER_SPEED * 10.f / 60.f;
			if (g_Clients[i]->speed <= PLAYER_SPEED)
			{
				g_Clients[i]->speed = PLAYER_SPEED;
				g_Clients[i]->roll = false;
				g_Clients[i]->rollkey = 0;
			}
			//cout << sqrtf(fabs(g_Clients[i]->info.fX - fX) * fabs(g_Clients[i]->info.fX - fX) +
			//	fabs(g_Clients[i]->info.fY - fY) * fabs(g_Clients[i]->info.fY - fY)) << endl;

		}
		else	//������ �ʰ� �ִ� ��
		{
			float fX = g_Clients[i]->info.fX;
			float fY = g_Clients[i]->info.fY;
			if (Key & KEY_W)
			{
				if (Key & KEY_A)
				{
					g_Clients[i]->info.fX -= fTimeDelta * g_Clients[i]->speed / sqrtf(2);
					g_Clients[i]->info.fY -= fTimeDelta * g_Clients[i]->speed / sqrtf(2);
				}
				else if (Key & KEY_D)
				{
					g_Clients[i]->info.fX += fTimeDelta * g_Clients[i]->speed / sqrtf(2);
					g_Clients[i]->info.fY -= fTimeDelta * g_Clients[i]->speed / sqrtf(2);
				}
				else
				{
					g_Clients[i]->info.fY -= fTimeDelta * g_Clients[i]->speed;
				}
			}
			else if (Key & KEY_S)
			{
				float fX = g_Clients[i]->info.fX;
				float fY = g_Clients[i]->info.fY;
				if (Key & KEY_A)
				{
					g_Clients[i]->info.fX -= fTimeDelta * g_Clients[i]->speed / sqrtf(2);
					g_Clients[i]->info.fY += fTimeDelta * g_Clients[i]->speed / sqrtf(2);
				}
				else if (Key & KEY_D)
				{
					g_Clients[i]->info.fX += fTimeDelta * g_Clients[i]->speed / sqrtf(2);
					g_Clients[i]->info.fY += fTimeDelta * g_Clients[i]->speed / sqrtf(2);
				}
				else
				{
					g_Clients[i]->info.fY += fTimeDelta * g_Clients[i]->speed;
				}
			}
			else if (Key & KEY_A)
			{
				g_Clients[i]->info.fX -= fTimeDelta * g_Clients[i]->speed;
			}
			else if (Key & KEY_D)
			{
				g_Clients[i]->info.fX += fTimeDelta * g_Clients[i]->speed;
			}
			if (Key & KEY_RBUTTON)
			{
				if (g_Clients[i]->roll == false && ((Key & KEY_W) || (Key & KEY_A) || (Key & KEY_S) || (Key & KEY_D)))
				{
					g_Clients[i]->roll = true;
					g_Clients[i]->rollkey = Key;
					g_Clients[i]->speed *= 4.f;
					//cout << "Roll! ";
				}
			}

			//cout << sqrtf(fabs(g_Clients[i]->info.fX - fX) * fabs(g_Clients[i]->info.fX - fX) +
			//	fabs(g_Clients[i]->info.fY - fY) * fabs(g_Clients[i]->info.fY - fY)) << endl;
		}
		CCOllisionMgr::Collision_Object_Wall(&g_Clients[i]->info, CTileMgr::Get_Instance()->Get_Tile());
		PlayerInfo tPlayerInfo = g_Clients[i]->info;
		float fX = tPlayerInfo.fX;
		float fY = tPlayerInfo.fY;
		int iCX = tPlayerInfo.iCX;
		int iCY = tPlayerInfo.iCY;
		LeaveCriticalSection(&g_csPlayerInfo);
		//cout << "Player" << i << ": " << g_Clients[i]->info.fX << ", " << g_Clients[i]->info.fY << endl;

		//Bullet ������Ʈ
		EnterCriticalSection(&g_csBulletInfo);
		bool bColl = false;
		for (auto& iter = g_lstBulletInfo.begin(); iter != g_lstBulletInfo.end();)
		{
			(*iter)->fX += cosf(DEGREETORADIAN((*iter)->fAngle)) * BULLET_SPEED * fTimeDelta;
			(*iter)->fY -= sinf(DEGREETORADIAN((*iter)->fAngle)) * BULLET_SPEED * fTimeDelta;
			(*iter)->fTime += fTimeDelta;


			RECT PlayerRect = {};
			PlayerRect.left = LONG(fX - iCX / 2);
			PlayerRect.top = LONG(fY - iCY * 0.5f);
			PlayerRect.right = LONG(fX + (iCX >> 1));
			PlayerRect.bottom = LONG(fY + (iCY >> 1));

			if (i != (*iter)->iOwnerNum)
			{
				float fBX = (*iter)->fX;
				float fBY = (*iter)->fY;
				int iCBX = (*iter)->iCX;
				int iCBY = (*iter)->iCY;

				RECT BulletRect = {};
				BulletRect.left = LONG(fBX - iCBX / 2);
				BulletRect.top = LONG(fBY - iCBY * 0.5f);
				BulletRect.right = LONG(fBX + (iCBX >> 1));
				BulletRect.bottom = LONG(fBY + (iCBY >> 1));

				RECT temp = {};


				if (IntersectRect(&temp, &PlayerRect, &BulletRect))
				{
					bColl = true;
					cout << "�浹" << endl;
					(*iter)->fTime = 10.f;
				}
			}

			if ((*iter)->fTime >= 10.f)
			{
				delete *iter;
				iter = g_lstBulletInfo.erase(iter);
			}
			else
				++iter;
		}

		CCOllisionMgr::Collision_Bullet_Wall(&g_lstBulletInfo, CTileMgr::Get_Instance()->Get_Tile());
		LeaveCriticalSection(&g_csBulletInfo);

		EnterCriticalSection(&g_csPlayerInfo);
		if (bColl)
			--g_Clients[i]->info.iHP;
		//if (g_Clients[i]->info.iHP <= 0)
		//	return i;
		LeaveCriticalSection(&g_csPlayerInfo);
	}
	return -1;
}