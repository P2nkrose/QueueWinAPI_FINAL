#pragma once

#include <Windows.h>
#include <vector>	// 동적배열
#include <list>		// 연결형 리스트
#include <map>		// 이진탐색트리
#include <string>	// 문자열 전용 관리
#include <assert.h>
#include <ctime>


// TransparentBlt 이 구현되어 있는 라이브러리 링크
#pragma comment(lib, "Msimg32.lib")


using std::vector;
using std::list;
using std::map;
using std::make_pair;

using std::string;
using std::wstring;

#include "define.h"
#include "enum.h"
#include "struct.h"
#include "func.h"
#include "qDbgRender.h"

#include "qSelectObj.h"

// png 로딩 관련 추가
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;


// 사운드
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")
