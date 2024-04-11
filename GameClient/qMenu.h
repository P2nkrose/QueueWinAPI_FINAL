#pragma once
#include "qUI.h"

class qTexture;

class qMenu : public qUI
{
public:
	CLONE(qMenu);

	qMenu();
	~qMenu();

public:
	virtual void tick_ui() override;
	virtual void render_ui() override;

	void SetImage(qTexture* _Tex) { m_MenuImg = _Tex; }

private:
	qTexture*		m_MenuImg;
	qTexture*		m_MenuNoImg;

};

