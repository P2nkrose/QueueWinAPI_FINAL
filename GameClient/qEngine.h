#pragma once
// ���� �ְ� ������

class qEngine
{
	SINGLE(qEngine)

private:
	HWND		m_hMainWnd;			// ���� ������ �ڵ�
	POINT		m_Resoulution;		// ���� ������ �ػ�
	HDC			m_hDC;				// ���� ������ DC

public:
	int init(HWND _hWnd, POINT _Resolution);
	void progress();

};

