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

    wchar_t szExt[50] = {};
    _wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);

    if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
    {
        m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str()
            , IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        if (nullptr == m_hBit)
        {
            MessageBox(nullptr, L"��Ʈ�� �ε� ����", L"Asset �ε� ����", MB_OK);
            return E_FAIL;
        }
    }
    else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
    {
        ULONG_PTR gdiplusToken = 0;
        GdiplusStartupInput gdiplusinput = {};
        GdiplusStartup(&gdiplusToken, &gdiplusinput, nullptr);

        Image* pImg = Image::FromFile(_strFilePath.c_str(), 0);
        Bitmap* pBitmap = (Bitmap*)pImg->Clone();
        Gdiplus::Status status = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);
        assert(status == Gdiplus::Status::Ok);
    }

    // �ε�� ��Ʈ���� ������ Ȯ���Ѵ�.
    GetObject(m_hBit, sizeof(BITMAP), &m_Info);

    // DC �� �������Ѽ� �ε�� ��Ʈ���̶� �����Ѵ�.
    m_hDC = CreateCompatibleDC(qEngine::GetInst()->GetMainDC());
    DeleteObject(SelectObject(m_hDC, m_hBit));

    return S_OK;
}

int qTexture::Create(UINT _Width, UINT _Height)
{
    // DC ����
    m_hDC = CreateCompatibleDC(qEngine::GetInst()->GetMainDC());

    // Bitmap ����
    m_hBit = CreateCompatibleBitmap(qEngine::GetInst()->GetMainDC(), _Width, _Height);

    // SubDC �� SubBitmap �� �����ϰ� ��
    HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBitmap);

    // �ε�� ��Ʈ���� ������ Ȯ���Ѵ�.
    GetObject(m_hBit, sizeof(BITMAP), &m_Info);

    return S_OK;
}
