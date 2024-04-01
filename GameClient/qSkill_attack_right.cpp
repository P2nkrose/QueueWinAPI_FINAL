#include "pch.h"
#include "qSkill_attack_right.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"


qSkill_attack_right::qSkill_attack_right()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	// 애니메이션
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// 애니메이션 추가
	qTexture* AttackRight = qAssetMgr::GetInst()->LoadTexture(L"AttackRight", L"texture\\skill\\attack\\attack_right.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"AttackRight", AttackRight, Vec2(0.f, 0.f), Vec2(410.f, 240.f), 12, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"AttackRight")->Save(L"animation\\skill\\attack\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\attack\\AttackRight.anim");

	m_Animator->Play(L"AttackRight", false);


	// 콜라이더

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(350.f, 200.f));

}

qSkill_attack_right::qSkill_attack_right(const qSkill_attack_right& _Other)
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_attack_right::~qSkill_attack_right()
{
}

void qSkill_attack_right::tick()
{
	qObj::tick();

	if (L"AttackRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}

void qSkill_attack_right::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
