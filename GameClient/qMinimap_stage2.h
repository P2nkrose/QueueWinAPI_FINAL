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
	virtual void tick_ui() override;
	virtual void render_ui() override;


	void SetImage(qTexture* _Tex) { m_MinimapImg_stage2 = _Tex; }


private:
	qTexture* m_MinimapImg_stage2;
};

