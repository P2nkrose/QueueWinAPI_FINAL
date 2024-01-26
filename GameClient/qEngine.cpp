#include "pch.h"
#include "qEngine.h"

#include "qLevelMgr.h"
#include "qTimeMgr.h"

qEngine::qEngine()
	: m_hMainWnd(nullptr)
	, m_Resoulution{}
	, m_hDC(nullptr)
{

}

qEngine::~qEngine()
{
	// DC 삭제
	ReleaseDC(m_hMainWnd, m_hDC);

}

int qEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_Resoulution = _Resolution;

	// 윈도우 해상도 변경
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, m_Resoulution.x, m_Resoulution.y, 0);
	
	// DC 생성
	CreateDefaultGDIObject();

	// Manager 초기화
	qTimeMgr::GetInst()->init();
	qLevelMgr::GetInst()->init();
	


	return S_OK;

}

void qEngine::progress()
{
	qTimeMgr::GetInst()->tick();
	
	qLevelMgr::GetInst()->progress();
	qLevelMgr::GetInst()->render();
}

void qEngine::CreateDefaultGDIObject()
{
	// DC(Device Context) 생성
	// DC 란? 렌더링과 관련
	// 비트맵에 렌더링하기 위해 필요한 필수 정보 집합체
	m_hDC = ::GetDC(m_hMainWnd);
	// DC 보유 정보
	// GetDC 로 생성되는 DC 의 정보
	// 목적지 비트맵 - 입력 윈도우의 비트맵
	// 펜 - BlackPen(Default)
	// 브러쉬 - White Brush(Default)
}
