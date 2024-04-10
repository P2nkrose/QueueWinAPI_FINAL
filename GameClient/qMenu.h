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
	virtual void tick() override;
	virtual void render() override;

	void SetMinimapImage(qTexture* _Tex) { m_MenuImg = _Tex; }

private:
	qTexture*		m_MenuImg;
};

