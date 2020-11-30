// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <time.h>
#include <string>
using namespace std; 
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")
#include "fmod.h"
#pragma comment(lib,"fmodex_vc.lib")
#include <io.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Extern.h"
#include "Define.h"
#include "Struct.h"
#include "Enum.h"
#include "Functor.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"
#include "SoundMgr.h"


#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif