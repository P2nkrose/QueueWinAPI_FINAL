#pragma once
#include "qUI.h"

class qTexture;


class qBossHP : public qUI
{
public:
	CLONE(qBossHP);

	qBossHP();
	~qBossHP();

public:
	virtual void tick_ui() override;
	virtual void render_ui() override;

	void SetImage(qTexture* _Tex) { m_HPImg = _Tex; }


private:
	qTexture*		m_HPImg;

};

