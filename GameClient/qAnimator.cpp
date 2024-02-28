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
	// ���� Animator �� ������ Animation ���� �����ؼ� �����´�.
	for (const auto& pair : _Other.m_mapAnim)
	{
		qAnimation* pCloneAnim = pair.second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pair.first, pCloneAnim));
	}

	// ���� ������� �ִϸ��̼� ����
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
	// ������ �̸��� Animation �� �̹� Animator �� �ִ� ���
	qAnimation* pAnim = FindAnimation(_AnimName);
	assert(!pAnim);

	// Animation ��ü �ϳ��� ������Ų��.
	pAnim = new qAnimation;
	pAnim->Create(_Atlas, _StartPos, _SliceSize, _FrameCount, _FPS);

	// Animation  �� Animator �� ��ϵǴ� �̸�(Ű) �� �˰� �Ѵ�.
	pAnim->SetName(_AnimName);

	// Animation �� ������ �ҼӵǴ� Animator �� �˰� �Ѵ�.
	pAnim->m_Animator = this;

	// Animator �� Animation �� Map �� �ִ´�.
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
	
	// �ִϸ��̼��� ���� ������ ��ηκ��� �ε��� ����
	qAnimation* pNewAnim = new qAnimation;
	if (FAILED(pNewAnim->Load(_strRelativeFilePath)))
	{
		delete pNewAnim;
		LOG(LOG_TYPE::DBG_ERROR, L"�ִϸ��̼� �ε� ����");
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
		LOG(LOG_TYPE::DBG_ERROR, L"Play �� �ִϸ��̼��� ã�� �� ����");
		return;
	}
	m_CurAnim->Reset();
	m_Repeat = _Repeat;
}
