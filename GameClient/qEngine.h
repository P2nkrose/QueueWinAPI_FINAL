#pragma once
// 게임 최고 관리자

class qEngine
{
	SINGLE(qEngine)

private:
	HWND		m_hMainWnd;			// 메인 윈도우 핸들
	POINT		m_Resolution;		// 메인 윈도우 해상도
	HDC			m_hDC;				// 메인 윈도우 DC

	HDC			m_hSubDC;			// 보조 DC
	HBITMAP		m_hSubBitmap;		// 보조 Bitmap 

public:
	int init(HWND _hWnd, POINT _Resolution);
	void progress();

private:
	void CreateDefaultGDIObject();


public:
	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }

	HDC GetSubDC() { return m_hSubDC; }
};

