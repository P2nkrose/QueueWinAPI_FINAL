#pragma once
#include "qLevel.h"

class qSound;
class qTexture;

class qLevel_boss2 : public qLevel
{
public:
	qLevel_boss2();
	~qLevel_boss2();

public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void Enter() override;
	virtual void Exit() override;

private:
	qSound*			pSound;
	qTexture*		m_Minimap;
	qTexture*		m_Menu;
	qTexture*		m_BossHud;
	qTexture*		m_BossHp;
};

