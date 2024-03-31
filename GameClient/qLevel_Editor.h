#pragma once
#include "qLevel.h"

class qTile;
class qTexture;
class qPlatform;
class qRope;
class qPortal;
class qObj;
class qCamera;


class qLevel_Editor : public qLevel
{
public:
	qLevel_Editor();
	~qLevel_Editor();


private:
	virtual void begin() override;			
	virtual void tick() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;


private:
	void Platform();
	void Rope();
	void Portal();
	void Monster();

	void ResetInfo()
	{
		memset(&m_tInfo, sizeof(tInfo), 0);
	}

	void SetType(EDIT_TYPE _EditType) { m_Type = _EditType; }
	EDIT_TYPE GetType() { return m_Type; }


private:
	qTile*			m_EditTile;

	tInfo			m_tInfo;
	EDIT_TYPE		m_Type;

	qTexture*		m_Img;

	qTexture*		m_CurImg;
	qObj*			m_Background;

	//qPlatform*	m_TestPlatform;
	//tInfo			m_TestInfo;

};

