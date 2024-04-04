#include "pch.h"
#include "qDamage_special.h"

#include "qAnimator.h"
#include "qTaskMgr.h"

qDamage_special::qDamage_special()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* DamageSpecial = qAssetMgr::GetInst()->LoadTexture(L"DamageSpecial", L"texture\\damage\\special\\special.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"DamageSpecial", DamageSpecial, Vec2(0.f, 0.f), Vec2(258.f, 112.f), 11, 10);

	// Animation Save
	m_Animator->FindAnimation(L"DamageSpecial")->Save(L"animation\\damage\\special\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\damage\\special\\DamageSpecial.anim");

	m_Animator->Play(L"DamageSpecial", false);
}

qDamage_special::qDamage_special(const qDamage_special& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qDamage_special::~qDamage_special()
{
}

void qDamage_special::tick()
{
	qObj::tick();

	if (L"DamageSpecial" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}
