#pragma once
#include "qObj.h"

class qCamera;
class qTexture;

class qBackground_stage1 : public qObj
{
public:
	CLONE(qBackground_stage1);

public:
	qBackground_stage1();
	~qBackground_stage1();

	void render();
	UINT GetWidth() { return m_Img->GetWidth(); }
	UINT GetHeight() { return m_Img->GetHeight(); }

private:
	qTexture*		m_Img;
};