#include "pch.h"
#include "qAnimation.h"

#include "qObj.h"
#include "qAnimation.h"
#include "qAnimator.h"
#include "qTexture.h"

#include "qTimeMgr.h"
#include "qPathMgr.h"

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

	// ������Ʈ�� ��ġ
	Vec2 vPos = pOwnerObj->GetPos();

	// ���� ������ �̹����� ������Ʈ ��ġ�� ������
	TransparentBlt(DC
					, (int)vPos.x - frm.SliceSize.x / 2.f + frm.Offset.x
					, (int)vPos.y - frm.SliceSize.y / 2.f + frm.Offset.y
					, (int)frm.SliceSize.x, (int)frm.SliceSize.y
					, m_Atlas->GetDC()
					, (int)frm.StartPos.x, (int)frm.StartPos.y
					, (int)frm.SliceSize.x, (int)frm.SliceSize.y
					, RGB(255, 0, 255));
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
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� ���� ����");
		return;
	}

	// �ִϸ��̼� ������ ����
	// �ִϸ��̼� �̸� ����
	wstring strAnimName = GetName();
	SaveWString(strAnimName, pFile);


	// ������ ������ ����
	size_t FrmCount = m_vecFrm.size();
	fwrite(&FrmCount, sizeof(size_t), 1, pFile);

	// ������ ������ ������ ����
	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwrite(&m_vecFrm[i], sizeof(tAnimFrm), 1, pFile);
	}
	
	// ��Ʋ�� �ؽ��� ������ ����
	bool bAtlasTex = false;
	if (nullptr != m_Atlas)
		bAtlasTex = true;

	fwrite(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex)
	{
		SaveWString(m_Atlas->GetKey(), pFile);
		SaveWString(m_Atlas->GetRelativePath(), pFile);
	}

	fclose(pFile);

}

int qAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		return E_FAIL;
	}

	// �ִϸ��̼��� ������ �б�
	// �ִϸ��̼� �̸� �б�
	wstring strAnimName;
	LoadWString(strAnimName, pFile);
	SetName(strAnimName);

	// ������ ���� ����
	size_t FrmCount = 0;
	fread(&FrmCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < FrmCount; ++i)
	{
		tAnimFrm frm{};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}

	bool bAtlasTex = false;
	fread(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex)
	{
		wstring strKey;
		LoadWString(strKey, pFile);

		wstring strRelativePath;
		LoadWString(strKey, pFile);

		m_Atlas = qAssetMgr::GetInst()->LoadTexture(strKey, strRelativePath);
	}

	fclose(pFile);

	return S_OK;
}
