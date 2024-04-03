#include "pch.h"
#include "qEffect_special.h"

#include "qAnimator.h"
#include "qSound.h"

#include "qTaskMgr.h"


qEffect_special::qEffect_special()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* SpecialEffect = qAssetMgr::GetInst()->LoadTexture(L"SpecialEffect", L"texture\\effect\\special\\special.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"SpecialEffect", SpecialEffect, Vec2(0.f, 0.f), Vec2(330.f, 345.f), 11, 10);

	// Animation Save
	m_Animator->FindAnimation(L"SpecialEffect")->Save(L"animation\\effect\\special\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\effect\\special\\SpecialEffect.anim");

	m_Animator->Play(L"SpecialEffect", false);

	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\effect\\special.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

qEffect_special::qEffect_special(const qEffect_special& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qEffect_special::~qEffect_special()
{
}

void qEffect_special::tick()
{
	qObj::tick();

	if (L"SpecialEffect" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}

void qEffect_special::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
