#include "pch.h"
#include "qBossEffect_firebird.h"

#include "qAnimator.h"
#include "qTaskMgr.h"

qBossEffect_firebird::qBossEffect_firebird()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* FirebirdEffect = qAssetMgr::GetInst()->LoadTexture(L"FirebirdEffect", L"texture\\boss_effect\\firebird\\firebird.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"FirebirdEffect", FirebirdEffect, Vec2(0.f, 0.f), Vec2(180.f, 180.f), 6, 10);

	// Animation Save
	m_Animator->FindAnimation(L"FirebirdEffect")->Save(L"animation\\boss_effect\\firebird\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\boss_effect\\firebird\\FirebirdEffect.anim");

	m_Animator->Play(L"FirebirdEffect", false);
}

qBossEffect_firebird::~qBossEffect_firebird()
{
}

void qBossEffect_firebird::tick()
{
	qObj::tick();

	if (L"FirebirdEffect" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}

void qBossEffect_firebird::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
