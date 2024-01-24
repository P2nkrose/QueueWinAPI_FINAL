#include "pch.h"
#include "qEngine.h"

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

	// DC (Device Context) 생성
	// DC 란? 렌더링과 관련, 비트맵에 렌더링하기 위해 필요한 필수 정보 집합체
	
	// DC 고유 정보


	m_hDC = GetDC(m_hMainWnd);




	return S_OK;

}

void qEngine::progress()
{

	HPEN redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	HPEN oldPen = (HPEN)SelectObject(m_hDC, redPen);

	Ellipse(m_hDC, 50, 50, 150, 150);

	(HPEN)SelectObject(m_hDC, oldPen);

	Rectangle(m_hDC, 150, 150, 250, 250);

	DeleteObject(redPen);
}
