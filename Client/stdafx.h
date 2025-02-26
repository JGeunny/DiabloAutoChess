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


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

// Standard
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <time.h>

#include <io.h>
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

////// Console â�� ���� ���ؼ�...
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
//#endif

// Memory Leak Detection�� ���ؼ�...
#include "crtdbg.h"
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif
// Memory Leak Detection�� ���ؼ�...//


// User
#include "Define.h"
#include "Extern.h"
#include "Enum.h"
#include "Function.h"
#include "Struct.h"

// Managers
#include "TimeMgr.h"
#include "FrameMgr.h"
#include "DeviceMgr.h"
#include "KeyMgr.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "ControlMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "BulletPoolMgr.h"
#include "SoundMgr.h"