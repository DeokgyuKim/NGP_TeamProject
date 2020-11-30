#pragma once

#define KEY_W	 	1 			//Ű���� ��W�� Ű, ���� �̵�
#define KEY_A	 	2			//Ű���� ��A�� Ű, ���� �̵�
#define KEY_S 	 	4			//Ű���� ��S�� Ű, �Ʒ��� �̵�
#define KEY_D	 	8			//Ű���� ��D�� Ű, ������ �̵�
#define KEY_LBUTTON	16			//���콺 ��Ŭ��, �Ѿ� �߻�
#define KEY_RBUTTON	32			//���콺 ��Ŭ��, ������
#define KEY_R		64			//Ű���� ��R�� Ű, �Ѿ� ������	

#define MSG_PLAYERINFO	1
#define MSG_BULLETINFO	2
#define MSG_GUNINFO	3
#define MSG_KEYINFO	4

#define MAX_BUFFER 1024
#define SERVERPORT 9000

#define PLAYER_SPEED	256.f
#define BULLET_SPEED	640.f

#define PI		3.141592f

#define RADIANTODEGREE(r)	(r * 180.f / PI)
#define DEGREETORADIAN(r)	(r / 180.f * PI)
