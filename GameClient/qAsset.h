#pragma once
#include "qEntity.h"
class qAsset : public qEntity
{
public:
	friend class qAssetMgr;
	
	qAsset();
	~qAsset();


public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }

public:
	CLONE_DISABLE(qAsset);
	virtual int Load(const wstring& _strFilePath) = 0;


private:
	wstring		m_Key;			// �ε��� �� ����� Ű
	wstring		m_RelativePath;	// ��� ���


};

