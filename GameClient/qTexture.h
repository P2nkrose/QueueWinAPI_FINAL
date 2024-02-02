#pragma once
#include "qAsset.h"
class qTexture : public qAsset
{
public:
	qTexture();
	~qTexture();


public:
	virtual int Load(const wstring& _strFilePath) override;


private:
	HDC			m_hDC;
	HBITMAP		m_hBit;
};

