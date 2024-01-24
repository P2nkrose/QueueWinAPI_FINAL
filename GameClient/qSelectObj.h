#pragma once
class qSelectObj
{

private:
	HDC			m_DC;
	HGDIOBJ		m_hPrev;


public:
	qSelectObj(HDC _dc, HGDIOBJ _SelectedObj);
	~qSelectObj();


};

