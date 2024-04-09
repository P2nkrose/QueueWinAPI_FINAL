#include "pch.h"
#include "qBossEffect_ball.h"

#include "qAnimator.h"

#include "qTaskMgr.h"


qBossEffect_ball::qBossEffect_ball()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* BallEffect = qAssetMgr::GetInst()->LoadTexture(L"BallEffect", L"texture\\boss_effect\\ball\\ball.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"BallEffect", BallEffect, Vec2(0.f, 0.f), Vec2(200.f, 200.f), 6, 10);

	// Animation Save
	m_Animator->FindAnimation(L"BallEffect")->Save(L"animation\\boss_effect\\ball\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\boss_effect\\ball\\BallEffect.anim");

	m_Animator->Play(L"BallEffect", false);


}

qBossEffect_ball::~qBossEffect_ball()
{
}

void qBossEffect_ball::tick()
{
	qObj::tick();

	if (L"BallEffect" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}

void qBossEffect_ball::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
