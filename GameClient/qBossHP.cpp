#include "pch.h"
#include "qBossHP.h"

qBossHP::qBossHP()
{
	m_HPImg = qAssetMgr::GetInst()->LoadTexture(L"hp", L"texture\\ui\\bosshud\\bosshp.png");
}

qBossHP::~qBossHP()
{
}

void qBossHP::tick_ui()
{
	GetBossHP();

	GetOwner()->GetAttackCount();
	GetOwner()->GetMissileCount();
	GetOwner()->GetSlashCount();
	GetOwner()->GetSpecialCount();
}

void qBossHP::render_ui()
{
	qUI::render_ui();

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	//// AlphaBlending
	//BLENDFUNCTION bf = {};

	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.SourceConstantAlpha = 255;
	//bf.AlphaFormat = AC_SRC_ALPHA;

	//AlphaBlend(DC, (int)(vPos.x)
	//	, (int)(vPos.y)
	//	, m_HPImg->GetWidth(), m_HPImg->GetHeight()
	//	, m_HPImg->GetDC(), 0, 0, m_HPImg->GetWidth(), m_HPImg->GetHeight(), bf);


	StretchBlt(DC, (int)vPos.x, (int)vPos.y
		, m_HPImg->GetWidth() - (m_HPImg->GetWidth() * GetOwner()->GetAttackCount() * 0.02380f + m_HPImg->GetWidth() * GetOwner()->GetMissileCount() * 0.02539f + m_HPImg->GetWidth() * GetOwner()->GetSlashCount() * 0.02698f + m_HPImg->GetWidth() * GetOwner()->GetSpecialCount() * 0.03968f), m_HPImg->GetHeight()
		, m_HPImg->GetDC()
		, 0, 0
		, m_HPImg->GetWidth(), m_HPImg->GetHeight(), SRCCOPY);
}
