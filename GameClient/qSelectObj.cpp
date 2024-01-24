#include "pch.h"
#include "qSelectObj.h"

qSelectObj::qSelectObj(HDC _dc, HGDIOBJ _SelectedObj)
	: m_DC(_dc)
	, m_hPrev(nullptr)
{
	m_hPrev = SelectObject(m_DC, _SelectedObj);
}

qSelectObj::~qSelectObj()
{
	SelectObject(m_DC, m_hPrev);

	
}
