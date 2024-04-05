#pragma once


class qMonster_blue;
class qMonster_red;

class qRespawnMgr
{
	SINGLE(qRespawnMgr)

public:
	void init();
	void progress();



private:
	qObj*		m_arrBlue[(UINT)LAYER_TYPE::MONSTER_BLUE];
	qObj*		m_pCurrentBlue;


	qObj*		m_arrRed[(UINT)LAYER_TYPE::MONSTER_RED];
	qObj*		m_pCurrentRed;

	bool		Dead;

};

