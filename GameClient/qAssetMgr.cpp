#include "pch.h"
#include "qAssetMgr.h"

#include "qPathMgr.h"
#include "qTexture.h"
#include "qSound.h"

qAssetMgr::qAssetMgr()
{}

qAssetMgr::~qAssetMgr()
{
    Safe_Del_Map(m_mapTex);

    Safe_Del_Map(m_mapSound);
}

void qAssetMgr::init()
{
}

qTexture* qAssetMgr::LoadTexture(const wstring & _Key, const wstring & _strRelativePath)
{
    // 이미 해당 키로 등록된 텍스쳐가 있으며
    qTexture* pTex = FindTexture(_Key);
    if (nullptr != pTex)
    {
        return pTex;
    }

    // Full Path 로 만들기
    wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // 텍스쳐 객체 생성
    // 텍스쳐 로딩
    pTex = new qTexture;
    if (FAILED(pTex->Load(strFilePath)))
    {
        MessageBox(nullptr, _strRelativePath.c_str(), L"텍스쳐 로딩 실패", MB_OK);
        delete pTex;

        return nullptr;
    }

    // map 에 로딩된 텍스쳐를 등록
    m_mapTex.insert(make_pair(_Key, pTex));

    // 텍스쳐 에셋에 본인의 키값과 상대경로를 알려줌
    pTex->m_Key = _Key;
    pTex->m_RelativePath = _strRelativePath;

    return pTex;

}

qTexture* qAssetMgr::CreateTexture(const wstring& _Key, UINT _Width, UINT _Height)
{
    // 이미 해당키로 등록된 텍스쳐가 있으면
    assert(!FindTexture(_Key));

    // 텍스쳐 객체 생성
    qTexture* pTex = new qTexture;
    if (FAILED(pTex->Create(_Width, _Height)))
    {
        MessageBox(nullptr, _Key.c_str(), L"텍스쳐 생성 실패", MB_OK);
        delete pTex;
        return nullptr;
    }

    // map 에 로딩된 텍스쳐를 등록
    m_mapTex.insert(make_pair(_Key, pTex));

    // 텍스쳐 에셋에 본인의 키값과 상대경로를 알려줌
    pTex->m_Key = _Key;

    return pTex;

}

qTexture* qAssetMgr::FindTexture(const wstring& _Key)
{
    map<wstring, qTexture*>::iterator iter = m_mapTex.find(_Key);

    if (iter == m_mapTex.end())
        return nullptr;

    return iter->second;
}

qSound* qAssetMgr::LoadSound(const wstring& _Key, const wstring& _strRelativePath)
{
    // 이미 해당 키로 등록된 사운드가 있으며
    qSound* pSound = FindSound(_Key);
    if (nullptr != pSound)
    {
        return pSound;
    }

    // Full Path 로 만들기
    wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // 사운드 객체 생성
    // 사운드 로딩
    pSound = new qSound;
    if (FAILED(pSound->Load(strFilePath)))
    {
        MessageBox(nullptr, _strRelativePath.c_str(), L"사운드 로딩 실패", MB_OK);
        delete pSound;
        return nullptr;
    }

    // map 에 로딩된 텍스쳐를 등록
    m_mapSound.insert(make_pair(_Key, pSound));

    // 텍스쳐 에셋에 본인의 키값과 상대경로를 알려줌
    pSound->m_Key = _Key;
    pSound->m_RelativePath = _strRelativePath;

    return pSound;
}

qSound* qAssetMgr::FindSound(const wstring& _Key)
{
    return nullptr;
}
