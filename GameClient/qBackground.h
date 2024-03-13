#pragma once
#include "qObj.h"

class qCamera;
class qTexture;

class qBackground : public qObj
{
public:
	CLONE(qBackground);

public:
	qBackground();
	~qBackground();

	virtual void render();
	UINT GetWidth() { return m_Img->GetWidth(); }
	UINT GetHeight() { return m_Img->GetHeight(); }

private:
	qTexture*		m_Img;
};

