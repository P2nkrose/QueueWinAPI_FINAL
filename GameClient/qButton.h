#pragma once
#include "qUI.h"

typedef void(*BUTTON_CALLBACK)(void);

class qButton : public qUI
{
public:
	CLONE(qButton);

	qButton();
	~qButton();

public:
	virtual void tick_ui() override;
	virtual void render_ui() override;
	virtual void LButtonClicked() override;

public:
	void SetCallBack(BUTTON_CALLBACK _Func) { m_Func = _Func; }

	void SetNormalImage(qTexture* _Tex) { m_NormalImg = _Tex; }
	void SetHoverImage(qTexture* _Tex) { m_HoverImg = _Tex; }
	void SetDownImage(qTexture* _Tex) { m_DownImg = _Tex; }


private:
	BUTTON_CALLBACK		m_Func;
	qTexture*			m_NormalImg;
	qTexture*			m_HoverImg;
	qTexture*			m_DownImg;
};

