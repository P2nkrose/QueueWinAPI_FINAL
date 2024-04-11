#include "pch.h"
#include "qDamage_physical.h"

#include "qAnimator.h"
#include "qTaskMgr.h"

qDamage_physical::qDamage_physical()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* DamagePhysical = qAssetMgr::GetInst()->LoadTexture(L"DamagePhysical", L"texture\\boss_damage\\physical\\physical.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"DamagePhysical", DamagePhysical, Vec2(0.f, 0.f), Vec2(181.f, 58.f), 11, 10);

	// Animation Save
	m_Animator->FindAnimation(L"DamagePhysical")->Save(L"animation\\boss_damage\\physical\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\boss_damage\\physical\\DamagePhysical.anim");

	m_Animator->Play(L"DamagePhysical", false);
}

qDamage_physical::~qDamage_physical()
{
}

void qDamage_physical::tick()
{
	qObj::tick();

	if (L"DamagePhysical" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}
