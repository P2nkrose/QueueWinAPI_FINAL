#include "pch.h"
#include "qBackground_boss1.h"

qBackground_boss1::qBackground_boss1()
{
	m_Img = qAssetMgr::GetInst()->LoadTexture(L"boss1", L"texture\\map\\boss1.png");
}

qBackground_boss1::~qBackground_boss1()
{
}

void qBackground_boss1::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	StretchBlt(DC, (int)vPos.x, (int)vPos.y
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC()
		, 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight(), SRCCOPY);
}
