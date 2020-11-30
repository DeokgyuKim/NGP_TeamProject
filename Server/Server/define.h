#pragma once

#define KEY_W	 	1 			//키보드 ’W’ 키, 위쪽 이동
#define KEY_A	 	2			//키보드 ’A’ 키, 왼쪽 이동
#define KEY_S 	 	4			//키보드 ‘S’ 키, 아래쪽 이동
#define KEY_D	 	8			//키보드 ‘D’ 키, 오른쪽 이동
#define KEY_LBUTTON	16			//마우스 좌클릭, 총알 발사
#define KEY_RBUTTON	32			//마우스 우클릭, 구르기
#define KEY_R		64			//키보드 ‘R’ 키, 총알 장전←	

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
