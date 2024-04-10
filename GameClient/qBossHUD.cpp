#include "pch.h"
#include "qBossHUD.h"

qBossHUD::qBossHUD()
{
	m_HUDImg = qAssetMgr::GetInst()->LoadTexture(L"hud", L"texture\\ui\\bosshud\\bosshud.png");
}

qBossHUD::~qBossHUD()
{
}

void qBossHUD::tick_ui()
{
	//qUI::tick();
}

void qBossHUD::render_ui()
{
	qUI::render_ui();

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)(vPos.x)
		, (int)(vPos.y)
		, m_HUDImg->GetWidth(), m_HUDImg->GetHeight()
		, m_HUDImg->GetDC(), 0, 0, m_HUDImg->GetWidth(), m_HUDImg->GetHeight(), bf);




}
