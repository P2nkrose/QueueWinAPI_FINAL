#pragma once
#include "qUI.h"

class qTexture;

class qBossHUD : public qUI
{
public:
	CLONE(qBossHUD);

	qBossHUD();
	~qBossHUD();

public:
	virtual void tick_ui() override;
	virtual void render_ui() override;

	void SetImage(qTexture* _Tex) { m_HUDImg = _Tex; }



private:
	qTexture* m_HUDImg;
};

