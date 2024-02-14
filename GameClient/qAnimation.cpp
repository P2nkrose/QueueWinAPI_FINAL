#include "pch.h"
#include "qAnimation.h"

#include "qObj.h"
#include "qAnimation.h"
#include "qAnimator.h"
#include "qTexture.h"

#include "qTimeMgr.h"

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
	// ���� ������ ����
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	// Animation �� ����ϰ� �ִ� ������Ʈ
	qObj* pOwnerObj = m_Animator->GetOwner();

	// ������Ʈ�� ��ġ
	Vec2 vPos = pOwnerObj->GetPos();

	// ���� ������ �̹����� ������Ʈ ��ġ�� ������
	TransparentBlt(DC
					, vPos.x - frm.SliceSize.x / 2.f
					, vPos.y - frm.SliceSize.y / 2.f
					, frm.SliceSize.x, frm.SliceSize.y
					, m_Atlas->GetDC()
					, frm.StartPos.x, frm.StartPos.y
					, frm.SliceSize.x, frm.SliceSize.y
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
