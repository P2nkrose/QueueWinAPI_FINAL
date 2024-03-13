#include "pch.h"
#include "qButton.h"

qButton::qButton()
	: m_Func(nullptr)
	, m_NormalImg(nullptr)
	, m_HoverImg(nullptr)
	, m_DownImg(nullptr)
{
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

	if (IsLbtnDowned())
	{
		if (nullptr == m_DownImg)
			qUI::render();
	}
	else if (IsMouseOn())
	{

		if (nullptr == m_HoverImg)
			qUI::render();
	}
	else
	{
		if (nullptr == m_NormalImg)
			qUI::render();
	}
}

void qButton::LButtonClicked()
{
	if (nullptr != m_Func)
	{
		m_Func();
	}
}
