#include "pch.h"
#include "qPlayerHP.h"

qPlayerHP::qPlayerHP()
{
	m_HPImg = qAssetMgr::GetInst()->LoadTexture(L"playerhp", L"texture\\ui\\menu\\playerhp.png");
}

qPlayerHP::~qPlayerHP()
{
}

void qPlayerHP::tick_ui()
{
	GetPlayerHP();

	GetOwner()->GetPhysicalCount();
	GetOwner()->GetMagicCount();
}

void qPlayerHP::render_ui()
{
	qUI::render_ui();

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	StretchBlt(DC, (int)vPos.x, (int)vPos.y
		, m_HPImg->GetWidth() - (m_HPImg->GetWidth() * GetOwner()->GetPhysicalCount() * 0.0608f + m_HPImg->GetWidth() * GetOwner()->GetMagicCount() * 0.0768f), m_HPImg->GetHeight()
		, m_HPImg->GetDC()
		, 0, 0
		, m_HPImg->GetWidth(), m_HPImg->GetHeight(), SRCCOPY);
}
