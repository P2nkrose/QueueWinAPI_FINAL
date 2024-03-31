#include "pch.h"
#include "qButton.h"

qButton::qButton()
	: m_Func(nullptr)
	, m_NormalImg(nullptr)
	, m_HoverImg(nullptr)
	, m_DownImg(nullptr)
{
	m_NormalImg = qAssetMgr::GetInst()->LoadTexture(L"normal", L"texture\\ui\\btn\\btn1.png");
	m_HoverImg = qAssetMgr::GetInst()->LoadTexture(L"hover", L"texture\\ui\\btn\\btn2.png");
	m_DownImg = qAssetMgr::GetInst()->LoadTexture(L"down", L"texture\\ui\\btn\\btn3.png");
}

qButton::~qButton()
{
}

void qButton::tick()
{
	qUI::tick();

	if (IsLbtnDowned())
	{
		LButtonClicked();
	}
}

void qButton::render()
{
	qUI::render();

	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	if (IsLbtnDowned())
	{
		if (nullptr == m_DownImg)
			qUI::render();

		StretchBlt(DC, (int)vPos.x, (int)vPos.y
			, m_DownImg->GetWidth(), m_DownImg->GetHeight()
			, m_DownImg->GetDC()
			, 0, 0
			, m_DownImg->GetWidth(), m_DownImg->GetHeight(), SRCCOPY);
	}
	else if (IsMouseOn())
	{

		if (nullptr == m_HoverImg)
			qUI::render();

		StretchBlt(DC, (int)vPos.x, (int)vPos.y
			, m_HoverImg->GetWidth(), m_HoverImg->GetHeight()
			, m_HoverImg->GetDC()
			, 0, 0
			, m_HoverImg->GetWidth(), m_HoverImg->GetHeight(), SRCCOPY);
	}
	else
	{
		if (nullptr == m_NormalImg)
			qUI::render();

		StretchBlt(DC, (int)vPos.x, (int)vPos.y
			, m_NormalImg->GetWidth(), m_NormalImg->GetHeight()
			, m_NormalImg->GetDC()
			, 0, 0
			, m_NormalImg->GetWidth(), m_NormalImg->GetHeight(), SRCCOPY);
	}

	
	
}

void qButton::LButtonClicked()
{
	if (nullptr != m_Func)
	{
		m_Func();
	}
}
