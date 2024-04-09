#include "pch.h"
#include "qBossSkill_ball_right.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

#include "qBossEffect_ball.h"

qBossSkill_ball_right::qBossSkill_ball_right()
	: m_BallSpeed(500.f)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* BossSkillBallRight = qAssetMgr::GetInst()->LoadTexture(L"BossSkillBallRight", L"texture\\boss_skill\\ball\\ball_right.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"BossSkillBallRight", BossSkillBallRight, Vec2(0.f, 0.f), Vec2(120.f, 60.f), 8, 10);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"BossSkillBallRight")->Save(L"animation\\boss_skill\\ball\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\boss_skill\\ball\\BossSkillBallRight.anim");

	m_Animator->Play(L"BossSkillBallRight", true);



	// 콜라이더
	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(120.f, 60.f));
}

qBossSkill_ball_right::~qBossSkill_ball_right()
{
}

void qBossSkill_ball_right::tick()
{
	qObj::tick();

	Vec2 vPos = GetPos();
	Vec2 vDir = Vec2(1.f, 0.f);

	vPos += vDir * m_BallSpeed * DT;

	SetPos(vPos);
}

void qBossSkill_ball_right::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::PLAYER == _OtherObj->GetLayerType())
	{
		qBossEffect_ball* pBallEffect = new qBossEffect_ball;
		pBallEffect->SetName(L"BallEffect");

		Vec2 vBallEffectPos = _OtherObj->GetPos() + Vec2(-30.f, -20.f);
		Vec2 vBallEffectScale = Vec2(200.f, 200.f);

		pBallEffect->SetPos(vBallEffectPos);
		pBallEffect->SetScale(vBallEffectScale);

		if (L"BallEffect" == pBallEffect->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pBallEffect);
		}
	}

	// 적과 부딪혔을때 Destroy();
	if (_OtherObj->GetName() == L"Player")
	{
		Destroy();
	}
}
