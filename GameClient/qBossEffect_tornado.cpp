#include "pch.h"
#include "qBossEffect_tornado.h"

#include "qAnimator.h"
#include "qTaskMgr.h"

qBossEffect_tornado::qBossEffect_tornado()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* TornadoEffect = qAssetMgr::GetInst()->LoadTexture(L"TornadoEffect", L"texture\\boss_effect\\tornado\\tornado.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"TornadoEffect", TornadoEffect, Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10);

	// Animation Save
	m_Animator->FindAnimation(L"TornadoEffect")->Save(L"animation\\boss_effect\\tornado\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\boss_effect\\tornado\\TornadoEffect.anim");

	m_Animator->Play(L"TornadoEffect", false);
}

qBossEffect_tornado::~qBossEffect_tornado()
{
}

void qBossEffect_tornado::tick()
{
	qObj::tick();

	if (L"TornadoEffect" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}

void qBossEffect_tornado::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
