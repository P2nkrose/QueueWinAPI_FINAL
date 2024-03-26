#include "pch.h"
#include "qAnimation.h"

#include "qObj.h"
#include "qAnimation.h"
#include "qAnimator.h"
#include "qTexture.h"

#include "qTimeMgr.h"
#include "qPathMgr.h"
#include "qCamera.h"

qAnimation::qAnimation()
	: m_Animator(nullptr)
	, m_Atlas(nullptr)
	, m_Time(0.f)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
{
}

qAnimation::~qAnimation()
{
}

void qAnimation::finaltick()
{
	if (m_bFinish)
		return;

	// ���� ������ ����
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	m_Time += DT;

	if (frm.Duration <= m_Time)
	{
		m_Time -= frm.Duration;
		++m_CurFrmIdx;

		// �������� �������� �����ߴ�.
		if (m_vecFrm.size() <= m_CurFrmIdx)
		{
			--m_CurFrmIdx;
			m_bFinish = true;
		}
	}

}

void qAnimation::render()
{

	if (nullptr == m_Atlas)
		return;

	// ���� ������ ����
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	// Animation �� ����ϰ� �ִ� ������Ʈ
	qObj* pOwnerObj = m_Animator->GetOwner();

	// ������Ʈ�� ������ ��ġ
	Vec2 vRenderPos = pOwnerObj->GetRenderPos();

	 //AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;


	// ���ĺ���� �׸���
	AlphaBlend(DC
	, (int)vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x
	, (int)vRenderPos.y - frm.SliceSize.y / 2.f + frm.Offset.y
	, frm.SliceSize.x
	, frm.SliceSize.y
	, m_Atlas->GetDC()
	, frm.StartPos.x , frm.StartPos.y
	, frm.SliceSize.x, frm.SliceSize.y
	, bf);


	//// ���� ������ �̹����� ������Ʈ ��ġ�� ������
	//TransparentBlt(DC
	//				, (int)vRenderPos.x - frm.SliceSize.x / 2.f + frm.Offset.x
	//				, (int)vRenderPos.y - frm.SliceSize.y / 2.f + frm.Offset.y
	//				, (int)frm.SliceSize.x, (int)frm.SliceSize.y
	//				, m_Atlas->GetDC()
	//				, (int)frm.StartPos.x, (int)frm.StartPos.y
	//				, (int)frm.SliceSize.x, (int)frm.SliceSize.y
	//				, RGB(255, 0, 255));
}

void qAnimation::Create(qTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	// ������ ���� ����
	for (int i = 0; i < _FrameCount; ++i)
	{
		tAnimFrm frm = {};
		frm.Duration = 1.f / (float)_FPS;
		frm.StartPos = _StartPos + Vec2(_SliceSize.x * i, 0.f);
		frm.SliceSize = _SliceSize;

		m_vecFrm.push_back(frm);
	}
}

void qAnimation::Save(const wstring& _strRelativeFolderPath)
{
	wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFolderPath;
	strFilePath += GetName();
	strFilePath += L".anim";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"w");

	if (nullptr == pFile)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� ���� ����");
		return;
	}

	// �ִϸ��̼� ������ ����
	// �ִϸ��̼� �̸� ����
	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	
	wstring strAnimName = GetName();
	fwprintf_s(pFile, L"%s\n\n", strAnimName.c_str());

	// ��Ʋ�� �ؽ��� ���� ����
	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");

	if (nullptr == m_Atlas)
	{
		fwprintf_s(pFile, L"[ATLAS_KEY]\t%s\n", L"None");
		fwprintf_s(pFile, L"[ATLAS_PATH\t%s\n", L"None");
	}
	else
	{
		fwprintf_s(pFile, L"[ATLAS_KEY]\t%s\n", m_Atlas->GetKey().c_str());
		fwprintf_s(pFile, L"[ATLAS_PATH]\t%s\n", m_Atlas->GetRelativePath().c_str());
	}

	fwprintf_s(pFile, L"\n");

	// ������ ����
	// ������ ������ ����
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", (int)m_vecFrm.size());

	// ������ ������ ������ ����
	size_t FrmCount = m_vecFrm.size();
	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"[FRAME_INDEX]\t%d\n", (int)i);
		fwprintf_s(pFile, L"[START_POS] \t%f  %f\n", m_vecFrm[i].StartPos.x, m_vecFrm[i].StartPos.y);
		fwprintf_s(pFile, L"[SLICE_SIZE]\t\t%f  %f\n", m_vecFrm[i].SliceSize.x, m_vecFrm[i].SliceSize.y);
		fwprintf_s(pFile, L"[OFFSET]\t\t%f  %f\n", m_vecFrm[i].Offset.x, m_vecFrm[i].Offset.y);
		fwprintf_s(pFile, L"[DURATION]  \t%f\n", m_vecFrm[i].Duration);
		fwprintf_s(pFile, L"\n");
	}
	
	fclose(pFile);

}

int qAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	if (nullptr == pFile)
	{
		return E_FAIL;
	}

	// �ִϸ��̼��� ������ �б�
	// �ִϸ��̼� �̸�
	wchar_t szReadBuff[256] = {};

	while (EOF != fwscanf_s(pFile, L"%s", szReadBuff, 256))
	{
		wstring strRead = szReadBuff;

		if (strRead == L"[ANIMATION_NAME]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			SetName(szReadBuff);
		}
		else if (strRead == L"[ATLAS_TEXTURE]")
		{
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			wstring strKey = szReadBuff;

			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			fwscanf_s(pFile, L"%s", szReadBuff, 256);
			wstring strPath = szReadBuff;

			if (strKey != L"None" && strPath != L"None")
			{
				m_Atlas = qAssetMgr::GetInst()->LoadTexture(strKey, strPath);
			}
		}
		else if (strRead == L"[FRAME_COUNT]")
		{
			int frmcount = 0;
			fwscanf_s(pFile, L"%d", &frmcount);

			for (int i = 0; i < frmcount; ++i)
			{
				tAnimFrm frm = {};
				
				// [START_POS] �� ���ö� ���� �о���δ�.

				do { fwscanf_s(pFile, L"%s", szReadBuff, 256); } while (wcscmp(szReadBuff, L"[START_POS]"));

				fwscanf_s(pFile, L"%f%f", &frm.StartPos.x, &frm.StartPos.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &frm.SliceSize.x, &frm.SliceSize.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f%f", &frm.Offset.x, &frm.Offset.y);
				fwscanf_s(pFile, L"%s", szReadBuff, 256);
				fwscanf_s(pFile, L"%f", &frm.Duration);

				m_vecFrm.push_back(frm);
			}
		}
	}
	
	
	fclose(pFile);

	return S_OK;
}
