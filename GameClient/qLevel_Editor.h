#pragma once
#include "qLevel.h"

class qTile;

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
	qTile*		m_EditTile;

};

