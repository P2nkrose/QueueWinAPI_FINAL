#pragma once
#include "qUI.h"

class qTexture;

class qMinimap_stage2 : public qUI
{
public:
	CLONE(qMinimap_stage2);

	qMinimap_stage2();
	~qMinimap_stage2();

public:
	virtual void tick() override;
	virtual void render() override;


	void SetMinimapImage(qTexture* _Tex) { m_MinimapImg_stage2 = _Tex; }


private:
	qTexture* m_MinimapImg_stage2;
};

