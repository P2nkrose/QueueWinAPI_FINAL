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
    // �̹� �ش� Ű�� ��ϵ� �ؽ��İ� ������
    qTexture* pTex = FindTexture(_Key);
    if (nullptr != pTex)
    {
        return pTex;
    }

    // Full Path �� �����
    wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    // �ؽ��� ��ü ����
    // �ؽ��� �ε�
    pTex = new qTexture;
    if (FAILED(pTex->Load(strFilePath)))
    {
        MessageBox(nullptr, _strRelativePath.c_str(), L"�ؽ��� �ε� ����", MB_OK);
        delete pTex;

        return nullptr;
    }

    // map �� �ε��� �ؽ��ĸ� ���
    m_mapTex.insert(make_pair(_Key, pTex));

    // �ؽ��� ���¿� ������ Ű���� ����θ� �˷���
    pTex->m_Key = _Key;
    pTex->m_RelativePath = _strRelativePath;

    return pTex;

}

qTexture* qAssetMgr::FindTexture(const wstring& _Key)
{
    map<wstring, qTexture*>::iterator iter = m_mapTex.find(_Key);

    if (iter == m_mapTex.end())
        return nullptr;

    return iter->second;
}
