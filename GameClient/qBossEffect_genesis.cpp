#include "pch.h"
#include "qBossEffect_genesis.h"

#include "qAnimator.h"
#include "qTaskMgr.h"

qBossEffect_genesis::qBossEffect_genesis()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* GenesisEffect = qAssetMgr::GetInst()->LoadTexture(L"GenesisEffect", L"texture\\boss_effect\\genesis\\genesis.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"GenesisEffect", GenesisEffect, Vec2(0.f, 0.f), Vec2(200.f, 200.f), 6, 10);

	// Animation Save
	m_Animator->FindAnimation(L"GenesisEffect")->Save(L"animation\\boss_effect\\genesis\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\boss_effect\\genesis\\GenesisEffect.anim");

	m_Animator->Play(L"GenesisEffect", false);
}

qBossEffect_genesis::~qBossEffect_genesis()
{
}

void qBossEffect_genesis::tick()
{
	qObj::tick();

	if (L"GenesisEffect" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}

void qBossEffect_genesis::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
