#pragma once
#include "qLevel.h"

class qTile;
class qTexture;
class qPlatform;
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
	void Monster();

	void ResetInfo()
	{
		memset(&m_tInfo, sizeof(tInfo), 0);
	}

	void SetType(EDIT_TYPE _Type) { m_Type = _Type; }
	void SetPlatType(PLATFORM_TYPE _Type) { m_pType = _Type; }

private:
	qTile*			m_EditTile;

	tInfo			m_tInfo;
	EDIT_TYPE		m_Type;
	PLATFORM_TYPE	m_pType;

	qTexture*		m_CurImg;
	qObj*			m_Background;

	//qPlatform*	m_TestPlatform;
	//tInfo			m_TestInfo;

};

