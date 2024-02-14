#include "pch.h"
#include "qAnimator.h"

#include "qAnimation.h"

qAnimator::qAnimator()
	: m_CurAnim(nullptr)
{
}

qAnimator::~qAnimator()
{
	Safe_Del_Map(m_mapAnim);
}

void qAnimator::finaltick()
{
	if (nullptr != m_CurAnim)
	{

		if (m_CurAnim->IsFinish() && m_Repeat)
		{
			m_CurAnim->Reset();
		}

		m_CurAnim->finaltick();
	}
}

void qAnimator::render()
{
	if (nullptr != m_CurAnim)
	{
		m_CurAnim->render();
	}
}

void qAnimator::CreateAnimation(const wstring& _AnimName, qTexture* _Atlas, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	// 동일한 이름의 Animatio 이 이미 Animator 에 있는 경우
	qAnimation* pAnim = FindAnimation(_AnimName);
	assert(!pAnim);

	// Animation 객체 하나를 생성시킨다.
	pAnim = new qAnimation;
	pAnim->Create(_Atlas, _StartPos, _SliceSize, _FrameCount, _FPS);

	// Animation  이 Animator 에 등록되는 이름(키) 을 알게 한다.
	pAnim->SetName(_AnimName);

	// Animation 에 본인이 소속되는 Animator 를 알게 한다.
	pAnim->m_Animator = this;

	// Animator 가 Animation 을 Map 에 넣는다.
	m_mapAnim.insert(make_pair(_AnimName, pAnim));
}

qAnimation* qAnimator::FindAnimation(const wstring& _AnimName)
{
	map<wstring, qAnimation*>::iterator iter = m_mapAnim.find(_AnimName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void qAnimator::Play(const wstring& _AnimName, bool _Repeat)
{
	m_CurAnim = FindAnimation(_AnimName);
	m_CurAnim->Reset();
	m_Repeat = _Repeat;
}
