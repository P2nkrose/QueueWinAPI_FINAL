#pragma once
#include "qLevel.h"

class qSound;
class qTexture;

class qLevel_stage1 : public qLevel
{
public:
	qLevel_stage1();
	~qLevel_stage1();

	virtual void begin() override;
	virtual void tick() override;
		    
	virtual void Enter() override;
	virtual void Exit() override;

private:
	qSound*			pSound;
	qTexture*		m_Minimap;
};


