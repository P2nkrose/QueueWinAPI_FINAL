#include "pch.h"
#include "qMinimap_stage1.h"

qMinimap_stage1::qMinimap_stage1()
{
	m_MinimapImg_stage1 = qAssetMgr::GetInst()->LoadTexture(L"minimap_stage1", L"texture\\ui\\minimap\\stage1.png");
}

qMinimap_stage1::~qMinimap_stage1()
{
}

void qMinimap_stage1::tick()
{
	qUI::tick();
}

void qMinimap_stage1::render()
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
		, m_MinimapImg_stage1->GetWidth(), m_MinimapImg_stage1->GetHeight()
		, m_MinimapImg_stage1->GetDC(), 0, 0, m_MinimapImg_stage1->GetWidth(), m_MinimapImg_stage1->GetHeight(), bf);
}
