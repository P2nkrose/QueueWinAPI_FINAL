#include "pch.h"
#include "qDamage_miss.h"

#include "qAnimator.h"

#include "qTaskMgr.h"

qDamage_miss::qDamage_miss()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* DamageMiss = qAssetMgr::GetInst()->LoadTexture(L"DamageMiss", L"texture\\damage\\miss\\miss.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"DamageMiss", DamageMiss, Vec2(0.f, 0.f), Vec2(140.f, 60.f), 5, 10);

	// Animation Save
	m_Animator->FindAnimation(L"DamageMiss")->Save(L"animation\\damage\\miss\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\damage\\miss\\DamageMiss.anim");

	m_Animator->Play(L"DamageMiss", false);
}

qDamage_miss::qDamage_miss(const qDamage_miss& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qDamage_miss::~qDamage_miss()
{
}

void qDamage_miss::tick()
{
	qObj::tick();

	if (L"DamageMiss" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}
