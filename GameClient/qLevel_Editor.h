#pragma once
#include "qLevel.h"

class qTile;
class qPlatform;
class qCamera;

class qLevel_Editor : public qLevel
{
public:
	qLevel_Editor();
	~qLevel_Editor();


private:
	virtual void begin() override;			
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;


private:
	void SaveToFile(const wstring& _strRelativePath);


private:
	qTile*			m_EditTile;

	qPlatform*		m_TestPlatform;
	tInfo			m_TestInfo;

};

