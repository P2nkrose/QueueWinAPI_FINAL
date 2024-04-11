#pragma once
#include "qUI.h"

class qTexture;

class qPlayerHP : public qUI
{
	CLONE(qPlayerHP);

public:

	qPlayerHP();
	~qPlayerHP();

public:
	virtual void tick_ui() override;
	virtual void render_ui() override;

	void SetImage(qTexture* _Tex) { m_HPImg = _Tex; }


private:
	qTexture* m_HPImg;
};

