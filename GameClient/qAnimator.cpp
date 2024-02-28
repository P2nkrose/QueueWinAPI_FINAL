#include "pch.h"
#include "qAnimator.h"

#include "qAnimation.h"

qAnimator::qAnimator()
	: m_CurAnim(nullptr)
	, m_Repeat(false)
{
}

qAnimator::qAnimator(const qAnimator& _Other)
	: qComponent(_Other)
	, m_CurAnim(nullptr)
	, m_Repeat(_Other.m_Repeat)
{
	// 원본 Animator 가 보유한 Animation 들을 복제해서 가져온다.
	for (const auto& pair : _Other.m_mapAnim)
	{
		qAnimation* pCloneAnim = pair.second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pair.first, pCloneAnim));
	}

	// 현재 재생중인 애니메이션 설정
	if (nullptr != _Other.m_CurAnim)
	{
		m_CurAnim = FindAnimation(_Other.m_CurAnim->GetName());
	}
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
	// 동일한 이름의 Animation 이 이미 Animator 에 있는 경우
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

void qAnimator::LoadAnimation(const wstring& _strRelativeFilePath)
{
	
	// 애니메이션을 만들어서 지정된 경로로부터 로딩을 진행
	qAnimation* pNewAnim = new qAnimation;
	if (FAILED(pNewAnim->Load(_strRelativeFilePath)))
	{
		delete pNewAnim;
		LOG(LOG_TYPE::DBG_ERROR, L"애니메이션 로딩 실패");
		return;
	}
	pNewAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));
}


void qAnimator::Play(const wstring& _AnimName, bool _Repeat)
{
	m_CurAnim = FindAnimation(_AnimName);

	if (nullptr == m_CurAnim)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"Play 할 애니메이션을 찾을 수 없음");
		return;
	}
	m_CurAnim->Reset();
	m_Repeat = _Repeat;
}
