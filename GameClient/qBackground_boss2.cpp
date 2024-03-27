#include "pch.h"
#include "qBackground_boss2.h"

qBackground_boss2::qBackground_boss2()
{
	m_Img = qAssetMgr::GetInst()->LoadTexture(L"boss2", L"texture\\map\\boss2.png");
}

qBackground_boss2::~qBackground_boss2()
{
}

void qBackground_boss2::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	StretchBlt(DC, (int)vPos.x, (int)vPos.y
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC()
		, 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight(), SRCCOPY);
}
