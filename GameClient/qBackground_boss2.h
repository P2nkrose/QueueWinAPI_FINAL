#pragma once
#include "qObj.h"

class qTexture;

class qBackground_boss2 : public qObj
{
public:
	CLONE(qBackground_boss2);

public:
	qBackground_boss2();
	~qBackground_boss2();

	void render();
	UINT GetWidth() { return m_Img->GetWidth(); }
	UINT GetHeight() { return m_Img->GetHeight(); }

private:
	qTexture* m_Img;

};

