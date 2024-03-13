#include "pch.h"
#include "qUI.h"

#include "qTaskMgr.h"

qUI::qUI()
	: m_MouseOn(false)
	, m_MouseLbtnDown(false)
{
}

qUI::~qUI()
{
}

void qUI::tick()
{
	CheckMouseOn();

	if (KEY_RELEASED(KEY::LBTN) && m_MouseLbtnDown)
	{
		qTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::UI_LBTN_DOWN, (DWORD_PTR)this, false });
	}
}

void qUI::render()
{
	qObj::render();

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(DC, (int)(vPos.x), (int)(vPos.y), (int)(vPos.x + vScale.x), (int)(vPos.y + vScale.y));
}

void qUI::CheckMouseOn()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 vMousePos = qKeyMgr::GetInst()->GetMousePos();

	m_MouseOnPrev = m_MouseOn;

	if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x
		&& vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
	{
		m_MouseOn = true;
	}
	else
	{
		m_MouseOn = false;
	}
}

void qUI::LButtonDown()
{
	m_MouseLbtnDown = true;
}

void qUI::LButtonUp()
{
}

void qUI::LButtonClicked()
{
}


