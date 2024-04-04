#include "pch.h"
#include "qDamage_missile.h"

#include "qAnimator.h"
#include "qTaskMgr.h"


qDamage_missile::qDamage_missile()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* DamageMissile = qAssetMgr::GetInst()->LoadTexture(L"DamageMissile", L"texture\\damage\\missile\\missile.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"DamageMissile", DamageMissile, Vec2(0.f, 0.f), Vec2(258.f, 112.f), 11, 10);

	// Animation Save
	m_Animator->FindAnimation(L"DamageMissile")->Save(L"animation\\damage\\missile\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\damage\\missile\\DamageMissile.anim");

	m_Animator->Play(L"DamageMissile", false);
}

qDamage_missile::qDamage_missile(const qDamage_missile& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qDamage_missile::~qDamage_missile()
{
}

void qDamage_missile::tick()
{
	qObj::tick();

	if (L"DamageMissile" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}
