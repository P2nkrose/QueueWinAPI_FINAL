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
	// DC ����
	ReleaseDC(m_hMainWnd, m_hDC);

	// Pen ����
	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
	
	// Brush ����
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

	// �Էµ� �ػ󵵸� �������� ���� ���� �������� ũ�⸦ ���
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);


	// ������ ũ�⸦ ����
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// DC, ��, �귯�� ����
	CreateDefaultGDIObject();

	// Manager �ʱ�ȭ
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
	// ȭ�� Clear
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
	// Task ó��
	// =========
	qTaskMgr::GetInst()->tick();
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

	// ���� ��Ʈ��(������) �� ����ϱ� ���� ���� �׸����� �׷����� �ؽ���
	m_SubTex = qAssetMgr::GetInst()->CreateTexture(L"SubTexture", (UINT)m_Resolution.x, (UINT)m_Resolution.y);



	// ���� ����� �� ����
	m_arrPen[(UINT)PEN_TYPE::PEN_RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// ���� ����� �귯�� ����
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
