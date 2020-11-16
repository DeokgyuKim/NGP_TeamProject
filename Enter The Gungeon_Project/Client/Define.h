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
//컬링수정	X
//빅맵		X
//아웃트로
//상자		X
//텔레포트	X
//상점구현	X