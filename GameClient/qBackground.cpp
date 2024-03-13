#include "pch.h"
#include "qBackground.h"

qBackground::qBackground()
{
	m_Img = qAssetMgr::GetInst()->LoadTexture(L"stage1", L"texture\\map\\stage1.png");
}

qBackground::~qBackground()
{
}

void qBackground::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
		, (int)(vPos.x - m_Img->GetWidth() * 0.5f)
		, (int)(vPos.y - m_Img->GetHeight() * 0.5f)
		, m_Img->GetWidth()
		, m_Img->GetHeight()
		, m_Img->GetDC()
		, 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight()
		, bf);
}
