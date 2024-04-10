#pragma once
#include "qUI.h"

class qTexture;

class qMinimap_boss2 : public qUI
{
	CLONE(qMinimap_boss2);

public:
	qMinimap_boss2();
	~qMinimap_boss2();

public:
	virtual void tick() override;
	virtual void render() override;


	void SetMinimapImage(qTexture* _Tex) { m_MinimapImg_boss2 = _Tex; }


private:
	qTexture* m_MinimapImg_boss2;
};

