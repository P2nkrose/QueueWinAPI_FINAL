#include "pch.h"
#include "qEngine.h"

#include "qLevelMgr.h"
#include "qTimeMgr.h"

qEngine::qEngine()
	: m_hMainWnd(nullptr)
	, m_Resolution{}
	, m_hDC(nullptr)
	, m_hSubDC(nullptr)
	, m_hSubBitmap(nullptr)
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
	m_Resolution = _Resolution;

	// 입력된 해상도를 가져가기 위한 실제 윈도우의 크기를 계산
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);


	// 윈도우 크기를 변경
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
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


	// 화면 Clear
	{
		Rectangle(m_hSubDC, -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	qLevelMgr::GetInst()->render();

	// Sub -> Main
	BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_hSubDC, 0, 0, SRCCOPY);
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

	// Sub DC 생성
	m_hSubDC = CreateCompatibleDC(m_hDC);

	// Sub Bitmap 생성
	m_hSubBitmap = CreateCompatibleBitmap(m_hDC, m_Resolution.x, m_Resolution.y);

	// SubDC 가 SubBitmap 을 지정하게 함
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hSubDC, m_hSubBitmap);
	DeleteObject(hPrevBitmap);


}
