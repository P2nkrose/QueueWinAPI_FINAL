#include "pch.h"
#include "qBossSkill_tornado.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

qBossSkill_tornado::qBossSkill_tornado()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation �߰�
	qTexture* BossSkillTornado = qAssetMgr::GetInst()->LoadTexture(L"BossSkillTornado", L"texture\\boss_skill\\tornado\\tornado.png");

	// �ִϸ��̼� CREATE
	m_Animator->CreateAnimation(L"BossSkillTornado", BossSkillTornado, Vec2(0.f, 0.f), Vec2(265.f, 600.f), 14, 10);

	// �ִϸ��̼� SAVE
	m_Animator->FindAnimation(L"BossSkillTornado")->Save(L"animation\\boss_skill\\tornado\\");

	// �ִϸ��̼� LOAD
	m_Animator->LoadAnimation(L"animation\\boss_skill\\tornado\\BossSkillTornado.anim");

	m_Animator->Play(L"BossSkillTornado", false);


	// �ݶ��̴�
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
}
