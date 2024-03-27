#pragma once
#include "qObj.h"

class qTexture;

class qBackground_boss1 : public qObj
{
public:
	CLONE(qBackground_boss1);

public:
	qBackground_boss1();
	~qBackground_boss1();

	void render();
	UINT GetWidth() { return m_Img->GetWidth(); }
	UINT GetHeight() { return m_Img->GetHeight(); }

private:
	qTexture* m_Img;

};

