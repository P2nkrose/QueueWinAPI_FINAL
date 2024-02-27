#include "pch.h"
#include "qEngine.h"

#include "qPathMgr.h"
#include "qLevelMgr.h"
#include "qTimeMgr.h"
#include "qDbgRender.h"
#include "qKeyMgr.h"
#include "qCollisionMgr.h"
#include "qAssetMgr.h"
#include "qTaskMgr.h"
#include "qCamera.h"

#include "qTexture.h"

qEngine::qEngine()
	: m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_hDC(nullptr)
	, m_arrPen{}
	, m_arrBrush{}
{

}

qEngine::~qEngine()
{
	// DC 삭제
	ReleaseDC(m_hMainWnd, m_hDC);

	// Pen 삭제
	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
	
	// Brush 삭제
	for (int i = 0; i < (UINT)BRUSH_TYPE::END; i++)
	{
		DeleteObject(m_arrBrush[i]);
	}

}

int qEngine::init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution)
{
	m_hInstance = _hInst;
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	// 입력된 해상도를 가져가기 위한 실제 윈도우의 크기를 계산
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);


	// 윈도우 크기를 변경
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// DC, 펜, 브러쉬 생성
	CreateDefaultGDIObject();

	// Manager 초기화
	qPathMgr::GetInst()->init();
	qKeyMgr::GetInst()->init();
	qTimeMgr::GetInst()->init();
	
	qAssetMgr::GetInst()->init();
	qLevelMgr::GetInst()->init();

	qCamera::GetInst()->init();
	


	return S_OK;

}

void qEngine::progress()
{
	// ============
	// Manager Tick
	// ============
	qTimeMgr::GetInst()->tick();
	qKeyMgr::GetInst()->tick();
	qDbgRender::GetInst()->tick();
	qCamera::GetInst()->tick();

	// ==============
	// Level Progress
	// ==============
	qLevelMgr::GetInst()->progress();
	qCollisionMgr::GetInst()->tick();

	// =========
	// Rendering
	// =========
	// 화면 Clear
	{
		USE_BRUSH(m_SubTex->GetDC(), BRUSH_TYPE::BRUSH_GRAY);
		Rectangle(m_SubTex->GetDC(), -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	qLevelMgr::GetInst()->render();
	qCamera::GetInst()->render();
	qDbgRender::GetInst()->render();

	// Sub -> Main
	BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_SubTex->GetDC(), 0, 0, SRCCOPY);

	// =========
	// Task 처리
	// =========
	qTaskMgr::GetInst()->tick();
}

void qEngine::CreateDefaultGDIObject()
{
	// DC(Device Context) 생성
	// DC 란? 렌더링과 관련
	// 비트맵에 렌더링하기 위해 필요한 필수 정보 집합체
	// DC 보유 정보
	// GetDC 로 생성되는 DC 의 정보
	// 목적지 비트맵 - 입력 윈도우의 비트맵

	// 메인 윈도우를 타겟으로 지정하는 DC 생성
	m_hDC = ::GetDC(m_hMainWnd);

	// 메인 비트맵(윈도우) 에 출력하기 전에 먼저 그림들이 그려지는 텍스쳐
	m_SubTex = qAssetMgr::GetInst()->CreateTexture(L"SubTexture", (UINT)m_Resolution.x, (UINT)m_Resolution.y);



	// 자주 사용할 펜 생성
	m_arrPen[(UINT)PEN_TYPE::PEN_RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// 자주 사용할 브러쉬 생성
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);


}

HDC qEngine::GetSubDC()
{
	return m_SubTex->GetDC();
}
