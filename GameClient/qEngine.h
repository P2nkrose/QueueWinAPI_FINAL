#pragma once
// 게임 최고 관리자

class qEngine
{
	SINGLE(qEngine)

private:
	HWND		m_hMainWnd;			// 메인 윈도우 핸들
	POINT		m_Resoulution;		// 메인 윈도우 해상도
	HDC			m_hDC;				// 메인 윈도우 DC

public:
	int init(HWND _hWnd, POINT _Resolution);
	void progress();

};

