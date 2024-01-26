#include "pch.h"
#include "qTimeMgr.h"

#include "qEngine.h"


qTimeMgr::qTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_FPS(0)
	, m_DeltaTime(0.f)
	, m_Time(0.f)
{

}


qTimeMgr::~qTimeMgr()
{

}

void qTimeMgr::init()
{
	// 1�ʿ� �� �� �ִ� ī��Ʈ ������ ��´�.
	QueryPerformanceFrequency(&m_llFrequency);

	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void qTimeMgr::tick()
{
	// ���� ī��Ʈ ���
	QueryPerformanceCounter(&m_llCurCount);

	// ���� ī��Ʈ�� ���� ī��Ʈ�� ���̰��� ���ؼ� 1������ ���� �ð����� ���
	m_DeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	// �����ð��� ���ؼ� ���α׷��� ����� ���ķ� ������ �ð����� ���
	m_Time += m_DeltaTime;

	// ���� ī��Ʈ ���� ���� ī��Ʈ�� �����ص�
	m_llPrevCount = m_llCurCount;

	// �ʴ� ���� Ƚ�� (FPS) ���
	++m_FPS;

	// 1�ʿ� �ѹ��� TextOut ���
	static float AccTime = 0.f;
	AccTime += m_DeltaTime;

	if (1.f < AccTime)
	{
		WCHAR szBuff[255] = {};
		swprintf_s(szBuff, L"DeltaTime : %f, FPS : %d ", m_DeltaTime, m_FPS);
		SetWindowText(qEngine::GetInst()->GetMainWnd(), szBuff);
		AccTime = 0.f;
		m_FPS = 0;
	}
}
