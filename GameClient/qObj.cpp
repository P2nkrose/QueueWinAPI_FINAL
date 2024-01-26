#include "pch.h"
#include "qObj.h"
#include "qEngine.h"

#include "qTimeMgr.h"

qObj::qObj()
{
}

qObj::~qObj()
{
}


void qObj::begin()
{
	
}

void qObj::tick()
{
	// GetAsyncKeyState
	// 0x0000 : �������� �������� ����, ȣ�� �������� �ȴ���������
	// 0x0001 : ������ �������� �ְ�, ȣ�� ������ �ȴ��������� (����)
	// 0x8000 : ������ �������� ����, ȣ�� ������ ���������� (������)
	// 0x8001 : ������ �����ְ�, ȣ�� ������ ���������� (��Ӵ�����)


	// ���ǽð� ����ȭ
	float DT = qTimeMgr::GetInst()->GetDeltaTime();

	float fSpeed = 200.0f;


	if (0x8001 & GetAsyncKeyState(VK_LEFT))
	{
		m_Pos.x -= fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_RIGHT))
	{
		m_Pos.x += fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_UP))
	{
		m_Pos.y -= fSpeed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_DOWN))
	{
		m_Pos.y += fSpeed * DT;
	}
}

void qObj::finaltick()
{
}

void qObj::render()
{
	HDC dc = qEngine::GetInst()->GetMainDC();

	Rectangle(dc, m_Pos.x - m_Scale.x * 0.5f
				, m_Pos.y - m_Scale.y * 0.5f
				, m_Pos.x + m_Scale.x * 0.5f
				, m_Pos.y + m_Scale.y * 0.5f);
}


