#include "pch.h"
#include "qMinimap_stage2.h"

qMinimap_stage2::qMinimap_stage2()
{
	m_MinimapImg_stage2 = qAssetMgr::GetInst()->LoadTexture(L"minimap_stage2", L"texture\\ui\\minimap\\stage2.png");
}

qMinimap_stage2::~qMinimap_stage2()
{
}

void qMinimap_stage2::tick_ui()
{
	//qUI::tick();
}

void qMinimap_stage2::render_ui()
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
		, m_MinimapImg_stage2->GetWidth(), m_MinimapImg_stage2->GetHeight()
		, m_MinimapImg_stage2->GetDC(), 0, 0, m_MinimapImg_stage2->GetWidth(), m_MinimapImg_stage2->GetHeight(), bf);
}
