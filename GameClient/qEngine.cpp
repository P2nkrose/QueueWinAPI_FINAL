#include "pch.h"
#include "qEngine.h"

#include "qLevelMgr.h"

qEngine::qEngine()
	: m_hMainWnd(nullptr)
	, m_Resoulution{}
	, m_hDC(nullptr)
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
	m_Resoulution = _Resolution;

	// ������ �ػ� ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, m_Resoulution.x, m_Resoulution.y, 0);
	
	// DC ����
	CreateDefaultGDIObject();

	// Manager �ʱ�ȭ
	qLevelMgr::GetInst()->init();

	return S_OK;

}

void qEngine::progress()
{
	qLevelMgr::GetInst()->progress();
}

void qEngine::CreateDefaultGDIObject()
{
	// DC(Device Context) ����
	// DC ��? �������� ����
	// ��Ʈ�ʿ� �������ϱ� ���� �ʿ��� �ʼ� ���� ����ü
	m_hDC = ::GetDC(m_hMainWnd);
	// DC ���� ����
	// GetDC �� �����Ǵ� DC �� ����
	// ������ ��Ʈ�� - �Է� �������� ��Ʈ��
	// �� - BlackPen(Default)
	// �귯�� - White Brush(Default)
}
