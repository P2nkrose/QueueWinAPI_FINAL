#pragma once
#include "qAsset.h"
class qTexture : public qAsset
{
public:

	friend class qAssetMgr;

	qTexture();
	~qTexture();

public:
	virtual int Load(const wstring& _strFilePath) override;

public:
	HDC GetDC() { return m_hDC; }
	UINT GetWidth() { return m_Info.bmWidth; }
	UINT GetHeight() { return m_Info.bmHeight; }



private:
	HDC			m_hDC;
	HBITMAP		m_hBit;
	BITMAP		m_Info;
};

