#include "pch.h"
#include "qObj.h"
#include "qEngine.h"

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
	if (0x8001 & GetAsyncKeyState(VK_LEFT))
	{
		m_Pos.x -= 0.01f;
	}

	if (0x8001 & GetAsyncKeyState(VK_RIGHT))
	{
		m_Pos.x += 0.01f;
	}

	if (0x8001 & GetAsyncKeyState(VK_UP))
	{
		m_Pos.y -= 0.01f;
	}

	if (0x8001 & GetAsyncKeyState(VK_DOWN))
	{
		m_Pos.y += 0.01f;
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


