#include "pch.h"
#include "qEffect_missile.h"

#include "qAnimator.h"
#include "qSound.h"

#include "qTaskMgr.h"

qEffect_missile::qEffect_missile()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* MissileEffect = qAssetMgr::GetInst()->LoadTexture(L"MissileEffect", L"texture\\effect\\missile\\missile.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"MissileEffect", MissileEffect, Vec2(0.f, 0.f), Vec2(150.f, 130.f), 8, 10);

	// Animation Save
	m_Animator->FindAnimation(L"MissileEffect")->Save(L"animation\\effect\\missile\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\effect\\missile\\MissileEffect.anim");

	m_Animator->Play(L"MissileEffect", false);

	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\effect\\missile.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

qEffect_missile::qEffect_missile(const qEffect_missile& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qEffect_missile::~qEffect_missile()
{
}

void qEffect_missile::tick()
{
	qObj::tick();

	if (L"MissileEffect" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}

void qEffect_missile::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
