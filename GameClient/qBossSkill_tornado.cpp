#include "pch.h"
#include "qBossSkill_tornado.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

#include "qBossEffect_tornado.h"
#include "qDamage_physical.h"

qBossSkill_tornado::qBossSkill_tornado()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* BossSkillTornado = qAssetMgr::GetInst()->LoadTexture(L"BossSkillTornado", L"texture\\boss_skill\\tornado\\tornado.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"BossSkillTornado", BossSkillTornado, Vec2(0.f, 0.f), Vec2(265.f, 600.f), 14, 10);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"BossSkillTornado")->Save(L"animation\\boss_skill\\tornado\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\boss_skill\\tornado\\BossSkillTornado.anim");

	m_Animator->Play(L"BossSkillTornado", false);


	// 콜라이더
	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 22.f));
	m_Collider->SetScale(Vec2(0.f, 0.f));
}

qBossSkill_tornado::~qBossSkill_tornado()
{
}

void qBossSkill_tornado::tick()
{
	qObj::tick();

	if (m_Animator->GetCurAnim()->GetCurFrmIdx() == 3)
	{
		m_Collider->SetScale(Vec2(150.f, 400.f));
	}


	if (L"BossSkillTornado" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}

void qBossSkill_tornado::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::PLAYER == _OtherObj->GetLayerType())
	{
		qBossEffect_tornado* pTornadoEffect = new qBossEffect_tornado;
		pTornadoEffect->SetName(L"TornadoEffect");

		Vec2 vTornadoEffectPos = _OtherObj->GetPos() + Vec2(0.f, -20.f);
		Vec2 vTonardoEffectScale = Vec2(130.f, 130.f);

		pTornadoEffect->SetPos(vTornadoEffectPos);
		pTornadoEffect->SetScale(vTonardoEffectScale);

		if (L"TornadoEffect" == pTornadoEffect->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pTornadoEffect);
		}
	}


	if (LAYER_TYPE::PLAYER == _OtherObj->GetLayerType())
	{
		qDamage_physical* pDamagePhysical = new qDamage_physical;
		pDamagePhysical->SetName(L"DamagePhysical");

		Vec2 vDamagePhysicalPos = _OtherObj->GetPos() + Vec2(0.f, -80.f);
		Vec2 vDamagePhysicalScale = Vec2(181.f, 58.f);

		pDamagePhysical->SetPos(vDamagePhysicalPos);
		pDamagePhysical->SetScale(vDamagePhysicalScale);

		if (L"DamagePhysical" == pDamagePhysical->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pDamagePhysical);
		}
	}


}
