#pragma once
#include "qUI.h"

class qTexture;

class qMinimap_stage1 : public qUI
{
public:
	CLONE(qMinimap_stage1);

	qMinimap_stage1();
	~qMinimap_stage1();

public:
	virtual void tick() override;
	virtual void render() override;


	void SetMinimapImage(qTexture* _Tex) { m_MinimapImg_stage1 = _Tex; }


private:
	qTexture*		m_MinimapImg_stage1;
};

