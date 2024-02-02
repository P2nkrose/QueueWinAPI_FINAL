#include "pch.h"
#include "qTexture.h"
#include "qEngine.h"

qTexture::qTexture()
    : m_hDC{}
    , m_hBit{}
    , m_Info{}
{
}

qTexture::~qTexture()
{
}

int qTexture::Load(const wstring& _strFilePath)
{
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str()
        , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    
    if (nullptr == m_hBit)
    {
        MessageBox(nullptr, L"��Ʈ�� �ε� ����", L"Asset �ε� ����", MB_OK);
        return E_FAIL;
    }

    // �ε�� ��Ʈ���� ������ Ȯ���Ѵ�.
    GetObject(m_hBit, sizeof(BITMAP), &m_Info);

    // DC �� �������Ѽ� �ε�� ��Ʈ���̶� �����Ѵ�.
    m_hDC = CreateCompatibleDC(qEngine::GetInst()->GetMainDC());
    DeleteObject(SelectObject(m_hDC, m_hBit));

    return S_OK;
}
