#include "pch.h"
#include "qMenu.h"

qMenu::qMenu()
{
	m_MenuImg = qAssetMgr::GetInst()->LoadTexture(L"menu", L"texture\\ui\\menu\\menu.png");
}

qMenu::~qMenu()
{
}

void qMenu::tick_ui()
{
	//qUI::tick();
}

void qMenu::render_ui()
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
		, m_MenuImg->GetWidth(), m_MenuImg->GetHeight()
		, m_MenuImg->GetDC(), 0, 0, m_MenuImg->GetWidth(), m_MenuImg->GetHeight(), bf);
}
