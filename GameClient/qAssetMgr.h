#pragma once

class qTexture;
class qSound;

class qAssetMgr
{
	SINGLE(qAssetMgr)

public:
	void init();

	qTexture* LoadTexture(const wstring& _Key, const wstring& _strRelativePath);
	qTexture* FindTexture(const wstring& _Key);

private:
	map<wstring, qTexture*> m_mapTex;
	map<wstring, qSound*> m_mapSound;

};

