#include "pch.h"
#include "qMinimap_boss2.h"

qMinimap_boss2::qMinimap_boss2()
{
	m_MinimapImg_boss2 = qAssetMgr::GetInst()->LoadTexture(L"minimap_boss2", L"texture\\ui\\minimap\\boss2.png");
}

qMinimap_boss2::~qMinimap_boss2()
{
}

void qMinimap_boss2::tick()
{
	qUI::tick();
}

void qMinimap_boss2::render()
{
	qUI::render();

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
		, m_MinimapImg_boss2->GetWidth(), m_MinimapImg_boss2->GetHeight()
		, m_MinimapImg_boss2->GetDC(), 0, 0, m_MinimapImg_boss2->GetWidth(), m_MinimapImg_boss2->GetHeight(), bf);
}
