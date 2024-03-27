#include "pch.h"
#include "qBackground_stage2.h"

qBackground_stage2::qBackground_stage2()
{
	m_Img = qAssetMgr::GetInst()->LoadTexture(L"stage2", L"texture\\map\\stage2.png");
}

qBackground_stage2::~qBackground_stage2()
{
}

void qBackground_stage2::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	StretchBlt(DC, (int)vPos.x, (int)vPos.y
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC()
		, 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight(), SRCCOPY);
}
