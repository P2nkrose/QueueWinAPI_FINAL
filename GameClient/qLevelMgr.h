#pragma once

class qLevel;



class qLevelMgr
{
	SINGLE(qLevelMgr)

public:
	friend class qTaskMgr;


private:
	qLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];
	qLevel*		m_pCurrentLevel;


private:
	void ChangeLevel(LEVEL_TYPE _NextLevelType);


public:
	qObj* FindObjectByName(const wstring& _StrName);
	

public:
	void init();
	void progress();
	void render();


public:
	qLevel* GetCurrentLevel() { return m_pCurrentLevel; }

};

