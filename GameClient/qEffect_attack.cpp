#include "pch.h"
#include "qEffect_attack.h"

#include "qAnimator.h"
#include "qSound.h"

#include "qTaskMgr.h"

qEffect_attack::qEffect_attack()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* AttackEffect = qAssetMgr::GetInst()->LoadTexture(L"AttackEffect", L"texture\\effect\\attack\\attack.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"AttackEffect", AttackEffect, Vec2(0.f, 0.f), Vec2(150.f, 150.f), 8, 10);

	// Animation Save
	m_Animator->FindAnimation(L"AttackEffect")->Save(L"animation\\effect\\attack\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\effect\\attack\\AttackEffect.anim");

	m_Animator->Play(L"AttackEffect", false);

	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\effect\\attack.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

qEffect_attack::qEffect_attack(const qEffect_attack& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qEffect_attack::~qEffect_attack()
{
}

void qEffect_attack::tick()
{
	qObj::tick();

	if (L"AttackEffect" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}

void qEffect_attack::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{

}
