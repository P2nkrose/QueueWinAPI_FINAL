#include "pch.h"
#include "qBossSkill_firebird.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

#include "qBossEffect_firebird.h"
#include "qDamage_magic.h"

qBossSkill_firebird::qBossSkill_firebird()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* BossSkillFirebird = qAssetMgr::GetInst()->LoadTexture(L"BossSkillFirebird", L"texture\\boss_skill\\firebird\\firebird.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"BossSkillFirebird", BossSkillFirebird, Vec2(0.f, 0.f), Vec2(700.f, 400.f), 20, 10);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"BossSkillFirebird")->Save(L"animation\\boss_skill\\firebird\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\boss_skill\\firebird\\BossSkillFirebird.anim");

	m_Animator->Play(L"BossSkillFirebird", false);




	// 콜라이더
	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(10.f, 3.f));
	//m_Collider->SetScale(Vec2(450.f, 300.f));
	m_Collider->SetScale(Vec2(0.f, 0.f));

}

qBossSkill_firebird::~qBossSkill_firebird()
{
}

void qBossSkill_firebird::tick()
{
	qObj::tick();

	if (m_Animator->GetCurAnim()->GetCurFrmIdx() == 12)
	{
		m_Collider->SetScale(Vec2(450.f, 300.f));
	}


	if (L"BossSkillFirebird" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}

void qBossSkill_firebird::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::PLAYER == _OtherObj->GetLayerType())
	{
		qBossEffect_firebird* pFirebirdEffect = new qBossEffect_firebird;
		pFirebirdEffect->SetName(L"FirebirdEffect");

		Vec2 vFirebirdEffectPos = _OtherObj->GetPos() + Vec2(0.f, -20.f);
		Vec2 vFirebirdEffectScale = Vec2(180.f, 180.f);

		pFirebirdEffect->SetPos(vFirebirdEffectPos);
		pFirebirdEffect->SetScale(vFirebirdEffectScale);

		if (L"FirebirdEffect" == pFirebirdEffect->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pFirebirdEffect);
		}
	}

	if (LAYER_TYPE::PLAYER == _OtherObj->GetLayerType())
	{
		qDamage_magic* pDamageMagic = new qDamage_magic;
		pDamageMagic->SetName(L"DamageMagic");

		Vec2 vDamageMagicPos = _OtherObj->GetPos() + Vec2(0.f, -80.f);
		Vec2 vDamageMagicScale = Vec2(181.f, 58.f);

		pDamageMagic->SetPos(vDamageMagicPos);
		pDamageMagic->SetScale(vDamageMagicScale);

		if (L"DamageMagic" == pDamageMagic->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pDamageMagic);
		}
	}
}
