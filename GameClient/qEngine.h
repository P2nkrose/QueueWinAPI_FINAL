#pragma once
// ���� �ְ� ������

class qEngine
{
	SINGLE(qEngine)

private:
	HWND		m_hMainWnd;			// ���� ������ �ڵ�
	POINT		m_Resolution;		// ���� ������ �ػ�
	HDC			m_hDC;				// ���� ������ DC

	HDC			m_hSubDC;			// ���� DC
	HBITMAP		m_hSubBitmap;		// ���� Bitmap 

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

