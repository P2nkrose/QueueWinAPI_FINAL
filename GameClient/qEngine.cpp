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
	// DC ����
	ReleaseDC(m_hMainWnd, m_hDC);

}

int qEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	// �Էµ� �ػ󵵸� �������� ���� ���� �������� ũ�⸦ ���
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);


	// ������ ũ�⸦ ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// DC ����
	CreateDefaultGDIObject();

	// Manager �ʱ�ȭ
	qTimeMgr::GetInst()->init();
	qLevelMgr::GetInst()->init();
	


	return S_OK;

}

void qEngine::progress()
{
	qTimeMgr::GetInst()->tick();
	qLevelMgr::GetInst()->progress();


	// ȭ�� Clear
	{
		Rectangle(m_hSubDC, -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	qLevelMgr::GetInst()->render();

	// Sub -> Main
	BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_hSubDC, 0, 0, SRCCOPY);
}

void qEngine::CreateDefaultGDIObject()
{
	// DC(Device Context) ����
	// DC ��? �������� ����
	// ��Ʈ�ʿ� �������ϱ� ���� �ʿ��� �ʼ� ���� ����ü
	// DC ���� ����
	// GetDC �� �����Ǵ� DC �� ����
	// ������ ��Ʈ�� - �Է� �������� ��Ʈ��

	// ���� �����츦 Ÿ������ �����ϴ� DC ����
	m_hDC = ::GetDC(m_hMainWnd);

	// Sub DC ����
	m_hSubDC = CreateCompatibleDC(m_hDC);

	// Sub Bitmap ����
	m_hSubBitmap = CreateCompatibleBitmap(m_hDC, m_Resolution.x, m_Resolution.y);

	// SubDC �� SubBitmap �� �����ϰ� ��
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hSubDC, m_hSubBitmap);
	DeleteObject(hPrevBitmap);


}
