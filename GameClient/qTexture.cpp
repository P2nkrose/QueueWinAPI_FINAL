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
    DeleteDC(m_hDC);
    DeleteObject(m_hBit);
}

int qTexture::Load(const wstring& _strFilePath)
{
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str()
        , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    
    if (nullptr == m_hBit)
    {
        MessageBox(nullptr, L"비트맵 로딩 실패", L"Asset 로딩 실패", MB_OK);
        return E_FAIL;
    }

    // 로드된 비트맵의 정보를 확인한다.
    GetObject(m_hBit, sizeof(BITMAP), &m_Info);

    // DC 를 생성시켜서 로드된 비트맵이랑 연결한다.
    m_hDC = CreateCompatibleDC(qEngine::GetInst()->GetMainDC());
    DeleteObject(SelectObject(m_hDC, m_hBit));

    return S_OK;
}

int qTexture::Create(UINT _Width, UINT _Height)
{
    // DC 생성
    m_hDC = CreateCompatibleDC(qEngine::GetInst()->GetMainDC());

    // Bitmap 생성
    m_hBit = CreateCompatibleBitmap(qEngine::GetInst()->GetMainDC(), _Width, _Height);

    // SubDC 가 SubBitmap 을 지정하게 함
    HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBitmap);

    // 로드된 비트맵의 정보를 확인한다.
    GetObject(m_hBit, sizeof(BITMAP), &m_Info);

    return S_OK;
}
