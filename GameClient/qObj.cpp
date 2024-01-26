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
	// 0x0000 : 이전에도 누른적이 없고, 호출 시점에도 안눌려있을때
	// 0x0001 : 이전에 누른적이 있고, 호출 시점에 안눌려있을때 (뗄떼)
	// 0x8000 : 이전에 누른적이 없고, 호출 시점에 눌려있을때 (누를때)
	// 0x8001 : 이전에 눌려있고, 호출 시점에 눌려있을때 (계속누를때)


	// 현실시간 동기화
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


