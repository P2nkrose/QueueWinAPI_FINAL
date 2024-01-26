#pragma once

class qLevel;

class qLevelMgr
{
	SINGLE(qLevelMgr)

private:
	qLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];
	qLevel*		m_pCurrentLevel;

	

public:
	void init();
	void progress();
	void render();

};

