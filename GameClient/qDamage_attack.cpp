#include "pch.h"
#include "qDamage_attack.h"

#include "qAnimator.h"
#include "qTaskMgr.h"

qDamage_attack::qDamage_attack()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* DamageAttack = qAssetMgr::GetInst()->LoadTexture(L"DamageAttack", L"texture\\damage\\attack\\attack.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"DamageAttack", DamageAttack, Vec2(0.f, 0.f), Vec2(258.f, 112.f), 11, 10);

	// Animation Save
	m_Animator->FindAnimation(L"DamageAttack")->Save(L"animation\\damage\\attack\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\damage\\attack\\DamageAttack.anim");

	m_Animator->Play(L"DamageAttack", false);

}

qDamage_attack::qDamage_attack(const qDamage_attack& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qDamage_attack::~qDamage_attack()
{
}

void qDamage_attack::tick()
{
	qObj::tick();

	if (L"DamageAttack" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}

