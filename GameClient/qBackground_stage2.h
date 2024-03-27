#pragma once
#include "qObj.h"

class qCamera;
class qTexture;

class qBackground_stage2 : public qObj
{
public:
	CLONE(qBackground_stage2);


public:
	qBackground_stage2();
	~qBackground_stage2();

	void render();
	UINT GetWidth() { return m_Img->GetWidth(); }
	UINT GetHeight() { return m_Img->GetHeight(); }

private:
	qTexture* m_Img;
};

