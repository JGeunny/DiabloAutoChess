// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once


#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

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

////// Console 창을 띄우기 위해서...
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
//#endif

// Memory Leak Detection을 위해서...
#include "crtdbg.h"
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif
// Memory Leak Detection을 위해서...//


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