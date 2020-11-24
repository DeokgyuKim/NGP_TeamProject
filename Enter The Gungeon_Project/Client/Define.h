#pragma once

#define WINCX		1280
#define WINCY		800

#define TILECX		64
#define TILECY		64
#define TILEX		100
#define TILEY		80

#define OBJ_DEAD		1
#define OBJ_NOEVENT		0
#define OBJ_PLAYERDEAD	-99
#define OBJ_BOSSDEAD	-98

#define PI		3.141592f
#define CAST	static_cast
#define SCAST	static_cast

#define FOLLOW	800
#define SHOT	400

#define RADIANTODEGREE(r)	(r * 180.f / PI)
#define DEGREETORADIAN(r)	(r / 180.f * PI)
#define SAFE_DELETE(p)		if(p) delete p; p = NULL

#define PLAYER_SPEED	4.f

#define MAPFIXX			180
#define MAPFIXY			100


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

//43 6	66 26
//41	16	Left
//41	24	Left
//49	27	Bottom
//67	9	Right
//
//82 6	98 23
//80	9	Left
//
//36 39	53 70
//49	37	top
//54	49	Right
//
//65 35	91 62
//63	49	left
//92	48	right
//�ø�����	X
//���		X
//�ƿ�Ʈ��
//����		X
//�ڷ���Ʈ	X
//��������	X