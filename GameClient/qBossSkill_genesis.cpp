#include "pch.h"
#include "qBossSkill_genesis.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

qBossSkill_genesis::qBossSkill_genesis()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* BossSkillGenesis = qAssetMgr::GetInst()->LoadTexture(L"BossSkillGenesis", L"texture\\boss_skill\\genesis\\genesis.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"BossSkillGenesis", BossSkillGenesis, Vec2(0.f, 0.f), Vec2(300.f, 590.f), 26, 10);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"BossSkillGenesis")->Save(L"animation\\boss_skill\\genesis\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\boss_skill\\genesis\\BossSkillGenesis.anim");

	m_Animator->Play(L"BossSkillGenesis", false);


	// 콜라이더
	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 10.f));
	m_Collider->SetScale(Vec2(190.f, 550.f));
}

qBossSkill_genesis::~qBossSkill_genesis()
{

}

void qBossSkill_genesis::tick()
{
	qObj::tick();

	if (L"BossSkillGenesis" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}

}

void qBossSkill_genesis::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
