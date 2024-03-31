#pragma once
#include "qLevel.h"

class qSound;
class qTexture;

class qLevel_Start : public qLevel
{
public:
	qLevel_Start();
	~qLevel_Start();

public:
	virtual void begin() override;

	virtual void Enter() override;
	virtual void Exit() override;


private:
	qSound* pSound;
	qTexture* m_NormalImg;
	qTexture* m_HoverImg;
	qTexture* m_DownImg;

};

