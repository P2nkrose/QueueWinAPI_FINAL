#include "pch.h"
#include "qMinimap_boss1.h"

qMinimap_boss1::qMinimap_boss1()
{
	m_MinimapImg_boss1 = qAssetMgr::GetInst()->LoadTexture(L"minimap_boss1", L"texture\\ui\\minimap\\boss1.png");
}

qMinimap_boss1::~qMinimap_boss1()
{
}

void qMinimap_boss1::tick_ui()
{
	//qUI::tick();
}

void qMinimap_boss1::render_ui()
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
		, m_MinimapImg_boss1->GetWidth(), m_MinimapImg_boss1->GetHeight()
		, m_MinimapImg_boss1->GetDC(), 0, 0, m_MinimapImg_boss1->GetWidth(), m_MinimapImg_boss1->GetHeight(), bf);
}
