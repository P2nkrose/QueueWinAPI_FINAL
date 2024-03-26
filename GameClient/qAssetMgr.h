#pragma once

class qTexture;
class qSound;

class qAssetMgr
{
	SINGLE(qAssetMgr)

public:
	void init();

	qTexture* LoadTexture(const wstring& _Key, const wstring& _strRelativePath);
	qTexture* CreateTexture(const wstring& _Key, UINT _Width, UINT _Height);
	qTexture* FindTexture(const wstring& _Key);

	qSound* LoadSound(const wstring& _Key, const wstring& _strRelativePath);
	qSound* FindSound(const wstring& _Key);


private:
	map<wstring, qTexture*> m_mapTex;
	map<wstring, qSound*> m_mapSound;

};

