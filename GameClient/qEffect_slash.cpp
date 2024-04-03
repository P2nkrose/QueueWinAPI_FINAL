#include "pch.h"
#include "qEffect_slash.h"

#include "qAnimator.h"
#include "qSound.h"

#include "qTaskMgr.h"

qEffect_slash::qEffect_slash()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* SlashEffect = qAssetMgr::GetInst()->LoadTexture(L"SlashEffect", L"texture\\effect\\slash\\slash.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"SlashEffect", SlashEffect, Vec2(0.f, 0.f), Vec2(200.f, 200.f), 7, 10);

	// Animation Save
	m_Animator->FindAnimation(L"SlashEffect")->Save(L"animation\\effect\\slash\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\effect\\slash\\SlashEffect.anim");

	m_Animator->Play(L"SlashEffect", false);

	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\effect\\slash.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

qEffect_slash::qEffect_slash(const qEffect_slash& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qEffect_slash::~qEffect_slash()
{
}

void qEffect_slash::tick()
{
	qObj::tick();

	if (L"SlashEffect" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}

void qEffect_slash::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}



