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
	// FinalPos °è»ê
	m_vFinalPos = GetPos();

	CheckMouseOn();

	if (KEY_RELEASED(KEY::LBTN) && m_MouseLbtnDown)
	{
		qTaskMgr::GetInst()->AddTask(tTask{ TASK_TYPE::UI_LBTN_DOWN, (DWORD_PTR)this, false });
	}

	tick_ui();
}

void qUI::render()
{
	qObj::render();

	render_ui();


}

void qUI::render_ui()
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
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


